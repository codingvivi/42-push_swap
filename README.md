_This project has been created as part of the 42 curriculum by lrain_

# push_swap

![](data/get-rotated.gif)

## Description

My submission for 42's push swap project!

The rules:
read a sequence of unordered,
non-duplicate integers
via cli input,
return them sorted
using two stacks (`a` and `b`)
and a fixed set of operations,
aiming for the **shortest possible sequence** of
moves.

Available operations:

| op | effect |
| ----- | ------------------------------------------------------ |
| `sa` | swap the top two elements of `a` |
| `sb` | swap the top two elements of `b` |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | push top of `b` onto `a` |
| `pb` | push top of `a` onto `b` |
| `ra` | rotate `a` up by one (top element becomes last) |
| `rb` | rotate `b` up by one |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | reverse-rotate `a` (last element becomes top) |
| `rrb` | reverse-rotate `b` |
| `rrr` | `rra` and `rrb` simultaneously |

Benchmark targets (100% validation):
**100 numbers in < 700 ops**
and **500 numbers in < 5500 ops**.

## Instructions

### Project layout

The repository uses a nested `src/` layout
inspired by Pitchfork convention
for development:

```
src/
├── main.c
├── stacks.h            # shared ring-buffer stack type
├── free/               # allocation helpers
├── init/               # argument parsing + stack construction
├── stackops/           # the 11 push_swap operations + index helpers
└── sort/               # sorting strategy
    ├── algo/           # top-level sort dispatchers (sort_3, sort_4or5, sort_n)
    │   └── n_algo/     # the n-case algorithm's individual steps
    └── helpers/        # helpers shared across multiple algo steps
external/libs/libft/    # libft submodule
docs/42/                # subject + norm PDFs
```

Headers live next to the `.c` files that define them —
per the Pitchfork convention,
`include/` is reserved for public-API headers of libraries,
and `push_swap` is an executable.

### Getting the repo

```bash
git clone --recursive git@github.com:codingvivi/42-push_swap.git
# or, if already cloned without --recursive:
git submodule update --init --recursive
```

### Dependencies

- `cc` (gcc or clang) and GNU `make`
- The `libft` submodule at `external/libs/libft` (pulled in by the clone above)

*Optionally:*

