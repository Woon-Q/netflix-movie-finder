#!/bin/bash
# Automated tests for the Netflix Recommendation Assistant.
# Usage:  ./tests/run_tests.sh | tee tests/test_results.txt
cd "$(dirname "$0")/.." || exit 1
g++ -std=c++11 -Wall -Wextra -o netflix_finder main.cpp || { echo "Compile failed"; exit 1; }

pass=0; fail=0
# run_test <id> <description> <input to type> <text(s) expected, separated by |>
run_test() {
    local id="$1" desc="$2" input="$3" patterns="$4" ok=1 output p
    output=$(printf "$input" | ./netflix_finder 2>&1)
    IFS='|' read -ra pats <<< "$patterns"
    for p in "${pats[@]}"; do
        grep -qF -- "$p" <<< "$output" || ok=0
    done
    if [ $ok -eq 1 ]; then echo "PASS  $id  $desc"; pass=$((pass+1))
    else echo "FAIL  $id  $desc"; fail=$((fail+1)); fi
}

echo "Netflix Recommendation Assistant - test run"
echo "-------------------------------------------"
run_test T01 "Exit straight away"                     "4\n"                 "Goodbye and happy streaming!"
run_test T02 "Action movie recommendation"            "1\n1\n1\n4\n"        "Genre : Action|Type  : Movie"
run_test T03 "Romance series recommendation"          "1\n6\n2\n2\n4\n"     "Genre : Romance|Type  : Series"
run_test T04 "Documentary, either format"             "1\n7\n3\n2\n4\n"     "Genre : Documentary"
run_test T05 "Letters typed at main menu"             "abc\n4\n"            "Invalid input"
run_test T06 "Number out of range (9)"                "9\n4\n"              "Invalid input"
run_test T07 "Ask for another until list runs out"    "1\n2\n2\n1\n4\n"     "That's every match"
run_test T08 "Timeline - Streaming stage"             "3\n3\n4\n"           "[2007]"
run_test T09 "Timeline - back to menu"                "3\n7\n4\n"           "Goodbye and happy streaming!"
run_test T10 "Surprise me shows a title"              "2\n4\n"              "Title :"
run_test T11 "Input ends unexpectedly (EOF)"          ""                    "No more input"
run_test T12 "Session counter reports 2 picks"        "2\n2\n4\n"           "2 recommendation(s)"
echo "-------------------------------------------"
echo "Passed: $pass   Failed: $fail"
[ $fail -eq 0 ]
