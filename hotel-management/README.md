# Hotel Management System

CS101 C study exercise. This is an authored practice draft for review, not a
recovered instructor solution or a submitted assignment. Check against the
actual course prompt before using it for submission.

Uses functions, an array of structures, and a menu to manage five rooms:

- List rooms, nightly rates, and availability.
- Check a guest into an available room for 1–365 nights.
- Check a guest out, display the bill, and make the room available again.

Guest names may contain spaces and must be 1–49 characters. Room and guest data
are held in memory and reset when the program exits. Rates are fixed whole-dollar
amounts; this exercise does not calculate taxes or process payments.

## Build and run

```sh
cc -std=c11 -Wall -Wextra -Wpedantic hotel_management.c -o hotel-management
./hotel-management
```

From the repository root, build with CMake and run `./build/hotel_management`.
