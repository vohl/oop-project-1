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

#define TESTRUN 1

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----
#if TESTRUN
TEST(CollatzFixture, read) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}


//Additional tests for read
TEST(CollatzFixture, reada_2) {
    string as1("051 012\n");
    const pair<int, int> ap1 = collatz_read(as1);
    ASSERT_EQ(51, ap1.first);
    ASSERT_EQ(12, ap1.second);
}

TEST(CollatzFixture, reada_3) {
    string as2("15.3 2.5837274");
    const pair<int, int> ap2 = collatz_read(as2);
    ASSERT_EQ(15, ap2.first);
    ASSERT_EQ(0, ap2.second);    
}


// ----
// eval
// ----

TEST(CollatzFixture, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(CollatzFixture, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(CollatzFixture, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(CollatzFixture, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}


//Additional tests for eval
TEST(CollatzFixture, evala_5) {
    const int v = collatz_eval(1, 1);
    ASSERT_EQ(1, v);}

TEST(CollatzFixture, evala_6) {
    const int v = collatz_eval(1, 4);
    ASSERT_EQ(8, v);}

TEST(CollatzFixture, evala_7) {
    const int v = collatz_eval(22, 22);
    ASSERT_EQ(16, v);}
TEST(CollatzFixture, evala_8){
    const int v = collatz_eval(500000, 100000);
    ASSERT_EQ(449, v);}



// -----
// print
// -----

TEST(CollatzFixture, print) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

//Additional tests for print
TEST(CollatzFixture, printa_2) {
    ostringstream w;
    collatz_print(w, 1, 1, 60);
    ASSERT_EQ("1 1 60\n", w.str());}

TEST(CollatzFixture, printa_3) {
    ostringstream w;
    collatz_print(w, 10, 100, 10000);
    ASSERT_EQ("10 100 10000\n", w.str());}

// -----
// solve
// -----

TEST(CollatzFixture, solve) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

//Additional tests for solve
TEST(CollatzFixture, solvea_2) {
    istringstream r("1 3\n1 1\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 3 8\n1 1 1\n", w.str());}

TEST(CollatzFixture, solvea_3) {
    istringstream r("56985 241493\n719699 902065\n414040 111247\n438423 198281\n276584 108807\n180806 554663\n573689 668307\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("56985 241493 443\n719699 902065 525\n414040 111247 449\n438423 198281 449\n276584 108807 443\n180806 554663 470\n573689 668307 509\n", w.str());}

#endif
    
//overflow on the int while calculating for n
/*
TEST(CollatzFixture, solvea_3) {
    istringstream r("0 1000000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("0 1000000 525\n", w.str());}   
*/
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
