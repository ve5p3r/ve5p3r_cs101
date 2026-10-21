#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROOM_COUNT 5
#define GUEST_NAME_SIZE 50
#define CARD_DIGITS 16

// Read a whole line so leftover input cannot become the next menu choice resolving bug
// Return 1 for success, 0 for end of input, and -1 for a line that is too long.
int readLine(char text[], int size)
{
    int ch;

    if (fgets(text, size, stdin) == NULL) {
        return 0;
    }
    if (strchr(text, '\n') == NULL) {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return -1;
        }
    }
    text[strcspn(text, "\r\n")] = '\0';
    return 1;
}

// Keep asking until a whole number in the allowed range is entered.
int readNumber(const char prompt[], int minimum, int maximum, int *number)
{
    char line[80];
    char *end;
    long value;
    int result;

    for (;;) {
        printf("%s", prompt);
        result = readLine(line, sizeof(line));
        if (result == 0) {
            return 0;
        }
        if (result == 1) {
            errno = 0;
            value = strtol(line, &end, 10);
            if (end != line && errno == 0) {
                while (isspace((unsigned char)*end)) {
                    end++;
                }
                if (*end == '\0' && value >= minimum && value <= maximum) {
                    *number = (int)value;
                    return 1;
                }
            }
        }
        printf("Please enter a whole number from %d to %d.\n", minimum, maximum);
    }
}

void showRooms(const int roomNumbers[], const int nightlyRates[], const int occupied[])
{
    int i;

    printf("\nRooms\n");
    for (i = 0; i < ROOM_COUNT; i++) {
        printf("Room %d - $%d per night - %s\n", roomNumbers[i],
               nightlyRates[i], occupied[i] ? "Occupied" : "Available");
    }
}

int checkIn(int roomIndex, const int roomNumbers[], int occupied[],
            char guests[][GUEST_NAME_SIZE], int nights[])
{
    char guest[GUEST_NAME_SIZE];
    int stayLength;
    int result;

    if (occupied[roomIndex]) {
        printf("That room is already occupied.\n");
        return 1;
    }
    for (;;) {
        printf("Guest name: ");
        result = readLine(guest, sizeof(guest));
        if (result == 0) {
            return 0;
        }
        if (result == 1 && guest[strspn(guest, " \t")] != '\0') {
            break;
        }
        printf("Enter a guest name of 1 to 49 characters.\n");
    }
    if (!readNumber("Number of nights (1-365): ", 1, 365, &stayLength)) {
        return 0;
    }

    strcpy(guests[roomIndex], guest);
    nights[roomIndex] = stayLength;
    occupied[roomIndex] = 1;
    printf("Checked in %s to room %d for %d night(s).\n",
           guests[roomIndex], roomNumbers[roomIndex], nights[roomIndex]);
    return 1;
}

// check the format, then pretend the payment was approved.
int processPayment(int amount)
{
    // A character array keeps leading zeros, unlike an int.
    // The extra spaces hold a newline and the end-of-string character.
    char cardNumber[CARD_DIGITS + 2];
    int result;
    int valid;
    int count;

    printf("Simulated payment only. Use a made-up card number.\n");
    do {
        printf("Enter 16 card digits (no spaces or dashes): ");
        result = readLine(cardNumber, sizeof(cardNumber));
        if (result == 0) {
            printf("Payment not completed. Room remains occupied.\n");
            return 0;
        }

        valid = 1; // 1 means valid; 0 means invalid.
        if (result == -1) {
            valid = 0; // The input was too long for the array.
        }

        // Start at position 0 and stop at '\0', which ends a string.
        count = 0;
        while (cardNumber[count] != '\0') {
            if (cardNumber[count] < '0' || cardNumber[count] > '9') {
                valid = 0;
            }
            count++;
        }
        if (count != CARD_DIGITS) {
            valid = 0;
        }
        if (valid == 0) {
            printf("Please enter exactly 16 digits.\n");
        }
    } while (valid == 0);

    printf("Simulated payment approved: $%d. No real charge was made.\n", amount);
    return 1;
}

int checkOut(int roomIndex, const int roomNumbers[], const int nightlyRates[],
              int occupied[], char guests[][GUEST_NAME_SIZE], int nights[])
{
    int total;

    if (!occupied[roomIndex]) {
        printf("That room is already available.\n");
        return 1;
    }
    total = nights[roomIndex] * nightlyRates[roomIndex];
    printf("\nGuest: %s\nRoom: %d\n", guests[roomIndex], roomNumbers[roomIndex]);
    printf("%d night(s) at $%d per night\n", nights[roomIndex], nightlyRates[roomIndex]);
    printf("Total bill: $%d\n", total);

    if (!processPayment(total)) {
        return 0;
    }

    occupied[roomIndex] = 0;
    guests[roomIndex][0] = '\0';
    nights[roomIndex] = 0;
    printf("Room %d is now available.\n", roomNumbers[roomIndex]);
    return 1;
}

int main(void)
{
    // Matching positions in these parallel arrays describe the same room.
    const int roomNumbers[ROOM_COUNT] = {101, 102, 103, 104, 105};
    const int nightlyRates[ROOM_COUNT] = {100, 100, 150, 150, 200};
    int occupied[ROOM_COUNT] = {0};
    char guests[ROOM_COUNT][GUEST_NAME_SIZE] = {""};
    int nights[ROOM_COUNT] = {0};
    int choice;
    int roomNumber;
    int roomIndex;

    printf("Hotel Management System\n");
    for (;;) {
        printf("\n1. List rooms\n2. Check in\n3. Check out\n4. Quit\n");
        if (!readNumber("Choose an option: ", 1, 4, &choice) || choice == 4) {
            break;
        }
        if (choice == 1) {
            showRooms(roomNumbers, nightlyRates, occupied);
            continue;
        }
        if (!readNumber("Room number (101-105): ", 101, 105, &roomNumber)) {
            break;
        }
        // Room numbers start at 101; array positions start at zero.
        roomIndex = roomNumber - 101;
        if (choice == 2) {
            if (!checkIn(roomIndex, roomNumbers, occupied, guests, nights)) {
                break;
            }
        } else {
            if (!checkOut(roomIndex, roomNumbers, nightlyRates, occupied, guests, nights)) {
                break;
            }
        }
    }
    printf("Goodbye.\n");
    return 0;
}
