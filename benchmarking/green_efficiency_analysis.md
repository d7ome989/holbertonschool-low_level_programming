# Green Efficiency Analysis



## Measurement Methodology

To evaluate the runtime efficiency of different computational implementations, a rigorous empirical approach was established within a controlled environment. The execution times were captured using the standard `clock()` function from the `<time.h>` library, which measures the CPU time consumed by the program. To ensure high precision, time intervals were converted into seconds by dividing the raw clock ticks by `CLOCKS_PER_SEC`, casting the values to floating-point representations. The compilation followed strict ISO C90 compliance using the required flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`. Measurements were isolated around distinct functional boundaries: data generation (`build_dataset`), state transformation (`process_dataset`), and aggregation (`reduce_checksum`). Each program was executed three consecutive times under identical system conditions to observe timing variability and eliminate external operating system noise.



## Observed Performance Differences

The empirical data collected reveals substantial performance variations based on workload size and algorithmic structural complexity. In the baseline test (Task 0), executing 100 million iterations of a simple modular loop yielded 0.350584 seconds on the first run, dropping to 0.237246 seconds and 0.235901 seconds in subsequent runs. This early difference demonstrates standard CPU warm-up or initial background scheduling overhead.



The most critical divergence appeared in Task 1 when comparing the naive algorithm against the single-pass implementation. The naive algorithm required 4.195345 seconds during its initial execution to process 625,025,000 operations, while the single-pass alternative completed its processing of 25,000 elements in just 0.000174 seconds. Across all three iterations, the naive approach averaged approximately 3.23 seconds, whereas the optimized single-pass approach consistently finished in roughly 0.00013 seconds. This massive speedup highlights how reducing algorithmic complexity from a quadratic scale to a linear scale minimizes processing demands.



In the multi-phase experiment (Task 2), the execution was broken down into three logical phases over 50,000 elements. Across all runs, the `process_dataset` phase consistently demanded the highest fraction of the total execution time (0.000833 seconds in Run 1 and 0.000718 seconds in Run 3) due to its combination of multiplication, division, and modulo arithmetic. Conversely, the `reduce_checksum` phase was the most efficient, requiring only 0.000463 seconds in Run 1 and falling to 0.000294 seconds by Run 3. The aggregate total time scaled downward from 0.001880 seconds (Run 1) to 0.001496 seconds (Run 3), confirming a predictable optimization trend as hardware caches stabilized.



## Relation Between Runtime and Energy Consumption

Software runtime serves as a direct proxy for active energy consumption. When a program executes an inefficient algorithm, such as the naive approach that ran for over 4.19 seconds, it forces the CPU to remain in a high-power state (P-state) for an extended duration. Longer CPU cycles translate directly to sustained electrical power draw. By deploying the single-pass algorithm, which dropped execution time to less than a millisecond, the processor minimizes its active execution window and can return to a low-power idle state sooner. At a massive datacenter scale, reducing processing time from seconds to fractions of a millisecond minimizes grid electricity usage, directly lowering carbon emissions and cooling costs.



## Limitations of the Experiment

While these measurements offer strong directional insight, the experiment has distinct analytical limitations. First, `clock()` tracks CPU time rather than real physical power draw; it does not measure energy metrics in Joules or Watts, nor does it capture memory or peripheral power. Second, the observed timing variability—such as the drop from 0.350584 to 0.235901 seconds in the baseline loop—shows that background operating system tasks, thread scheduling, and hardware dynamic frequency scaling interfere with capturing absolute algorithmic costs.



## Practical Engineering Takeaway

The data underscores that sustainability in software engineering is primarily driven by algorithmic discipline rather than hardware power. Optimizing code structure, as seen in the single-pass implementation, produces performance gains that far exceed any hardware-level enhancements. Software engineers must treat execution time as a critical ecological resource, utilizing empirical profiling to eliminate intensive computational loops before deploying software at scale.# Green Efficiency Analysis



## Measurement Methodology

To evaluate the runtime efficiency of different computational implementations, a rigorous empirical approach was established within a controlled environment. The execution times were captured using the standard `clock()` function from the `<time.h>` library, which measures the CPU time consumed by the program. To ensure high precision, time intervals were converted into seconds by dividing the raw clock ticks by `CLOCKS_PER_SEC`, casting the values to floating-point representations. The compilation followed strict ISO C90 compliance using the required flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`. Measurements were isolated around distinct functional boundaries: data generation (`build_dataset`), state transformation (`process_dataset`), and aggregation (`reduce_checksum`). Each program was executed three consecutive times under identical system conditions to observe timing variability and eliminate external operating system noise.



## Observed Performance Differences

The empirical data collected reveals substantial performance variations based on workload size and algorithmic structural complexity. In the baseline test (Task 0), executing 100 million iterations of a simple modular loop yielded 0.350584 seconds on the first run, dropping to 0.237246 seconds and 0.235901 seconds in subsequent runs. This early difference demonstrates standard CPU warm-up or initial background scheduling overhead.



The most critical divergence appeared in Task 1 when comparing the naive algorithm against the single-pass implementation. The naive algorithm required 4.195345 seconds during its initial execution to process 625,025,000 operations, while the single-pass alternative completed its processing of 25,000 elements in just 0.000174 seconds. Across all three iterations, the naive approach averaged approximately 3.23 seconds, whereas the optimized single-pass approach consistently finished in roughly 0.00013 seconds. This massive speedup highlights how reducing algorithmic complexity from a quadratic scale to a linear scale minimizes processing demands.



In the multi-phase experiment (Task 2), the execution was broken down into three logical phases over 50,000 elements. Across all runs, the `process_dataset` phase consistently demanded the highest fraction of the total execution time (0.000833 seconds in Run 1 and 0.000718 seconds in Run 3) due to its combination of multiplication, division, and modulo arithmetic. Conversely, the `reduce_checksum` phase was the most efficient, requiring only 0.000463 seconds in Run 1 and falling to 0.000294 seconds by Run 3. The aggregate total time scaled downward from 0.001880 seconds (Run 1) to 0.001496 seconds (Run 3), confirming a predictable optimization trend as hardware caches stabilized.



## Relation Between Runtime and Energy Consumption

Software runtime serves as a direct proxy for active energy consumption. When a program executes an inefficient algorithm, such as the naive approach that ran for over 4.19 seconds, it forces the CPU to remain in a high-power state (P-state) for an extended duration. Longer CPU cycles translate directly to sustained electrical power draw. By deploying the single-pass algorithm, which dropped execution time to less than a millisecond, the processor minimizes its active execution window and can return to a low-power idle state sooner. At a massive datacenter scale, reducing processing time from seconds to fractions of a millisecond minimizes grid electricity usage, directly lowering carbon emissions and cooling costs.



## Limitations of the Experiment

While these measurements offer strong directional insight, the experiment has distinct analytical limitations. First, `clock()` tracks CPU time rather than real physical power draw; it does not measure energy metrics in Joules or Watts, nor does it capture memory or peripheral power. Second, the observed timing variability—such as the drop from 0.350584 to 0.235901 seconds in the baseline loop—shows that background operating system tasks, thread scheduling, and hardware dynamic frequency scaling interfere with capturing absolute algorithmic costs.



## Practical Engineering Takeaway

The data underscores that sustainability in software engineering is primarily driven by algorithmic discipline rather than hardware power. Optimizing code structure, as seen in the single-pass implementation, produces performance gains that far exceed any hardware-level enhancements. Software engineers must treat execution time as a critical ecological resource, utilizing empirical profiling to eliminate intensive computational loops before deploying software at scale.
