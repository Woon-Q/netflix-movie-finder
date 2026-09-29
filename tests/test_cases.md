# Test Cases - Netflix Recommendation Assistant

Run all cases with `./tests/run_tests.sh`. Inputs are typed automatically, in order.

| ID  | Scenario                              | Input sequence      | Expected result                                   |
|-----|---------------------------------------|---------------------|---------------------------------------------------|
| T01 | Exit straight away                    | 4                   | Goodbye message                                   |
| T02 | Action + Movie                        | 1, 1, 1, 4          | Action movie shown                                |
| T03 | Romance + Series                      | 1, 6, 2, 2, 4       | Romance series shown                              |
| T04 | Documentary + Either                  | 1, 7, 3, 2, 4       | Documentary title shown                           |
| T05 | Letters typed at main menu            | abc, 4              | "Invalid input" message, then menu asks again     |
| T06 | Out-of-range number                   | 9, 4                | "Invalid input" message, then menu asks again     |
| T07 | Keep asking "another" until exhausted | 1, 2, 2, 1, 4       | "That's every match" (Comedy series has 2 titles) |
| T08 | Timeline - Streaming                  | 3, 3, 4             | Shows the 2007 streaming launch                   |
| T09 | Timeline - back                       | 3, 7, 4             | Returns to main menu                              |
| T10 | Surprise me                           | 2, 4                | A random title is displayed                       |
| T11 | Input stream ends (EOF)               | (no input)          | Program exits cleanly with a message              |
| T12 | Session counter                       | 2, 2, 4             | "2 recommendation(s)" in the goodbye message      |
