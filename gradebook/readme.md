# Class Gradebook

CS101 assignment due November 2, before lecture.

- [gradebook.c](gradebook.c) — the program
- [Part 1 and Part 2 self-check answers](gradebook_study_answers.txt)

The program prints the scores, student averages, test averages, and highest score, then adds 5 points to Test 3 (up to 100) and prints the updated table.

## Build and run

From this folder:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic gradebook.c -o gradebook
./gradebook
```

In CLion, open the repository root and choose the `gradebook` run target.

The self-check answers are study notes. The instructor asks for just the code for submission.
