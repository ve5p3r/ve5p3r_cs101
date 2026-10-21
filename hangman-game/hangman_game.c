#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_MISSES 6

// hides letters that havent been guessed yet
void showWord(const char word[], const int guessedLetters[])
{
    size_t i;

    for (i = 0; i < strlen(word); i++) {
        int letterIndex = word[i] - 'A';

        if (guessedLetters[letterIndex]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// checks if every letter in the word was guessed
int wordIsComplete(const char word[], const int guessedLetters[])
{
    size_t i;

    for (i = 0; i < strlen(word); i++) {
        if (!guessedLetters[word[i] - 'A']) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    // uses the same word
    const char word[] = "CAT";
    // keeps track of guesses from A to Z
    int guessedLetters[26] = {0};
    int misses = 0;
    char guess;

    printf("Hangman Game\n");

    while (misses < MAX_MISSES && !wordIsComplete(word, guessedLetters)) {
        int letterIndex;

        showWord(word, guessedLetters);
        printf("Misses: %d of %d\n", misses, MAX_MISSES);
        printf("Enter a letter: ");

        if (scanf(" %c", &guess) != 1 || !isalpha((unsigned char)guess)) {
            printf("Invalid letter.\n");
            return 1;
        }

        // makes lowercase and uppercase guesses count the same for caps-insensitivity
        guess = (char)toupper((unsigned char)guess);
        letterIndex = guess - 'A';

        // repeated guesses do not count as misses
        if (guessedLetters[letterIndex]) {
            printf("You already guessed %c.\n", guess);
            continue;
        }

        guessedLetters[letterIndex] = 1;
        // counts a miss when the letter is not in the word
        if (strchr(word, guess) == NULL) {
            misses++;
            printf("%c is not in the word.\n", guess);
        }
    }

    showWord(word, guessedLetters);
    if (wordIsComplete(word, guessedLetters)) {
        printf("You won! The word was %s.\n", word);
    } else {
        printf("You lost. The word was %s.\n", word);
    }

    return 0;
}
