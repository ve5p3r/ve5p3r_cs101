#include <stdio.h>

// uses the same number
#define SECRET_NUMBER 42

int main(void)
{
    int guess;
    int attempts = 0;

    printf("Number Guessing Game\n");
    printf("Guess a number from 1 to 100.\n");

    // keeps asking until the guess is right
    do {
        printf("Enter your guess: ");
        if (scanf("%d", &guess) != 1) {
            printf("Invalid guess.\n");
            return 1;
        }

        attempts++;

        // tells user which way to guess next
        if (guess < SECRET_NUMBER) {
            printf("Too low.\n");
        } else if (guess > SECRET_NUMBER) {
            printf("Too high.\n");
        }
    } while (guess != SECRET_NUMBER);

    printf("Correct! You used %d attempt(s).\n", attempts);
    return 0;
}