- `just` to wrap/orchestrate useful commands
- `bear` for compile commands
- [`push_swap_visualizer`](https://github.com/o-reo/push_swap_visualizer) by o-reo
  to visualize what push_swap is doing

### Building & running

```bash
make                 # dev build → build/bin/src/push_swap
make re              # clean rebuild
make clean           # remove object files
make fclean          # remove all build artifacts
```

Optional `just` wrappers (refreshes `compile_commands.json` via `bear`):

```bash
just build             # == bear -- make
just run ARGS...       # run the compiled binary
just brun BARGS RARGS  # build, then run
just crun BARGS RARGS  # make clean, then brun
just rerun ARGS...     # make re, then run
```

Run manually:

```bash
./build/bin/src/push_swap 2 1 3 6 5 8
# prints the instruction list on stdout

./build/bin/src/push_swap 0 one 2 3
# Error
```

or with just:

```bash
just run 2 1 3 6 5 8
just run 0 one 2 3
```

- No arguments
  → no output,
  clean exit.
- Invalid input (non-integer, overflow, duplicates)
  → `Error\n` on stderr,
  non-zero exit.
- Arguments can be passed as separate `argv` entries,
  or as a single quoted whitespace-separated string
  (e.g. `"4 67 3 87 23"`).
- In dev builds, passing `-v` or `--verbose`
  as the **first** argument
  prints intermediate cost tables and sort state for debugging.
  The flag is compiled out of turn-in builds
  (where `-DNDEBUG` is set).

Validate with a checker
(run `make tester` first to stage `checker_linux` into `build/tester/`):

```bash
ARG="4 67 3 87 23"
./build/bin/src/push_swap $ARG | ./build/tester/checker_linux $ARG
# OK
```

### Developing & Evaluating

#### Turn-in build

To generate a folder that has the exact submission specifications
run:

```bash
make stage                        # → build/dist/push_swap_turnin_/
```

The resulting folder contains only the allowed files
and matches the folder structure required by the project guidelines.
Per those same guidelines
only integer arguments are allowed,
so `-v` / `--verbose` would be non-conformant —
the turn-in build compiles with `-DNDEBUG`
to strip the flag out entirely,
keeping it strictly a dev-time debugging aid.

To generate that folder plus a tarball
(handy to send to the school computer/
use as a github release)
run

```bash
RELEASE_TAG=v1 make dist          # → push_swap_turnin_v1.tar.gz
```

The `just` wrappers run pre-flight checks before packaging:

```bash
just dist RELEASE_TAG=v1          # rebuild + norminette, then make dist
just dist-safe RELEASE_TAG=v1     # rebuild + norminette + full tester, then make dist
```

Run the checks standalone:

```bash
just checks-dist                  # rebuild + norminette
just checks-dist-full             # rebuild + norminette + full tester
```

To package, tag, push, and cut a GitHub release in one go:

```bash
just publish v1 "release notes"   # make dist + git tag + push + gh release create
```

#### (Re)generating a sane repo directory

The strictest interpretation of the instructions for push_swap
and libft
requires flat folder structures for both projects as follows:

```
root/
├── *.c                 # push_swap sources
├── *.h                 # push_swap headers
├── Makefile
├── README.md
└── libft/
    ├── *.c             # libft sources
    ├── *.h             # libft headers
    ├── Makefile
    └── README.md
```

Furthermore,
the final build result for either project
should be placed in the respective project's root directory.

To conform to this requirement
while still making things easy on the evaluators
(and developer)
`make stage` will generate the folder structure as described above
into `build/dist/push_swap_turnin_/`.

The switch between "turn-in" and "dev" behavior is driven by a
single Makefile variable:

```make
TURNIN_RUN = true
```

`make stage` prepends that line to the Makefile it copies into the
staged tree,
so the staged Makefile knows it's running in turn-in mode.
In dev mode the variable is unset and the same targets are no-ops
on the project layout.

Inside the staged (flat) tree,
the workflow is:

```bash
make            # unflattens *.c / *.h into src/ and
                # libft/ into external/libs/libft/, then builds
make init       # same unflatten step, without compiling
make fclean     # cleans build artifacts AND re-flattens the tree
                # back to exactly what was shipped
```

The default `all` target depends on `init`,
so a plain `make` in the staged tree always unflattens first —
one source of truth for the nested layout.

In the dev tree (where `TURNIN_RUN` is unset),
`make fclean` only removes build artifacts —
it does *not* restructure the push_swap src layout.
(libft's own fclean does flatten its tree,
but the next `make` re-nests it transparently via `make init`.)

#### Testing

Both testers build on top of the staged turn-in tree,
so they exercise the exact sources that would ship.

```bash
make tester          # stage + build + stage push_swap_tester scripts in build/tester/
make tester-yfu      # stage + build + stage yfu's tester in build/tester-yfu/
```

`just` wrappers run the tester after building it:

```bash
just test                     # push_swap_tester (push_swap_test_linux.sh)
just test-yfu                 # yfu's basic_test.sh
just test-yfu-loop SIZE COUNT # yfu's loop.sh (defaults: 100 10)
just test-norm                # run norminette across src/
```

#### Visualizer

```bash
make visualizer              # builds external/tools/push_swap_visualizer
just visualize-deps-tw       # install build deps (zypper, openSUSE Tumbleweed)
just visualize ARGS...       # make visualizer, then run it with ARGS
```

## Algorithm

### Stack implementation

The two stacks are implemented as fixed-capacity ring buffers
(`t_stack` in `src/stacks.h`):
rotations and pushes move a `head` index modulo capacity.
Not a grading criteria
but avoids costly linked lists
and copying array elements,
so it technically keeps every operation O(1).

### Sorting algorithm

Using 500 random values as a benchmark,
my goal was to get the number of moves
as low as possible.

After researching different solutions
and algorithms
both for sorting in general
and push_swap in specific
I came to an important realization:
For push_swap,
only the operations allowed for MOVING
the data are benchmarked
everything else does **not** add to the time complexity.
Traversing the stacks to gain knowledge of them is free,
precomputing different solutions is free
and memory for anything besides the input data
isn't constrained either.

#### Main algorithm

To leverage this exact strength
I chose a **Longest Increasing Subsequence (LIS)** based algorithm.

The sorting works as follows

1. Compute the LIS of `a`
   via O(n²) DP with parent pointers
   (`src/sort/algo/n_algo/lis_tabulation.c`).
1. Elements belonging to the LIS stay on `a` and only get rotated;
   every other element is pushed to `b`.
1. Elements are then reinserted from `b` into `a`
   at their minimum-cost position,
   where cost is the combined rotations needed on both stacks
   to align a value with its correct slot.
1. A final rotation realigns `a`
   so the smallest element is at the top.

#### 3-5 numbers

To my knowledge before turning in,
the evaluation checks for a different number of inputs
prior to the 100 and 500 benchmarks.

These include 3 and 5 inputs,
for some permutations of which
LIS performs below the maximum expected
number of moves.

For n=3 the program therefore calculates the target index of each input number
and then applies the optimal set of moves for any n = 3 permutation.
For 3 < n \<= 5,
it pushes the smallest number(s) onto stack b,
before running the 3 sort
and merging b back into a.

### References

[1] "Big O Notation," *GeeksforGeeks*. Accessed: Apr. 03, 2026. [Online]. Available: <https://www.geeksforgeeks.org/dsa/analysis-algorithms-big-o-analysis/>

[2] "Bubble Sort," *GeeksforGeeks*. Accessed: Apr. 17, 2026. [Online]. Available: <https://www.geeksforgeeks.org/dsa/bubble-sort-algorithm/>

[3] "cxx-pflR1: The Pitchfork Layout (PFL)." Accessed: Mar. 26, 2026. [Online]. Available: <https://joholl.github.io/pitchfork-website/>

[4] J. L. Bentley and M. D. McIlroy, "Engineering a sort function," *Softw Pract Exp*, vol. 23, no. 11, pp. 1249–1265, Nov. 1993, doi: [10.1002/spe.4380231105](https://doi.org/10.1002/spe.4380231105).

[5] G. Martinez, *gemartin99/Push-Swap-Tester*. (Apr. 14, 2026). Shell. Accessed: Apr. 16, 2026. [Online]. Available: <https://github.com/gemartin99/Push-Swap-Tester>

[6] LeoFu9487, *LeoFu9487/push_swap_tester*. (Feb. 17, 2026). C. Accessed: Apr. 16, 2026. [Online]. Available: <https://github.com/LeoFu9487/push_swap_tester>

[7] "Longest Increasing Subsequence in C," *GeeksforGeeks*. Accessed: Apr. 03, 2026. [Online]. Available: <https://www.geeksforgeeks.org/c/longest-increasing-subsequence-in-c/>

[8] E. Ruaud, *o-reo/push_swap_visualizer*. (Apr. 09, 2026). C++. Accessed: Apr. 16, 2026. [Online]. Available: <https://github.com/o-reo/push_swap_visualizer>

[9] A. Y. Ogun, "Push Swap — A journey to find most efficient sorting algorithm," *Medium*. Accessed: Mar. 25, 2026. [Online]. Available: <https://medium.com/@ayogun/push-swap-c1f5d2d41e97>

[10] U. Gerkens, "Push Swap in less than 4200 operations," *Medium*. Accessed: Apr. 01, 2026. [Online]. Available: <https://medium.com/@ulysse.gks/push-swap-in-less-than-4200-operations-c292f034f6c0>

[11] M. Cerchi, *push_swap*. (Mar. 30, 2026). C. Accessed: Apr. 04, 2026. [Online]. Available: <https://github.com/sisittu99/push_swap>

[12] Y. Deng, "Push_Swap Turk algorithm explained in 6 steps," *Medium*. Accessed: Apr. 01, 2026. [Online]. Available: <https://pure-forest.medium.com/push-swap-turk-algorithm-explained-in-6-steps-4c6650a458c0>

[13] "Quicksort," *Wikipedia*. Feb. 28, 2026. Accessed: Apr. 03, 2026. [Online]. Available: <https://en.wikipedia.org/w/index.php?title=Quicksort&oldid=1341007678>

[14] CodeSlate, *Quicksort: How to choose the pivot (Animated!)*, (Jul. 12, 2024). Accessed: Apr. 03, 2026. [Online Video]. Available: <https://www.youtube.com/watch?v=dqNuN6zzYug>

### AI usage

Claude Opus 4.7
was used for gruntwork tasks, like:

- refactoring (e.g. update argument structures of functions across files)
- Edit/correct sections of the readme
- Convert Zotero's reference formatting to markdown
