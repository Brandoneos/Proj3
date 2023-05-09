//Header

#include <ctype.h>

#include <cctype>

#include <string>

#include <cstring>

#include <math.h>

#include <algorithm>

#include "mymatrix.h"
 //goal is to make a mymatrix class
// and write some test cases
// 

using namespace std;

//Test case for default constructor
bool test1() {
  mymatrix < int > ma;
  return (ma.numrows() == 4 && ma.numcols(2) == 4);
}
//Test case for parameterized constructor
bool test2() {
  mymatrix < int > ma(3, 5);
  return (ma.numrows() == 3 && ma.numcols(2) == 5); //Also add size == 15, when size() works
}
//Test for copy constructor
bool test3() {
  mymatrix < int > ma(3, 6);
  mymatrix < int > ma1(ma);
  return (ma1.numrows() == 3 && ma1.numcols(2) == 6); //Change this so that some 
  // values equal each other after .at() function works

}
bool test3_1() { //Copy constructor jagged
  mymatrix < int > ma(3, 3);
  ma.growcols(0, 4);
  ma.growcols(2, 6);
  mymatrix < int > ma1(ma);
  return (ma1.numrows() == 3 && ma1.numcols(0) == 4 && ma1.numcols(2) == 6); //Change this so that some 
  // values equal each other after .at() function works
}

//Test for numRows, 
bool test4() {
  //already work
}
//Test for numCols
bool test5() {
  //make sure a value like -1 can throw exception?
}
//Test for growcols
bool test6() {
  mymatrix < int > ma(4, 6);
  ma.growcols(0, 9);
  return (ma.numrows() == 4 && ma.numcols(0) == 9);
}
//Test for grow
bool test7() {
  bool boolean1 = true;
  mymatrix < int > ma(4, 6);
  ma.growcols(1, 8);
  ma.grow(1, 9);
  if (ma.numrows() != 4 || ma.numcols(1) != 9) {
    boolean1 = false;
  }

  return boolean1;

}
bool test7_1() {
  bool boolean1 = true;
  mymatrix < int > ma(4, 6);
  ma.growcols(1, 8);
  ma.grow(1, 7);
  if (ma.numrows() != 4 || ma.numcols(1) != 8) {
    boolean1 = false;
  }

  return boolean1;

}

bool test7_2() {
  bool boolean1 = true;
  mymatrix < int > ma(4, 6);

  ma.grow(5, 5);
  if (ma.numrows() != 5 || ma.numcols(1) != 6) {
    boolean1 = false;
  }

  return boolean1;

}

//Test for size()
bool test8() {
  mymatrix < int > ma(4, 6);
  ma.growcols(0, 8);
  return (ma.size() == 26);
}
//Test for .at()
bool test9() {
  mymatrix < int > ma(4, 6);
  ma.at(0, 0) = 4;
  return (ma.at(0, 0) == 4);
}
//Test for operator()
bool test10() {
  mymatrix < int > ma(4, 6);
  ma(0, 1) = 6;
  return (ma.at(0, 1) == 6);
}
//Test for scalar multiplication
bool test11() {
  mymatrix < int > m1;
  mymatrix < int > m2(4, 4);
  m2.at(0, 0) = 6;
  m1 = m2 * 2;
  return (m1(0, 0) == 12);
}
bool test11_1() { //Jagged scalar multiplication
  mymatrix < int > m1;
  mymatrix < int > m2(2, 2);
  m2.growcols(0, 4);
  m2.at(0, 0) = 1;
  m2.at(0, 1) = 1;
  m2.at(1, 0) = 1;
  m2.at(1, 1) = 1;
  m1 = m2 * 2;

  return (m1(0, 0) == 2);
}
bool test11_2() { //Jagged scalar multiplication, with grow()
  mymatrix < int > m1;
  mymatrix < int > m2(2, 2);
  m2.grow(3, 4);
  m2.growcols(0, 6);
  m2.growcols(2, 7);
  m2.at(0, 0) = 1;
  m2.at(0, 1) = 1;
  m2.at(1, 0) = 1;
  m2.at(1, 1) = 1;
  m1 = m2 * 2;

  return (m1(0, 0) == 2);
}

