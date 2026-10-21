#include <stdio.h>

#define GRADE_COUNT 5

// adds grades and divides by how many there are
double calculateAverage(const double grades[], int count)
{
    double total = 0.0;
    int i;

    for (i = 0; i < count; i++) {
        total += grades[i];
    }

    return total / count;
}

// matches average to a letter grade
char findLetterGrade(double average)
{
    if (average >= 90.0) {
        return 'A';
    } else if (average >= 80.0) {
        return 'B';
    } else if (average >= 70.0) {
        return 'C';
    } else if (average >= 60.0) {
        return 'D';
    }

    return 'F';
}

int main(void)
{
    double grades[GRADE_COUNT];
    double average;
    int i;

    printf("Grade Calculator\n");

    // gets all five grades
    for (i = 0; i < GRADE_COUNT; i++) {
        printf("Enter grade %d (0-100): ", i + 1);
        // only accepts numbers from 0 to 100
        if (scanf("%lf", &grades[i]) != 1 ||
            grades[i] < 0.0 || grades[i] > 100.0) {
            printf("Invalid grade.\n");
            return 1;
        }
    }

    average = calculateAverage(grades, GRADE_COUNT);
    printf("Average: %.2f\n", average);
    printf("Letter grade: %c\n", findLetterGrade(average));

    return 0;
}
