# Netflix Recommendation Assistant (C++)

LDCW6123 Group Project - Part 2. Inspired by Netflix (Part 1 poster).

## Plan
**Purpose:** suggest a Netflix Original based on what the user feels like watching.

**Inputs:** main-menu choice, genre (7 options), format (movie / series / either).

**Outputs:** a suggested title with type, year, genre and a one-line description.

**Logic:** `switch` for menus and genre mapping, `if / else` for the format filter,
loops for repeating the menu and for "another suggestion".

## How to build and run
```
g++ -std=c++11 -Wall -Wextra -o netflix_finder main.cpp
./netflix_finder          # on Windows: netflix_finder.exe
```

## Features
1. Find a movie or series by genre (7 genres) and format (movie / series / either)
2. "Another suggestion" loop - matches are shuffled and never repeat
3. Surprise Me - random pick from the whole catalogue
4. Netflix timeline - stages match the Part 1 poster
5. Input validation - letters, symbols and out-of-range numbers are rejected politely

## Tests
`./tests/run_tests.sh` runs 12 automated cases (see `tests/test_cases.md`).
