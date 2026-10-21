# Hotel Management System

CS101 C study exercise. This is an authored practice draft for review, not a
recovered instructor solution or a submitted assignment. Check against the
actual course prompt before using it for submission.

Uses functions, parallel arrays, and a menu to manage five rooms:

- List rooms, nightly rates, and availability.
- Check a guest into an available room for 1–365 nights.
- Display the bill, simulate a card payment, and check the guest out.

Room numbers, nightly rates, occupancy, and nights stayed each have a
one-dimensional array. Guest names use a two-dimensional character array, with
one row per room. The same index identifies a room across all arrays: index `0`
holds room `101`, through index `4` for room `105`. Check-in fills that room's
guest name and stay length and marks it occupied; checkout calculates its bill
and clears those entries after simulated payment so the room can be reused.

Guest names may contain spaces and must be 1–49 characters. Room and guest data
are held in memory and reset when the program exits. Rates are fixed whole-dollar
amounts; this exercise does not calculate taxes or process real payments.

At checkout, enter a made-up 16-digit card number such as `0000111122223333`.
The number is held in a local character array so leading zeros are preserved.
A `while` loop counts the characters and checks that each is a digit. A separate
`if` checks that the count is 16. A `do...while` loop asks again when the input is
invalid. Spaces and dashes are not accepted. Any number matching that format gets a
simulated approval; no bank or card-validity check takes place. The program does
not save or print the card number. Invalid input prompts again; ending input
before approval leaves the room unchanged and exits the program.

## Build and run

```sh
cc -std=c11 -Wall -Wextra -Wpedantic hotel_management.c -o hotel-management
./hotel-management
```

From the repository root, build with CMake and run `./build/hotel_management`.
