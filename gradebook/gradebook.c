#include <stdio.h>

// table init
void printTable(int scores[][3])
{
    int student, test;
    printf("Student  Test1  Test2  Test3\n");
    for (student = 0; student < 4; student++) {
        printf("%-7d", student + 1);
        for (test = 0; test < 3; test++) {
            printf("%7d", scores[student][test]);
        }
        printf("\n");
    }
}

// gets the average for one student
double studentAverage(const int *row)
{
    int test;
    int total = 0;
    for (test = 0; test < 3; test++) {
        total += *(row + test);
    }
    return total / 3.0;
}

// all averages
void printStudentAverages(int scores[][3])
{
    int student;
    printf("\nStudent averages:\n");
    for (student = 0; student < 4; student++) {
        printf("Student %d: %.2f\n", student + 1,
               studentAverage(scores[student]));
    }
}

void printTestAverages(int scores[][3])
{
    int student, test, total;
    printf("\nTest averages:\n");
    for (test = 0; test < 3; test++) {
        total = 0;
        for (student = 0; student < 4; student++) {
            total += scores[student][test];
        }
        printf("Test %d: %.2f\n", test + 1, total / 4.0);
    }
}

// uses pointers to return the highest score, student, and test
void findHighest(int scores[][3], int *best, int *student, int *test)
{
    int row, column;
    *best = scores[0][0];
    *student = 1;
    *test = 1;
    for (row = 0; row < 4; row++) {
        for (column = 0; column < 3; column++) {
            if (scores[row][column] > *best) {
                *best = scores[row][column];
                *student = row + 1;
                *test = column + 1;
            }
        }
    }
    printf("\nHighest score: %d (Student %d, Test %d)\n",
           *best, *student, *test);
}

void addBonus(int scores[][3])
{
    int student;
    for (student = 0; student < 4; student++) {
        scores[student][2] += 5;
        if (scores[student][2] > 100) {
            scores[student][2] = 100;
        }
    }
}

void printAfterBonus(int scores[][3])
{
    printf("\nAfter adding 5 bonus points to Test 3:\n");
    printTable(scores);
}

int main(void)
{
    int scores[4][3] = {
        {78, 85, 92},
        {64, 70, 58},
        {90, 88, 97},
        {55, 61, 73}
    };
    int best, student, test;

    printTable(scores);
    printStudentAverages(scores);
    printTestAverages(scores);
    findHighest(scores, &best, &student, &test);
    addBonus(scores);
    printAfterBonus(scores);

    return 0;
}
