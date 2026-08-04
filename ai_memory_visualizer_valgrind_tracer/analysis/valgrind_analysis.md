# Valgrind & AI Memory Tracer — Analysis

Both programs were compiled with the project's `Makefile` flags
(`-Wall -Wextra -Werror -pedantic -std=gnu89 -g`, except `aliasing_example.c`
which was compiled without `-Werror` — see note in `memory_maps.md`, GCC 13's
`-Wuse-after-free` refuses to build it under `-Werror`), then run under:

```
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./<binary>
```

---

## 1. `heap_example.c` — Memory Leak

### Full relevant output
```
HEAP SUMMARY:
    in use at exit: 6 bytes in 1 blocks
    total heap usage: 5 allocs, 4 frees, 4,138 bytes allocated

6 bytes in 1 blocks are definitely lost in loss record 1 of 1
   at 0x4846828: malloc (in vgpreload_memcheck-amd64-linux.so)
   by 0x109211: person_new (heap_example.c:21)
   by 0x1092FA: main (heap_example.c:51)

LEAK SUMMARY:
   definitely lost: 6 bytes in 1 blocks
   ...
ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

### Classification
**Type:** Memory leak, severity **"definitely lost"** (the strongest leak
category Valgrind reports — it means no pointer to this block exists
anywhere in the program at exit, not even an indirect one).

### Which memory object is involved
The report only shows an **allocation site**, never a "free'd at" trace,
because that is exactly what defines a leak: the block was never passed to
`free()` at all during the program's execution. Valgrind can only tell you
where something was *born*; it has no death to report.

`heap_example.c:21` is the second `malloc` inside `person_new`:
```c
Person *p = (Person *)malloc(sizeof(Person));   /* line ~15, malloc #1: the struct */
...
p->name = (char *)malloc(len + 1);              /* line 21, malloc #2: the name string */
```
`person_new` performs **two independent heap allocations** per call: one for
the `Person` struct, one for the name string. The leaked 6 bytes (`"Alice"` +
`'\0'`) correspond specifically to malloc #2 — the **name string**, not the
struct.

The call stack (`person_new` at line 21, called from `main` at line 51)
confirms this is the `alice = person_new("Alice", 30);` call — line 51 in
`main`.

### Lifetime violation / root cause
Tracing ownership through `main`:
```c
free(bob->name);            /* bob's name freed explicitly */
free(bob);                  /* bob's struct freed          */

person_free_partial(alice); /* the ONLY cleanup path used for alice */
```
`person_free_partial()` only calls `free(p)` — it frees the `Person` struct
itself but never touches `p->name`:
```c
static void person_free_partial(Person *p)
{
    if (!p) return;
    free(p);          /* struct freed; p->name field goes with it */
}
```
The `name` field inside the `Person` struct held the **only pointer value**
in the entire program that referenced the heap block containing `"Alice"`.
That field lived *inside* the struct's own memory. The moment `free(p)`
released the struct, the last stored copy of the name-block's address was
destroyed along with it — not because the name block itself was freed, but
because the **sole reference to its address was contained in memory that
was itself just deallocated**. No variable anywhere in the program (local,
global, or otherwise) retained a separate copy of that address afterward.
This is precisely a **leak due to lost ownership**: the object is still
technically alive on the heap, but it becomes permanently unreachable —
"orphaned" — the instant its only referencing pointer is destroyed alongside
it.

`bob` does not exhibit this bug because `main` explicitly frees
`bob->name` *before* freeing the `bob` struct, preserving a valid,
still-reachable pointer to the name block at the moment it is released.

---

## 2. `aliasing_example.c` — Use-After-Free (Invalid Read / Invalid Write)

### Full relevant output
```
Invalid read of size 4
   at 0x1092F5: main (aliasing_example.c:42)
 Address 0x4a7d088 is 8 bytes inside a block of size 20 free'd
   at 0x484988F: free (...)
   by 0x1092D1: main (aliasing_example.c:38)
 Block was alloc'd at
   at 0x4846828: malloc (...)
   by 0x1091E4: make_numbers (aliasing_example.c:12)
   by 0x109272: main (aliasing_example.c:30)

Invalid write of size 4
   at 0x109315: main (aliasing_example.c:44)
 Address 0x4a7d08c is 12 bytes inside a block of size 20 free'd
   ... (same free/alloc trace)

Invalid read of size 4
   at 0x109323: main (aliasing_example.c:45)
 Address 0x4a7d08c is 12 bytes inside a block of size 20 free'd
   ... (same free/alloc trace)

HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
    total heap usage: 2 allocs, 2 frees, 4,116 bytes allocated
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 3 errors from 3 contexts
```

### Classification
**Type:** Use-after-free, reported as three separate Memcheck errors:
two `Invalid read of size 4` and one `Invalid write of size 4`. Note there
is **no leak** here (`0 bytes in 0 blocks`, `all heap blocks were freed`) —
this file's bug is entirely about *timing/lifetime of access*, not about
missing `free()` calls. This is an important distinction: a program can be
"leak-free" by Valgrind's leak checker and still be riddled with severe
memory-safety errors.

### Which memory object is involved
All three errors point to the **same single heap block**: a 20-byte
allocation (`5 * sizeof(int)`), allocated by `malloc` inside
`make_numbers()` (`aliasing_example.c:12`), called from `main` at line 30 —
this is the `a = make_numbers(n);` allocation.

Each error's "Address ... is N bytes inside a block of size 20" line maps
directly to an array index: `offset = index * sizeof(int)`.

| Error | Line | Source | Offset | Index |
|---|---|---|---|---|
| Invalid read #1 | 42 | `b[2]` | 8 bytes | 2 |
| Invalid write | 44 | `b[3] = 1234;` | 12 bytes | 3 |
| Invalid read #2 | 45 | `b[3]` | 12 bytes | 3 |

### Lifetime violation / root cause
```c
a = make_numbers(n);   /* a owns the one heap block */
b = a;                  /* b becomes an ALIAS: same address as a */
...
free(a);                /* the block is released via a */
...
b[2];                    /* line 42: read through b, AFTER free(a)  */
b[3] = 1234;             /* line 44: write through b, AFTER free(a) */
b[3];                    /* line 45: read through b, AFTER free(a)  */
```
`b = a;` does not create a second allocation — it copies the address
*value* from `a` into `b`, making both stack variables reference the
identical heap block (true pointer aliasing). `free(a)` releases that block
using the address stored in `a`; this operation affects the heap block
itself, not the stack variables `a` or `b` — which is exactly why every
Valgrind trace above still shows `b`'s address unchanged before and after
the free. However, once the block is released, it is no longer a valid
allocation from the allocator's point of view, and `b` becomes a
**dangling pointer**: it still holds a numeric address, but that address no
longer denotes memory the program owns. Every subsequent access through
`b` (lines 42, 44, 45) is a use-after-free — accessing memory whose
lifetime, from the allocator's perspective, has already ended.

Consistent with this being genuine **undefined behavior** rather than a
guaranteed crash: running the program normally (outside Valgrind) produced
a garbage value for `b[2]` (differing across separate runs — e.g.
`-1608275214` vs. `-524430081` on two independent executions), while
running it *under* Valgrind produced `b[2]=22`, the original, "correct"
value. This is expected: Valgrind's own memory-management instrumentation
changes how/when the underlying bytes of a freed block get overwritten, so
the specific garbage (or lack thereof) observed after a UAF is an artifact
of the current allocator state — not something the C standard, or the
program's logic, guarantees one way or the other.

---

## 3. AI Interpretation Review — Documented Correction

**AI's first-pass interpretation (hypothesis, before careful review):**
> "The `heap_example.c` leak happens because `person_free_partial` frees the
> `Person` struct, and freeing that struct also frees `p->name` since it's
> a field inside the struct — but the analysis shows the name block is
> still 'in use at exit', so what must have happened is that `free(p)`
> failed to actually deallocate the struct properly, leaving the name
> pointer dangling but unfreed."

**Why this is wrong:**
1. `free(p)` frees exactly one block: the `Person` struct itself
   (`sizeof(Person)` bytes — i.e., the `name` pointer *field* and the `age`
   integer field, as raw storage). It does **not** recursively free
   whatever `p->name` points to — C has no concept of "freeing a struct
   frees its pointer members' targets." That is a *manual* responsibility
   the programmer must implement (which is exactly what `person_free_partial`
   fails to do).
2. The claim that "`free(p)` failed to actually deallocate the struct
   properly" is unsupported and contradicted by the output: Valgrind's
   heap summary shows `5 allocs, 4 frees` — of the two `Person` structs
   allocated, both were in fact freed (`bob`'s via the manual `free(bob)`
   call, `alice`'s via `person_free_partial(alice)`). The **struct** was
   freed correctly in both cases; only the **name string** for `alice` was
   never freed. Attributing the leak to a "failed" struct-free invents a
   mechanism Valgrind's own numbers rule out — `in use at exit: 6 bytes in
   1 blocks` is exactly the size of `"Alice\0"`, not `sizeof(Person)`,
   confirming the leaked block is the name string, not the struct.

**Corrected statement:** `free()` only releases the single block whose
address is passed to it. A struct's pointer-typed fields must be freed
independently and explicitly, in the correct order (inner allocations
before the struct that references them), or their target blocks become
unreachable — which is what happened to `alice->name` here. The struct
itself was freed correctly; the bug is a missing, separate `free()` call
for a *different* block, not a malfunction of the `free()` that was called.

---

## Summary

| Program | Valgrind finding | Precise classification | Root cause |
|---|---|---|---|
| `heap_example.c` | `6 bytes definitely lost` | Memory leak — lost ownership | `person_free_partial` frees the `Person` struct but never `p->name`; for `alice`, this is the only cleanup path used, so the name block's one and only address (stored inside the now-freed struct) is destroyed with no copy surviving |
| `aliasing_example.c` | `2 Invalid read` + `1 Invalid write` (3 errors, 0 leaks) | Use-after-free via pointer aliasing | `b = a` aliases the block; `free(a)` releases it; every later access through `b` (lines 42, 44, 45) touches memory whose allocation has already ended — undefined behavior, not a guaranteed crash |
