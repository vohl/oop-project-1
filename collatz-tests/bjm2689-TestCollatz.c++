// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Collatz.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

// Test normal parameters
TEST(CollatzFixture, read_1) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

// Test normal parameters
TEST(CollatzFixture, read_2) {
    string s("100 200\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(100, p.first);
    ASSERT_EQ(200, p.second);}

// Test reverse parameters
TEST(CollatzFixture, read_3) {
    string s("10 5\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(10, p.first);
    ASSERT_EQ( 5, p.second);}

// Test input with a lot of spaces
TEST(CollatzFixture, read_4) {
    string s("  1      2  \n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(1, p.first);
    ASSERT_EQ(2, p.second);}

// ----
// eval
// ----

// Test normal parameters
TEST(CollatzFixture, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

// Test normal parameters
TEST(CollatzFixture, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

// Test normal parameters
TEST(CollatzFixture, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

// Test normal parameters
TEST(CollatzFixture, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

// Test reverse parameters
TEST(CollatzFixture, eval_5) {
    const int v = collatz_eval(1000, 900);
    ASSERT_EQ(174, v);}

// Test inclusive parameters
TEST(CollatzFixture, eval_6) {
    const int v = collatz_eval(1, 2);
    ASSERT_EQ(2, v);}

// -----
// print
// -----

// Test normal parameters
TEST(CollatzFixture, print_1) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

// Test reverse parameters
TEST(CollatzFixture, print_2) {
    ostringstream w;
    collatz_print(w, 10, 1, 20);
    ASSERT_EQ("10 1 20\n", w.str());}

// Test parameters that are one apart
TEST(CollatzFixture, print_3) {
    ostringstream w;
    collatz_print(w, 1, 2, 2);
    ASSERT_EQ("1 2 2\n", w.str());}

// -----
// solve
// -----

// Test normal parameters
TEST(CollatzFixture, solve_1) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

// Test reverse parameters
TEST(CollatzFixture, solve_2) {
    istringstream r("10 1\n200 100\n210 201\n1000 900\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("10 1 20\n200 100 125\n210 201 89\n1000 900 174\n", w.str());}

// Test extraneous spaces
TEST(CollatzFixture, solve_3) {
    istringstream r(" 1     10  \n 100  200   \n  201  210\n  900   1000  \n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz                                         >  TestCollatz.out 2>&1
% gcov -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.out
% gcov -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.out



% cat TestCollatz.out
==26864== Memcheck, a memory error detector
==26864== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==26864== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==26864== Command: ./TestCollatz
==26864== 
Running main() from gtest_main.cc
[==========] Running 16 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 16 tests from CollatzFixture
[ RUN      ] CollatzFixture.read_1
[       OK ] CollatzFixture.read_1 (17 ms)
[ RUN      ] CollatzFixture.read_2
[       OK ] CollatzFixture.read_2 (2 ms)
[ RUN      ] CollatzFixture.read_3
[       OK ] CollatzFixture.read_3 (3 ms)
[ RUN      ] CollatzFixture.read_4
[       OK ] CollatzFixture.read_4 (2 ms)
[ RUN      ] CollatzFixture.eval_1
[       OK ] CollatzFixture.eval_1 (4 ms)
[ RUN      ] CollatzFixture.eval_2
[       OK ] CollatzFixture.eval_2 (1 ms)
[ RUN      ] CollatzFixture.eval_3
[       OK ] CollatzFixture.eval_3 (1 ms)
[ RUN      ] CollatzFixture.eval_4
[       OK ] CollatzFixture.eval_4 (2 ms)
[ RUN      ] CollatzFixture.eval_5
[       OK ] CollatzFixture.eval_5 (2 ms)
[ RUN      ] CollatzFixture.eval_6
[       OK ] CollatzFixture.eval_6 (2 ms)
[ RUN      ] CollatzFixture.print_1
[       OK ] CollatzFixture.print_1 (6 ms)
[ RUN      ] CollatzFixture.print_2
[       OK ] CollatzFixture.print_2 (2 ms)
[ RUN      ] CollatzFixture.print_3
[       OK ] CollatzFixture.print_3 (3 ms)
[ RUN      ] CollatzFixture.solve_1
[       OK ] CollatzFixture.solve_1 (8 ms)
[ RUN      ] CollatzFixture.solve_2
[       OK ] CollatzFixture.solve_2 (3 ms)
[ RUN      ] CollatzFixture.solve_3
[       OK ] CollatzFixture.solve_3 (3 ms)
[----------] 16 tests from CollatzFixture (69 ms total)

[----------] Global test environment tear-down
[==========] 16 tests from 1 test case ran. (98 ms total)
[  PASSED  ] 16 tests.
==26864== 
==26864== HEAP SUMMARY:
==26864==     in use at exit: 0 bytes in 0 blocks
==26864==   total heap usage: 493 allocs, 493 frees, 73,382 bytes allocated
==26864== 
==26864== All heap blocks were freed -- no leaks are possible
==26864== 
==26864== For counts of detected and suppressed errors, rerun with: -v
==26864== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
File 'Collatz.c++'
Lines executed:97.56% of 41
Branches executed:100.00% of 48
Taken at least once:62.50% of 48
Calls executed:74.07% of 27
Creating 'Collatz.c++.gcov'
File 'TestCollatz.c++'
Lines executed:100.00% of 65
Branches executed:61.72% of 418
Taken at least once:30.86% of 418
Calls executed:53.89% of 488
Creating 'TestCollatz.c++.gcov'
*/
