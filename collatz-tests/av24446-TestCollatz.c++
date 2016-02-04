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

TEST(CollatzFixture, read) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

//added tests
TEST(CollatzFixture, read_2) {
    string s("999999 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 999999, p.first);
    ASSERT_EQ(10, p.second);}

TEST(CollatzFixture, read_3) {
    string s("543 2000\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 543, p.first);
    ASSERT_EQ(2000, p.second);}

TEST(CollatzFixture, read_4) {
    string s("5050 105050\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 5050, p.first);
    ASSERT_EQ(105050, p.second);}


// ----
// cache compute
// ----
TEST(CollatzFixture, cachecompute_1) {
    const int v = collatz_cachecompute(10);
    ASSERT_EQ(7,v);
}
TEST(CollatzFixture, cachecompute_2) {
    const int v = collatz_cachecompute(100);
    ASSERT_EQ(26,v);
}
TEST(CollatzFixture, cachecompute_3) {
    const int v = collatz_cachecompute(1000);
    ASSERT_EQ(112,v);
}
TEST(CollatzFixture, cachecompute_4) {
    const int v = collatz_cachecompute(1000000);
    ASSERT_EQ(153,v);
}
TEST(CollatzFixture, cachecompute_5) {
    const int v = collatz_cachecompute(999999);
    ASSERT_EQ(259,v);
}
TEST(CollatzFixture, cachecompute_6) {
    const int v = collatz_cachecompute(901191);
    ASSERT_EQ(145,v);
}

// ----
// compute
// ----
TEST(CollatzFixture, compute_1) {
    const int v = collatz_compute(10);
    ASSERT_EQ(7,v);
}
TEST(CollatzFixture, compute_2) {
    const int v = collatz_compute(100);
    ASSERT_EQ(26,v);
}
TEST(CollatzFixture, compute_3) {
    const int v = collatz_compute(1000);
    ASSERT_EQ(112,v);
}
TEST(CollatzFixture, compute_4) {
    const int v = collatz_compute(1000000);
    ASSERT_EQ(153,v);
}
TEST(CollatzFixture, compute_5) {
    const int v = collatz_compute(999999);
    ASSERT_EQ(259,v);
}
TEST(CollatzFixture, compute_6) {
    const int v = collatz_compute(901191);
    ASSERT_EQ(145,v);
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

//added tests
TEST(CollatzFixture, eval_5) {
    const int v = collatz_eval(100,100);
    ASSERT_EQ(26,v);
}
TEST(CollatzFixture, eval_6) {
    const int v = collatz_eval(901191,901191);
    ASSERT_EQ(145,v);
}
TEST(CollatzFixture, eval_7) {
    const int v = collatz_eval(1000,900);
    ASSERT_EQ(174,v);
}
TEST(CollatzFixture, eval_8) {
    const int v = collatz_eval(5000,5);
    ASSERT_EQ(238,v);
}


// -----
// print
// -----

TEST(CollatzFixture, print) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

//added tests
TEST(CollatzFixture, print_1) {
    ostringstream w;
    collatz_print(w, 900, 1000, 174);
    ASSERT_EQ("900 1000 174\n", w.str());}

TEST(CollatzFixture, print_2) {
    ostringstream w;
    collatz_print(w, 201, 210, 89);
    ASSERT_EQ("201 210 89\n", w.str());}

TEST(CollatzFixture, print_3) {
    ostringstream w;
    collatz_print(w, 5000, 100, 238);
    ASSERT_EQ("5000 100 238\n", w.str());}

// -----
// solve
// -----

TEST(CollatzFixture, solve) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

//added tests
TEST(CollatzFixture, solve_1) {
    istringstream r("100 100\n1000 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("100 100 26\n1000 1000 112\n", w.str());}

TEST(CollatzFixture, solve_2) {
    istringstream r("4000 4500\n4500 5000\n5000 5500\n5500 10000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("4000 4500 215\n4500 5000 210\n5000 5500 192\n5500 10000 262\n", w.str());}

TEST(CollatzFixture, solve_3) {
    istringstream r("44 66\n8435 8849\n48438 830382\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("44 66 113\n8435 8849 216\n48438 830382 470\n", w.str());}


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
