#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROOM_COUNT 5

struct Room {
    int number;
    int nightlyRate;
    int occupied;
    char guest[50];
    int nights;
};

// Read a whole line so leftover input cannot become the next menu choice.
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

void showRooms(const struct Room rooms[])
{
    int i;

    printf("\nRooms\n");
    for (i = 0; i < ROOM_COUNT; i++) {
        printf("Room %d - $%d per night - %s\n", rooms[i].number,
               rooms[i].nightlyRate, rooms[i].occupied ? "Occupied" : "Available");
    }
}

int checkIn(struct Room *room)
{
    char guest[50];
    int nights;
    int result;

    if (room->occupied) {
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
    if (!readNumber("Number of nights (1-365): ", 1, 365, &nights)) {
        return 0;
    }

    strcpy(room->guest, guest);
    room->nights = nights;
    room->occupied = 1;
    printf("Checked in %s to room %d for %d night(s).\n",
           room->guest, room->number, room->nights);
    return 1;
}

void checkOut(struct Room *room)
{
    if (!room->occupied) {
        printf("That room is already available.\n");
        return;
    }
    printf("\nGuest: %s\nRoom: %d\n", room->guest, room->number);
    printf("%d night(s) at $%d per night\n", room->nights, room->nightlyRate);
    printf("Total bill: $%d\n", room->nights * room->nightlyRate);

    room->occupied = 0;
    room->guest[0] = '\0';
    room->nights = 0;
    printf("Room %d is now available.\n", room->number);
}

int main(void)
{
    struct Room rooms[ROOM_COUNT] = {
        {101, 100, 0, "", 0},
        {102, 100, 0, "", 0},
        {103, 150, 0, "", 0},
        {104, 150, 0, "", 0},
        {105, 200, 0, "", 0}
    };
    int choice;
    int roomNumber;

    printf("Hotel Management System\n");
    for (;;) {
        printf("\n1. List rooms\n2. Check in\n3. Check out\n4. Quit\n");
        if (!readNumber("Choose an option: ", 1, 4, &choice) || choice == 4) {
            break;
        }
        if (choice == 1) {
            showRooms(rooms);
            continue;
        }
        if (!readNumber("Room number (101-105): ", 101, 105, &roomNumber)) {
            break;
        }
        // Room numbers start at 101; array positions start at zero.
        if (choice == 2) {
            if (!checkIn(&rooms[roomNumber - 101])) {
                break;
            }
        } else {
            checkOut(&rooms[roomNumber - 101]);
        }
    }
    printf("Goodbye.\n");
    return 0;
}
