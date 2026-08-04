# AI Memory Visualizer — Corrected Memory Maps

Build flags used: `-Wall -Wextra -Werror -pedantic -std=gnu89 -g` (per `Makefile`).
Programs were compiled and run normally (no Valgrind) to observe real addresses
and real runtime behavior, then an AI-generated explanation was reviewed and
corrected against that real output.

---

## 1. `stack_example.c` — Stack Frames & Recursion

### What the program does
`walk_stack(depth, max_depth)` recurses from depth 0 to 3. At each call it:
- declares a local `int marker` (stack),
- calls `dump_frame()`, which itself declares `local_int`, `local_buf[16]`,
  and `p_local` (all stack, local to `dump_frame`'s own frame),
- recurses deeper *before* printing the "exit" line for the current depth.

### Real output (addresses truncated to the meaningful low bits)

| depth | `&local_int` (in `dump_frame`) | `local_buf` | `&marker` (in `walk_stack`) |
|---|---|---|---|
| 0 | ...a804 | ...a810 | ...a854 |
| 1 | ...a7d4 | ...a7e0 | ...a824 |
| 2 | ...a7a4 | ...a7b0 | ...a7f4 |
| 3 | ...a774 | ...a780 | ...a7c4 |

### Stack/Heap classification
Every single variable in this program (`marker`, `local_int`, `local_buf`,
`p_local`) lives **on the stack**. There is no `malloc` anywhere in this file.
`p_local` is a stack variable whose *value* is a pointer, but it points to
another stack variable (`&local_int`) — it does not point to heap memory.

### Lifetimes
- Each call to `walk_stack` and `dump_frame` creates a **new stack frame**.
  `marker` at depth 0 and `marker` at depth 1 are *different objects* with
  *different addresses*, even though they share a variable name.
- `dump_frame`'s locals (`local_int`, `local_buf`, `p_local`) are only valid
  from the moment `dump_frame` is entered until it returns. Once
  `dump_frame("enter", depth)` returns back into `walk_stack`, those specific
  addresses are dead — the *next* call to `dump_frame` (at `depth+1`, or the
  "exit" call at the same depth) reuses/overwrites that region of the stack.
- Note that the "exit" call to `dump_frame` at a given depth prints the
  **same addresses** as the "enter" call at that same depth (e.g. depth 3:
  `...a774` both times). That's expected: by the time control returns to
  print "exit" at depth 3, all deeper frames (depth 4 doesn't exist here)
  have already been popped, so `dump_frame` is called from the exact same
  point in `walk_stack`'s frame and gets the same offset again.

### Pointer aliasing
`p_local = &local_int` inside `dump_frame`. This is straightforward: one
pointer, one target, no sharing across frames. There is **no aliasing
between depths** — depth 0's `local_int` and depth 1's `local_int` are
unrelated objects that merely happen to reuse nearby stack addresses at
different points in time.

### AI explanation — documented error and correction

**AI's first-pass explanation (hypothesis, before verification):**
> "Since `local_int` is declared before `local_buf` in the source code, and
> the stack grows downward, `local_buf` must be at a *lower* address than
> `local_int` within the same frame. Also, because `walk_stack` calls
> `dump_frame` twice per depth level (enter and exit) and the addresses
> printed are identical each time, this must mean the compiler is caching
> `dump_frame`'s frame and reusing it — i.e. the two calls share the exact
> same stack frame instance."

**Why this is wrong:**
1. The address data contradicts the "lower address" claim: at depth 0,
   `&local_int = ...a804` and `local_buf = ...a810`. `...a810 > ...a804`, so
   `local_buf` is actually at a **higher** address than `local_int`, not
   lower. C does not guarantee any particular relative ordering of
   local variables within a frame — the compiler is free to reorder, pad,
   or place them however it wants (for alignment, register spilling,
   canary placement, etc.). Declaration order is a source-level detail,
   not a memory-layout guarantee.
2. "Same address ⇒ same frame instance" is also wrong. The enter-call and
   exit-call at a given depth *are* two separate calls with two separate
   frames — they are simply **sequential**, not overlapping in time. The
   first `dump_frame` call fully returns (destroying its frame) before
   `walk_stack` recurses; when control comes back up and calls
   `dump_frame` again for "exit", it's a brand-new call that happens to
   land on the same stack offset because no other function call disturbed
   the stack pointer in between. It's address *reuse across time*, not a
   *shared instance*.

**Corrected statement:** Local variable placement within a stack frame is
compiler-determined and not predictable from declaration order alone.
Identical addresses across two calls indicate the *same memory location was
reused after being freed by a previous call's return*, not a persisting
single frame.

---

## 2. `heap_example.c` — Heap Allocation, Ownership, and a Deliberate Leak

### Real output
```
alice = 0x5573c72f22b0   alice->name = 0x5573c72f22d0   age=30
bob   = 0x5573c72f22f0   bob->name   = 0x5573c72f2310    age=41
```

### Stack vs heap classification
- **Stack:** the pointer variables `alice` and `bob` themselves (in `main`),
  and the parameter/local variables inside `person_new` (`i`, `len`, and the
  pointer variable `p` itself — `p` is a stack variable that *holds* a heap
  address).
- **Heap:** everything `p` and `p->name` point to. Each `Person` struct
  (`malloc(sizeof(Person))`) is one heap block; each name string
  (`malloc(len + 1)`) is a **second, separate** heap block. So each
  `person_new()` call produces **two independent heap allocations** linked
  by the `name` pointer field inside the `Person` struct.

### Ownership tracking
- `alice` owns two heap blocks: the `Person` struct at `0x...22b0` and the
  string at `0x...22d0`.
- `bob` owns two heap blocks: the `Person` struct at `0x...22f0` and the
  string at `0x...2310`.
- Correct cleanup requires freeing **both** blocks for each person, and the
  *name* must be freed **before** the struct (once the struct is freed, the
  pointer to reach `->name` is gone).

### The deliberate leak
Look at what `main` actually does:
```c
free(bob->name);       /* frees bob's string  -- OK */
free(bob);              /* frees bob's struct   -- OK, bob fully cleaned up */

person_free_partial(alice);   /* only calls free(p); never frees p->name */
```
`person_free_partial()` frees only the `Person` struct itself and never
touches `p->name`. For `bob`, the caller manually freed `bob->name` first,
so `bob` is fully cleaned up. For `alice`, the *only* cleanup path used is
`person_free_partial(alice)`, so `alice->name` (the heap block at
`0x5573c72f22d0`, holding `"Alice"`) is **never freed** — it is leaked the
moment `alice` (the last pointer to the `Person` struct, which is now also
freed) goes out of scope at the end of `main`.

This is a **6-byte leak** (`"Alice"` + `'\0'`) that Valgrind would report as
"definitely lost" — the block is unreachable and no pointer to it survives
program exit.

### AI explanation — a second worth-flagging inaccuracy
An AI summary of this file claimed: *"the program leaks memory for both
`alice` and `bob` because `person_free_partial` never frees the name
field."* This is **half-wrong**: `person_free_partial` is indeed incomplete
by itself, but `bob`'s name was freed *separately, before* `person_free_partial`
was even involved (in fact `person_free_partial` is never called on `bob`
at all — `bob` is freed manually and only `alice` goes through
`person_free_partial`). Only `alice->name` leaks. Blanket statements about
"the function" being the sole cause ignore how it's actually *called* at
each site — the leak is a property of the specific call sequence in `main`,
not of `person_free_partial` in isolation.

---

## 3. `aliasing_example.c` — Aliasing and Use-After-Free

### Real output
```
a=0x55f762b4a2b0 b=0x55f762b4a2b0 a[2]=22 b[2]=22
after free(a): b=0x55f762b4a2b0 (dangling)
reading b[2]=-1608275214
wrote b[3]=1234
exit=0
```

(Compiled with `-Wall -Wextra -pedantic -std=gnu89 -g`, **without** `-Werror`,
since GCC 13's static analysis refuses to compile this file at all under
`-Werror` — see build note below.)

### Build-time note (important finding)
Under the project's actual specified flags (`-Werror` included), this file
**fails to compile**:
```
error: pointer 'b' used after 'free' [-Werror=use-after-free]
```
GCC 13's `-Wuse-after-free` flow analysis can see that `b = a;` makes `b` an
alias of `a`, and that every later use of `b` occurs after `free(a)`. This
is a case where **the compiler itself performs the aliasing/lifetime
analysis** that this task asks us to do by hand — a strong sanity check
that our manual reasoning below is correct, and a reminder that strict
warning flags can catch memory-safety bugs before a single line ever runs
or Valgrind is invoked.

### Stack vs heap classification
- **Stack:** pointer variables `a` and `b` in `main`; `arr`, `i`, `n` inside
  `make_numbers`.
- **Heap:** the block returned by `malloc((size_t)n * sizeof(int))` inside
  `make_numbers` — one allocation of `5 * sizeof(int)` = 20 bytes.

### Pointer aliasing (the core of this file)
```c
a = make_numbers(n);   /* a now owns the heap block */
b = a;                  /* b is now an ALIAS of a: same address, same block */
```
After `b = a;`, `a` and `b` are two different stack variables holding the
**identical heap address** (`0x55f762b4a2b0` in this run). They are not two
allocations — there is exactly **one** 20-byte heap block, and two names
for it. This is true pointer aliasing: any write through `a[i]` or `b[i]`
mutates the same underlying memory.

### Ownership and the use-after-free
`free(a)` releases the one heap block. Critically, `free()` does **not**
know that `b` also refers to that block, and it does **not** null out `b`.
`b` becomes a **dangling pointer**: it still holds the numeric address
`0x55f762b4a2b0`, but that address is no longer a valid allocation as far
as the heap allocator is concerned. The subsequent lines:
```c
printf("  reading b[2]=%d\n", b[2]);   /* undefined behavior */
b[3] = 1234;                            /* undefined behavior */
```
both read/write through `b` **after** the block `b` points to has been
freed. This is a textbook use-after-free (UAF).

### AI explanation — documented error and correction (required example)

**AI's first-pass explanation (hypothesis, before verification):**
> "Once `free(a)` is called, `b` becomes an invalid pointer, and any attempt
> to read or write through `b` afterward will cause the program to crash
> immediately with a segmentation fault, since the memory has been
> deallocated and is no longer accessible."

**Why this is wrong:**
The real output shows the program did **not** crash. `reading b[2]` printed
a garbage value (`-1608275214`) instead of `22`, and `wrote b[3]=1234`
succeeded and printed normally, and the program exited with status `0`.

Use-after-free is **undefined behavior**, not "guaranteed crash on access."
In practice, `free()` typically does not unmap the underlying memory page or
zero it out immediately — it usually just marks the block as available in
the allocator's free list (or merges it with adjacent free space) for reuse
by a *future* `malloc()`. Since no other allocation happened between
`free(a)` and the reads/writes through `b`, the bytes at that address
happened to still be reachable and (mostly) still readable/writable, so the
program "appeared to work" while actually corrupting allocator-internal
state and reading stale/undefined content. A crash is *possible* under UAF
(e.g., if the page had been returned to the OS, or if another allocation
had overwritten/reused that block first) but it is not guaranteed, and
relying on "it will crash" as a detection strategy is precisely the kind of
incorrect assumption this project is designed to expose. This is also why
tools like Valgrind exist: Valgrind would flag every one of these accesses
as "Invalid read of size 4" / "Invalid write of size 4" on a freed block,
even though the raw process itself ran to completion without crashing or
printing any visible error.

**Corrected statement:** After `free(a)`, `b` is a dangling alias. Any
access through `b` is undefined behavior — the *observable* result (garbage
value, apparent success, or crash) depends on allocator internals and is
not something the source code guarantees one way or the other. The program
"working" is not evidence of correctness; it is evidence that UB happened
not to manifest visibly in this particular run.

### Independent verification: address (stack) vs. content (heap)

Running the program a second time (a separate execution, independent of the
run captured above) produced:
```
a=0x5925455896b0 b=0x5925455896b0 a[2]=22 b[2]=22
after free(a): b=0x5925455896b0 (dangling)
reading b[2]=-524430081
wrote b[3]=1234
```

Comparing the two runs directly clarifies exactly *what* `free()` touches
and what it does not:

- `a` and `b` are two separate **stack** variables (boxes). `b = a;` copies
  the *value* stored in `a` (the address) into `b` — it does not create a
  second heap allocation. After this line, both boxes hold the identical
  address, and both point at the **one and only** heap block.
- `free(a)` takes that address **value** and hands it to the allocator to
  release the **heap block** it identifies. `free()` operates on the block
  in the heap — it does not reach back and modify the stack boxes `a` or
  `b` themselves. That is exactly why `b` printed the **same address**
  before and after `free(a)`, and why it printed the same address again in
  the second, independent run: the box `b` was never touched.
- What *did* change between reading `b[2]` before and after `free(a)` is the
  **content stored at that heap address**, not the address itself. The
  freed block became available for the allocator to write its own internal
  bookkeeping into, which is why `b[2]` read back as garbage instead of `22`.
- The two runs read back **different** garbage values for `b[2]`
  (`-1608275214` vs. `-524430081`) despite executing the identical source
  code and reusing the identical relative address. This is direct, repeatable
  evidence that the *content* left behind after `free()` is undefined and
  run-dependent — a stack-allocated pointer variable keeps whatever address
  value it was assigned regardless of what happens to the memory it points
  to, but the validity/content of that memory is a separate matter entirely.

---

## Summary

| Program | Stack objects | Heap objects | Key lifetime/aliasing issue |
|---|---|---|---|
| `stack_example.c` | `marker`, `local_int`, `local_buf`, `p_local` | none | Frame reuse across sequential calls; layout is compiler-determined, not declaration-order |
| `heap_example.c` | `alice`, `bob`, `p`, `i`, `len` | `Person` struct + name string, ×2 | `alice->name` leaked because `person_free_partial` never frees the `name` field, and that's the only cleanup path used for `alice` |
| `aliasing_example.c` | `a`, `b`, `arr`, `i`, `n` | one `int[5]` block | `b = a` creates a true alias; `free(a)` leaves `b` dangling; later access through `b` is UB, not a guaranteed crash |