//Test for matrix multiplication
bool test12() { // Checks if this matrix is not rectangular

  mymatrix < int > m1;
  mymatrix < int > m2(4, 4);
  m2.at(0, 0) = 6;
  mymatrix < int > m3(4, 4);
  m2.growcols(0, 5);
  m3.at(0, 0) = 7;
  m1 = m2 * m3; // catch error
}
bool test12_1() { // Both are rectangular
  mymatrix < int > m1;
  mymatrix < int > m2(4, 4);
  m2.at(0, 0) = 6;
  mymatrix < int > m3(4, 4);
  m3.at(0, 0) = 7;
  m1 = m2 * m3;
  return true;
}
bool test12_2() { // Other matrix is not rectangular
  mymatrix < int > m1;
  mymatrix < int > m2(4, 4);
  m2.at(0, 0) = 6;
  mymatrix < int > m3(4, 4);
  m3.growcols(0, 5);
  m3.at(0, 0) = 7;
  m1 = m2 * m3; // Catch error
}
bool test12_3() { //Sizes dont match

}
bool test12_4() { //Sizes do match

}
bool test12_5() { //Multiplication works correctly (1)
  //Correct size of resulting matrix
  mymatrix < int > m1;
  mymatrix < int > m2(2, 3);
  mymatrix < int > m3(3, 2);
  m1 = m2 * m3;
  return (m1.size() == 4);

}
bool test12_6() { //Multiplication works correctly (2)
  //Correct values of resulting matrix;
  mymatrix < int > m1;
  mymatrix < int > m2(2, 3);
  m2.at(0, 0) = 1;
  m2.at(0, 1) = 2;
  m2.at(0, 2) = 3;
  m2.at(1, 0) = 4;
  m2.at(1, 1) = 5;
  m2.at(1, 2) = 6;
  mymatrix < int > m3(3, 2);
  m3.at(0, 0) = 7;
  m3.at(0, 1) = 8;
  m3.at(1, 0) = 9;
  m3.at(1, 1) = 10;
  m3.at(2, 0) = 11;
  m3.at(2, 1) = 12;
  m1 = m2 * m3;
  return (m1(0, 0) == 58 && m1(1, 0) == 139);

}

int main() {
  // cout << "Default constructor: " << endl;
  // mymatrix<int> m1;
  // cout << "numrows: " << m1.numrows() << endl;
  // cout << "numcols: " << m1.numcols(0) << endl;
  // mymatrix<int> m2(4,4);
  // cout << "Parameterized constructor: " << endl;
  // cout << "numrows: " << m2.numrows() << endl;
  // cout << "numcols: " << m2.numcols(0) << endl;
  // mymatrix<int> m3(m2);
  // cout << "Copy constructor: " << endl;
  // cout << "numrows: " << m3.numrows() << endl;
  // cout << "numcols: " << m3.numcols(0) << endl;
  // m3.growcols(0,5);
  // cout << "growcols: " << endl;
  // cout << "numrows: " << m3.numrows() << endl;
  // cout << "numcols: " << m3.numcols(0) << endl;
  // cout << "grow: " << endl;
  // m3._output();
  // cout << "size: " << m3.size() << endl;
  // m3.grow(3,5);
  // cout << "After Grow: " << endl;

  // m3._output();
  // cout << "size: " << m3.size() << endl;
  // cout << "at(): " << endl;
  // m3(0,0) = 6;
  // cout << "m3(0,0): " << m3(0,0) << endl;
  // m3._output();
  // mymatrix<int> m1;
  // mymatrix<int> m2(2,3);
  // m2.at(0,0) = 1;
  // m2.at(0,1) = 2;
  // m2.at(0,2) = 3;
  // m2.at(1,0) = 4;
  // m2.at(1,1) = 5;
  // m2.at(1,2) = 6;
  // mymatrix<int> m3(3,2);
  // m3.at(0,0) = 7;
  // m3.at(0,1) = 8;
  // m3.at(1,0) = 9;
  // m3.at(1,1) = 10;
  // m3.at(2,0) = 11;
  // m3.at(2,1) = 12;
  // // m2.growcols(0,5);

  // cout << "This matrix: " << endl;
  // m2._output();
  // cout << "Other matrix: " << endl;
  // m3._output();
  // // cout << "After scalar multiplication:  " << endl;
  // // m1 = m2 * 2;
  // cout << "After matrix multiplication:  " << endl;
  // m1 = m2 * m3;
  // m1._output();

  int pass = 0;
  int fail = 0;
  (test1()) ? pass++ : fail++; //Default constructor
  (test2()) ? pass++ : fail++; //Parameterized constructor
  (test3()) ? pass++ : fail++; //Copy constructor
  (test3_1()) ? pass++ : fail++; // copy constructor with jagged matrix
  (test6()) ? pass++ : fail++; //Growcols
  (test7()) ? pass++ : fail++; // grow
  (test7_1()) ? pass++ : fail++; // grow
  (test7_2()) ? pass++ : fail++; // grow
  (test8()) ? pass++ : fail++; //size()
  (test9()) ? pass++ : fail++; //.at()
  (test10()) ? pass++ : fail++; //operator()
  (test11()) ? pass++ : fail++; //scalar multiplication
  (test11_1()) ? pass++ : fail++; //scalar multiplication with jagged matrix
  (test11_2()) ? pass++ : fail++;
  // (test12()) ? pass++ : fail++; //matrix multiplication
  (test12_1()) ? pass++ : fail++; //matrix multiplication
  // (test12_2()) ? pass++ : fail++; //matrix multiplication
  (test12_5()) ? pass++ : fail++; // Correct size of matrix multiplcation
  (test12_6()) ? pass++ : fail++; //Correct values of matrix multiplication
  // (test3()) ? pass++ : fail++;

  cout << "test cases passed: " << pass << endl;
  cout << "test cases failed: " << fail << endl;

  return 0;
}