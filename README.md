# push_swap

Sorting a stack of integers in C using only eleven stack operations —
`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr` — with no
random access and no comparison beyond the top of each stack. The program does
not sort anything itself: it prints the sequence of operations that would, and
the score is how short that sequence is.

The algorithm is a cost-driven insertion sort. Every element but the last three
is pushed onto stack `b`, the remaining three are put in rotational order, and
then each element of `b` is priced: how many rotations of `a` to bring its
insertion point to the top, how many rotations of `b` to bring the element
itself to the top. Both counts are signed, so a rotation in either direction is
whichever is cheaper, and when the two signs agree the moves are merged into
`rr` or `rrr` and paid once instead of twice. The cheapest element is moved,
and the prices are recomputed from scratch on the next pass, since every move
changes them. A final rotation brings the smallest value to the top.

Stack `a` is kept sorted only up to rotation while `b` is being drained, never
fully sorted: that is what lets the insertion point be found as the single
descent in a circular sequence, and it is why the last rotation is needed at
all.

## How it works

A four-element run is short enough to follow end to end:

```
./push_swap 2 1 3 4   ->   pb ra pa rra

  start   a = [2, 1, 3, 4]   b = []
  pb      a = [1, 3, 4]      b = [2]
  ra      a = [3, 4, 1]      b = [2]
  pa      a = [2, 3, 4, 1]   b = []
  rra     a = [1, 2, 3, 4]   b = []
```

Everything but the last three goes to `b`, so `2` is pushed and `[1, 3, 4]` is
left. Those three are already in rotational order, so nothing is emitted for
them — a stack that reads `1, 3, 4` from the top needs no work, even though a
stack that reads `3, 4, 1` would look unsorted to a naive check.

Then `2` is priced. It belongs between `1` and `3`, so its insertion point is
the node holding `3`, one position down from the top: one `ra` on `a`. It is
already on top of `b`, so nothing on `b`. One rotation, then `pa`.

The two counts are **signed**, and that is the whole trick. A position in the
lower half of a stack is reported as a negative distance, meaning it is cheaper
to reach by rotating backwards: the closing `rra` is exactly that, since `1` sat
at the bottom and `rra` reaches it in one move where `ra` would have taken
three. When the two signs agree, the rotations on `a` and `b` happen in the same
direction and are merged into a single `rr` or `rrr`, paid once instead of
twice; when they disagree, the costs are added, because the two stacks have to
be turned separately.

The cheapest element of `b` wins, and every price is recomputed from scratch
afterwards, since moving one element shifts the position of all the others.

## Build and run

Requirements on the host: a C compiler and `make`. Nothing else, no external
libraries. The bundled `libft` is built first by the project's Makefile.

```bash
make          # push_swap
make bonus    # checker
make debug    # push_swap with debug symbols
make fclean   # removes the binaries, the library and the objects
```

```bash
# prints the operations, one per line
./push_swap 2 1 3 6 5 8

# count them
./push_swap 4 67 3 87 23 | wc -l

# checker reads operations on standard input and applies them to the stack,
# then prints OK if the result is sorted and b is empty, KO otherwise
./push_swap 4 67 3 87 23 | ./checker 4 67 3 87 23
```

Invalid arguments — non-integers, values outside the `int` range, duplicates —
print `Error` on standard error and produce no operations. With no arguments
the program prints nothing at all. `checker` also reports `Error` for an
instruction it does not recognise.

Measured over 600 random sets of each size, with the printed operations
replayed by an independent simulator and compared against the sorted input:

| Size | Mean | Median | Max | Limit |
|---|---|---|---|---|
| 100 | 582 | 581 | 664 | 700 |
| 500 | 5188 | 5189 | 5570 | 5500 |

At 100 numbers the result is always within the limit. At 500 it is not: the
mean leaves a 6% margin, but 1.3% of the sets measured here crossed 5500. The
cost function prices one element at a time and never reconsiders an earlier
choice, which is where those cases are lost; a chunk-based partition of `b`
would trade the extra bookkeeping for a tighter bound.

Correctness was checked exhaustively on every permutation of 1 to 8 elements
(46,233 cases) and on 1,600 random sets, in both cases by replaying the output
rather than by trusting the bundled `checker`. Compiled without warnings with
clang on macOS (arm64) and with gcc 12 on Debian (x86_64). Checked under
valgrind on Linux, including the error paths: no leaks, no invalid reads.

## Repository layout

```
.
├── push_swap.c              # entry point and the sort pipeline
├── push_swap.h
├── push_swap_bonus.h
├── algorithm/
│   ├── algorithm_1.c        # the cost of moving one element of b into a
│   ├── algorithm_2.c        # final rotation, signed position, cost bookkeeping
│   └── algorithm_3.c        # the three-element case, and paying a chosen cost
├── function/
│   ├── function_1.c         # sa, sb, ss
│   ├── function_2.c         # pa, pb
│   ├── function_3.c         # ra, rb, rr
│   └── function_4.c         # rra, rrb, rrr
├── utils/
│   ├── utils_1.c            # minimum, sortedness test, duplicate detection
│   └── utils_2.c            # list construction from argv, and teardown
├── bonus/
│   ├── checker.c            # reads operations on stdin, applies them, OK or KO
│   ├── function_bonus_1.c   # swap and push, silent and returning to the caller
│   └── function_bonus_2.c   # rotate and reverse rotate, same convention
└── libft/                   # the library, as published in redei-ma/libft
```

The operations are split across four files because the Norm allows five
functions per file; the numbering follows that constraint, not a hierarchy.
The bonus reimplements the same eleven operations rather than reusing
`function/`: those print their own name, which is the whole point in
`push_swap` and exactly wrong in `checker`, where the caller instead needs a
return value to tell a recognised instruction from an unknown one.

## Resources

References on the topic, for anyone reading the code and wanting the
background rather than the implementation:

- The 42 subject, which fixes the operation set, the error handling and the
  move-count limits the benchmark above is measured against.
- Knuth, *The Art of Computer Programming*, vol. 3, *Sorting and Searching*,
  on sorting as a cost problem rather than a correctness one — the distinction
  this project is built around.
- Chunk-based and radix approaches to the same exercise, which partition `b`
  into ranges instead of pricing one element at a time. They bound the worst
  case more tightly than the greedy choice used here, at the cost of carrying
  the partition around; the trade-off is the one noted under the benchmark.
