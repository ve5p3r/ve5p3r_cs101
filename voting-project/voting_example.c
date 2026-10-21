#include <stdio.h>

// keeps the details and vote count for each candidate
struct Candidate {
    char fName[50];
    char lName[50];
    int party;
    int votes;
};

// clears the rest of the input line
void clearInput(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

// shows the party name from its number
void printParty(int party)
{
    if (party == 1) {
        printf("Democrat");
    } else if (party == 2) {
        printf("Republican");
    } else {
        printf("Independent");
    }
}

// shows the total votes and each candidate's results
void showResults(struct Candidate candidates[], int totalVotes)
{
    int i;

    printf("\nTotal votes: %d out of 12\n", totalVotes);

    for (i = 0; i < 4; i++) {
        printf("%d. %s %s - ", i + 1,
               candidates[i].fName, candidates[i].lName);
        printParty(candidates[i].party);
        printf(": %d vote(s)\n", candidates[i].votes);
    }
}

int main(void)
{
    struct Candidate candidates[4];
    int i;
    int choice;
    int candidateNumber;
    int result;
    int totalVotes = 0;

    printf("DejiSoft Voting Terminal\n");
    printf("Please enter the details of the four candidates.\n");

    // gets the details for all four candidates
    for (i = 0; i < 4; i++) {
        candidates[i].votes = 0;

        printf("\nCandidate %d\n", i + 1);
        printf("First name: ");
        if (scanf("%49s", candidates[i].fName) != 1) {
            return 1;
        }
        clearInput();

        printf("Last name: ");
        if (scanf("%49s", candidates[i].lName) != 1) {
            return 1;
        }
        clearInput();

        do {
            printf("Party (1 Democrat, 2 Republican, 3 Independent): ");
            result = scanf("%d", &candidates[i].party);
            clearInput();

            if (result == EOF) {
                return 1;
            }

            if (result != 1 || candidates[i].party < 1 ||
                candidates[i].party > 3) {
                printf("Please enter 1, 2, or 3.\n");
                candidates[i].party = 0;
            }
        } while (candidates[i].party == 0);
    }

    // keeps showing the menu until the user quits or input ends
    do {
        printf("\n1. Vote\n");
        printf("2. Show results\n");
        printf("3. Quit\n");
        printf("Choose an option: ");
        result = scanf("%d", &choice);
        clearInput();

        if (result == EOF) {
            break;
        }

        if (result != 1) {
            choice = 0;
        }

        if (choice == 1) {
            // allows up to 12 votes in total
            if (totalVotes >= 12) {
                printf("The maximum of 12 votes has been reached.\n");
            } else {
                showResults(candidates, totalVotes);
                printf("Enter the candidate number to vote for: ");
                result = scanf("%d", &candidateNumber);
                clearInput();

                if (result == 1 && candidateNumber >= 1 &&
                    candidateNumber <= 4) {
                    // subtracts 1 because array positions start at 0
                    candidates[candidateNumber - 1].votes++;
                    totalVotes++;
                    printf("Your vote was recorded.\n");
                } else {
                    printf("That is not a valid candidate.\n");
                }
            }
        } else if (choice == 2) {
            showResults(candidates, totalVotes);
        } else if (choice != 3) {
            printf("Please choose 1, 2, or 3.\n");
        }
    } while (choice != 3);

    printf("\nFinal results:\n");
    showResults(candidates, totalVotes);

    return 0;
}
