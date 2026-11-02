# CS101 C Exercises

CS101 project exercises, pointer classwork, and the class gradebook assignment in one CMake project.

| Directory | Program |
| --- | --- |
| `smart-calculator` | Arithmetic calculator |
| `grade-calculator` | Average and letter grade calculator |
| `number-guessing-game` | Number guessing game (fixed number: 42) |
| `tic-tac-toe` | Two-player tic-tac-toe |
| `hangman-game` | Hangman (fixed word: CAT) |
| `voting-project` | Voting terminal for four candidates |
| `hotel-management` | Room availability, check-in, checkout, and billing |
| `pointer-classwork` | Pointer access, assignment, and swapping |
| `gradebook` | Class gradebook using pointers and a 2D array |

## Build and run

Requires CMake 3.16 or newer and a C11 compiler.

```sh
cmake -S . -B build
cmake --build build
./build/pointer_classwork
```

Other executables: `smart_calculator`, `grade_calculator`,
`number_guessing_game`, `tic_tac_toe`, `hangman_game`, `voting_example`,
`hotel_management`, and `gradebook`.

For CLion, open this repository's root directory as a CMake project.
Individual exercise READMEs also include standalone compiler commands.

## Gradebook assignment

- [Program](gradebook/gradebook.c)
- [Part 1 and Part 2 self-check answers](gradebook/gradebook_study_answers.txt)

Run the assignment with `./build/gradebook` after building. The answer file is for study; the instructor requests just the code for submission.
