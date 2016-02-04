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

TEST(CollatzFixture, read_1){
    string s("41 257\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(41, p.first);
    ASSERT_EQ(257, p.second);}

TEST(CollatzFixture, read_2){
    string s("101 666\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(101, p.first);
    ASSERT_EQ(666, p.second);}

TEST(CollatzFixture, read_3){
    string s("98 100\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(98, p.first);
    ASSERT_EQ(100, p.second);}
    
TEST(CollatzFixture, read_4b){
    string s("100 51\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(100, p.first);
    ASSERT_EQ(51, p.second);}    
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

TEST(CollatzFixture, eval_4b) {
    const int v = collatz_eval(1000, 900);
    ASSERT_EQ(174, v);}
  
TEST(CollatzFixture, eval_5) {
    const int v = collatz_eval(500000, 500000);
    ASSERT_EQ(152, v);}    
           
TEST(CollatzFixture, eval_6) {
    const int v = collatz_eval(999998, 999999);
    ASSERT_EQ(259, v);} 
        
TEST(CollatzFixture, eval_7) {
    const int v = collatz_eval(900000, 999999);
    ASSERT_EQ(507, v);}   
   
TEST(CollatzFixture, eval_8b) {
    const int v = collatz_eval(999999, 1);
    ASSERT_EQ(525, v);}
    
TEST(CollatzFixture, eval_9) {
    const int v = collatz_eval(999999, 999999);
    ASSERT_EQ(259, v);}
        
// -----
// print
// -----

TEST(CollatzFixture, print) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}
    
TEST(CollatzFixture, print_1) {
    ostringstream w;
    collatz_print(w, 100, 200, 125);
    ASSERT_EQ("100 200 125\n", w.str());}
    
TEST(CollatzFixture, print_2) {
    ostringstream w;
    collatz_print(w, 201, 210, 89);
    ASSERT_EQ("201 210 89\n", w.str());}
    
TEST(CollatzFixture, print_3) {
    ostringstream w;
    collatz_print(w, 900, 1000, 174);
    ASSERT_EQ("900 1000 174\n", w.str());}
// -----
// solve
// -----

TEST(CollatzFixture, solve) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

TEST(CollatzFicture, solve_1){
    istringstream r("1 5\n5 4\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 5 8\n5 4 6\n", w.str());}
    
TEST(CollatzFicture, solve_2){
    istringstream r("3 7\n4 5\n5 1\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("3 7 17\n4 5 6\n5 1 8\n", w.str());}
    
TEST(CollatzFicture, solve_3){
    istringstream r("1 1\n5 5\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1 1\n5 5 6\n", w.str());}
       
/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz                                         >  TestCollatz.out 2>&1
% gcov -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.out
% gcov -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.out



% cat TestCollatz.out
==42274== Memcheck, a memory error detector
==42274== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==42274== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==42274== Command: ./TestCollatz
==42274== 
Running main() from gtest_main.cc
[==========] Running 22 tests from 2 test cases.
[----------] Global test environment set-up.
[----------] 19 tests from CollatzFixture
[ RUN      ] CollatzFixture.read
[       OK ] CollatzFixture.read (23 ms)
[ RUN      ] CollatzFixture.read_1
[       OK ] CollatzFixture.read_1 (3 ms)
[ RUN      ] CollatzFixture.read_2
[       OK ] CollatzFixture.read_2 (3 ms)
[ RUN      ] CollatzFixture.read_3
[       OK ] CollatzFixture.read_3 (3 ms)
[ RUN      ] CollatzFixture.read_4b
[       OK ] CollatzFixture.read_4b (3 ms)
[ RUN      ] CollatzFixture.eval_1
[       OK ] CollatzFixture.eval_1 (7 ms)
[ RUN      ] CollatzFixture.eval_2
[       OK ] CollatzFixture.eval_2 (3 ms)
[ RUN      ] CollatzFixture.eval_3
[       OK ] CollatzFixture.eval_3 (2 ms)
[ RUN      ] CollatzFixture.eval_4b
[       OK ] CollatzFixture.eval_4b (2 ms)
[ RUN      ] CollatzFixture.eval_5
[       OK ] CollatzFixture.eval_5 (2 ms)
[ RUN      ] CollatzFixture.eval_6
[       OK ] CollatzFixture.eval_6 (2 ms)
[ RUN      ] CollatzFixture.eval_7
[       OK ] CollatzFixture.eval_7 (2110 ms)
[ RUN      ] CollatzFixture.eval_8b
[       OK ] CollatzFixture.eval_8b (2288 ms)
[ RUN      ] CollatzFixture.eval_9
[       OK ] CollatzFixture.eval_9 (2 ms)
[ RUN      ] CollatzFixture.print
[       OK ] CollatzFixture.print (14 ms)
[ RUN      ] CollatzFixture.print_1
[       OK ] CollatzFixture.print_1 (3 ms)
[ RUN      ] CollatzFixture.print_2
[       OK ] CollatzFixture.print_2 (4 ms)
[ RUN      ] CollatzFixture.print_3
[       OK ] CollatzFixture.print_3 (4 ms)
[ RUN      ] CollatzFixture.solve
[       OK ] CollatzFixture.solve (14 ms)
[----------] 19 tests from CollatzFixture (4509 ms total)

[----------] 3 tests from CollatzFicture
[ RUN      ] CollatzFicture.solve_1
[       OK ] CollatzFicture.solve_1 (3 ms)
[ RUN      ] CollatzFicture.solve_2
[       OK ] CollatzFicture.solve_2 (4 ms)
[ RUN      ] CollatzFicture.solve_3
[       OK ] CollatzFicture.solve_3 (4 ms)
[----------] 3 tests from CollatzFicture (11 ms total)

[----------] Global test environment tear-down
[==========] 22 tests from 2 test cases ran. (4574 ms total)
[  PASSED  ] 22 tests.
==42274== 
==42274== HEAP SUMMARY:
==42274==     in use at exit: 0 bytes in 0 blocks
==42274==   total heap usage: 1,061 allocs, 1,061 frees, 4,107,627 bytes allocated
==42274== 
==42274== All heap blocks were freed -- no leaks are possible
==42274== 
==42274== For counts of detected and suppressed errors, rerun with: -v
==42274== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
File 'Collatz.c++'
Lines executed:98.04% of 51
Branches executed:100.00% of 56
Taken at least once:71.43% of 56
Calls executed:90.63% of 32
Creating 'Collatz.c++.gcov'
File 'TestCollatz.c++'
Lines executed:100.00% of 88
Branches executed:61.57% of 562
Taken at least once:30.78% of 562
Calls executed:54.02% of 659
Creating 'TestCollatz.c++.gcov'
*/
