#include <stdio.h>

/* C Pointer Classwork - October 19, 2026
 *
 * 1. What is a pointer?
 *    A pointer is a variable that stores a memory address.
 *
 * 2. What is the purpose of &?
 *    It gets the address of a variable, so &score is the address of score.
 *
 * 3. What does *ptr mean?
 *    It accesses the value stored at the address held by ptr.
 *
 * 4. Why do &score and ptr contain the same address?
 *    We set ptr to &score, so ptr holds the address of score.
 *
 * 5. Why does assigning to *ptr change score?
 *    ptr points to score, so *ptr and score access the same int.
 */

int main(void)
{
    int score = 80;
    int *ptr = &score;
    int num1 = 10;
    int num2 = 20;
    int *ptr1 = &num1;
    int *ptr2 = &num2;
    int temp;

    printf("Score before update: %d\n", score);
    printf("Address of score (&score): %p\n", (void *)&score);
    printf("Address stored in ptr: %p\n", (void *)ptr);
    printf("Value at ptr (*ptr): %d\n", *ptr);

    // ptr points to score, so this writes 95 into score's memory.
    *ptr = 95;
    printf("Score after *ptr = 95: %d\n", score);

    printf("\nBefore swap: num1 = %d, num2 = %d\n", num1, num2);

    // Keep the first value while moving the second one into its place.
    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;

    printf("After swap: num1 = %d, num2 = %d\n", num1, num2);

    return 0;
}
