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

TEST(CollatzFixture, read_1) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);
}

TEST(CollatzFixture, read_2) {
    string s("111 555\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(111, p.first);
    ASSERT_EQ(555, p.second);
}

TEST(CollatzFixture, read_3) {
    string s("10 11 12\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 10, p.first);
    ASSERT_EQ(11, p.second);
}


// ----
// cycle_length //FUNCTION DEFINED IN MY CODE ONLY
// ----
/*
TEST(CollatzFixture, len_1) {
    ASSERT_EQ(31, cycle_length(555));
}

TEST(CollatzFixture, len_2) {
    ASSERT_EQ(27, cycle_length(33));
}

TEST(CollatzFixture, len_3) {
    ASSERT_EQ(55, cycle_length(956));
}

TEST(CollatzFixture, len_4) {
    ASSERT_EQ(26, cycle_length(101));
}
*/


// ----
// eval
// ----

TEST(CollatzFixture, eval_1) {
    ASSERT_EQ(20, collatz_eval(1, 10));
}

TEST(CollatzFixture, eval_2) {
    ASSERT_EQ(125, collatz_eval(100, 200));
}

TEST(CollatzFixture, eval_3) {
    ASSERT_EQ(89, collatz_eval(201, 210));
}

TEST(CollatzFixture, eval_4) {
    ASSERT_EQ(174, collatz_eval(900, 1000));
}

//backwards input
TEST(CollatzFixture, eval_5) {
    ASSERT_EQ(174, collatz_eval(1000, 900));
}

//backwards input
TEST(CollatzFixture, eval_6) {
    ASSERT_EQ(89, collatz_eval(210, 201));
}

//tests all possible values
TEST(CollatzFixture, eval_7) {
    ASSERT_EQ(476, collatz_eval(1, 999999));
}

//tests all possible values, backwards
TEST(CollatzFixture, eval_8) {
    ASSERT_EQ(476, collatz_eval(999999, 1));
}

TEST(CollatzFixture, eval_9) {
    ASSERT_EQ(67, collatz_eval(98475, 98475));
}

TEST(CollatzFixture, eval_10) {
    ASSERT_EQ(17, collatz_eval(7, 7));
}


// -----
// print
// -----

TEST(CollatzFixture, print_1) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());
}

TEST(CollatzFixture, print_2) {
    ostringstream w;
    collatz_print(w, 49, 555, 111);
    ASSERT_EQ("49 555 111\n", w.str());
}

TEST(CollatzFixture, print_3) {
    ostringstream w;
    collatz_print(w, 1, 2, 3);
    ASSERT_EQ("1 2 3\n", w.str());
}

// -----
// solve
// -----

TEST(CollatzFixture, solve_1) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());
}

TEST(CollatzFixture, solve_2) {

    istringstream r("920560 922657\n1000 900\n1252 2252\n2252 3252\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("920560 922657 445\n1000 900 174\n1252 2252 183\n2252 3252 217\n", w.str());
}

TEST(CollatzFixture, solve_3) {
    istringstream r("2 1\n7252 8252\n6252 7252\n4252 5252\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("2 1 2\n7252 8252 252\n6252 7252 257\n4252 5252 215\n", w.str());
}

TEST(CollatzFixture, solve_4) {
    istringstream r("1 2\n8252 7252\n7252 6252\n5252 4252\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 2 2\n8252 7252 252\n7252 6252 257\n5252 4252 215\n", w.str());
}


/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz                                         >  TestCollatz.out 2>&1
% gcov -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.out
% gcov -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.out



% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
*/
