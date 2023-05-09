/*mymatrix.h*/

/*
AUTHOR: BRANDON KIM
PROGRAM OVERVIEW: This file allows users to access the mymatrix class
which allows them to do various functions similar to a matrix. 
*/

/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>

#include <exception>

#include <stdexcept>


using namespace std;

template < typename T >
  class mymatrix {
    private: struct ROW {
      T * Cols; // dynamic array of column elements
      int NumCols; // total # of columns (0..NumCols-1)
    };

    ROW * Rows; // dynamic array of ROWs
    int NumRows; // total # of rows (0..NumRows-1)

    //
    // getVerticalList:
    //
    // This function makes an array of elements from the column of index. 
    // Gets the columns array used for matrix multiplication
    //
    T * getVerticalList(int index,
      const mymatrix < T > & other, int size1) {
      T * verticalList = new T[size1];
      for (int i = 0; i < size1; i++) {
        verticalList[i] = other.Rows[i].Cols[index];
      }
      return verticalList;
    }
    //
    // dotProduct:
    //
    // This function calculates the dot product of 2 lists, which
    // multiplication corresponding elements and adds up the total of those products and returns that value;
    //
    T dotProduct(ROW Row1, T * list2, int size1) {
      T sum = T {};
      for (int i = 0; i < size1; i++) {
        sum += Row1.Cols[i] * list2[i];
      }
      return sum;
    }

    public:
      //
      // default constructor:
      //
      // Called automatically by C++ to construct a 4x4 matrix.  All 
      // elements are initialized to the default value of T.
      //
      mymatrix() {
        Rows = new ROW[4]; // an array with 4 ROW structs:
        NumRows = 4;

        // initialize each row to have 4 columns:
        for (int r = 0; r < NumRows; ++r) {
          Rows[r].Cols = new T[4]; // an array with 4 elements of type T:
          Rows[r].NumCols = 4;

          // initialize the elements to their default value:
          for (int c = 0; c < Rows[r].NumCols; ++c) {
            Rows[r].Cols[c] = T {}; // default value for type T:
          }
        }
      }

    //
    // parameterized constructor:
    //
    // Called automatically by C++ to construct a matrix with R rows, 
    // where each row has C columns. All elements are initialized to 
    // the default value of T.
    //
    mymatrix(int R, int C) {
      if (R < 1)
        throw invalid_argument("mymatrix::constructor: # of rows");
      if (C < 1)
        throw invalid_argument("mymatrix::constructor: # of cols");
      //Throw error if user is trying to make 0x0 matrix or smaller.
      Rows = new ROW[R];
      NumRows = R;

      for (int r = 0; r < NumRows; ++r) {
        Rows[r].Cols = new T[C]; // an array with C elements of type T:
        Rows[r].NumCols = C;

        // initialize the elements to their default value:
        for (int c = 0; c < Rows[r].NumCols; ++c) {
          Rows[r].Cols[c] = T {}; // default value for type T:
        }
      }

    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to construct a matrix that contains a 
    // copy of an existing matrix.  Example: this occurs when passing 
    // mymatrix as a parameter by value
    //
    //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
    //   { ... }
    //
    mymatrix(const mymatrix < T > & other) {

      Rows = new ROW[other.NumRows]; // an array with the same number of ROW structs as passed in
      NumRows = (((other).NumRows));

      for (int r = 0; r < other.NumRows; ++r) {
        Rows[r].Cols = new T[((other).Rows[r].NumCols)];
        Rows[r].NumCols = (((other).Rows[r].NumCols));

        // initialize the elements to the same as other passed in
        for (int c = 0; c < Rows[r].NumCols; ++c) {
          Rows[r].Cols[c] = (other).Rows[r].Cols[c]; // values from other matrix
        }
      }

    }

    //
    // numrows
    //
    // Returns the # of rows in the matrix.  The indices for these rows
    // are 0..numrows-1.
    //
    int numrows() const {
      return NumRows;
    }

    //
    // numcols
    //
    // Returns the # of columns in row r.  The indices for these columns
    // are 0..numcols-1.  Note that the # of columns can be different 
    // row-by-row since "jagged" rows are supported --- matrices are not
    // necessarily rectangular.
    //
    int numcols(int r) const {
      if (r < 0 || r >= NumRows)
        throw invalid_argument("mymatrix::numcols: row");

      return Rows[r].NumCols;
    }

    //
    // growcols
    //
    // Grows the # of columns in row r to at least C.  If row r contains 
    // fewer than C columns, then columns are added; the existing elements
    // are retained and new locations are initialized to the default value 
    // for T.  If row r has C or more columns, then all existing columns
    // are retained -- we never reduce the # of columns.
    //
    // Jagged rows are supported, i.e. different rows may have different
    // column capacities -- matrices are not necessarily rectangular.
    //
    void growcols(int r, int C) {
      if (r < 0 || r >= NumRows)
        throw invalid_argument("mymatrix::growcols: row");
      if (C < 1)
        throw invalid_argument("mymatrix::growcols: columns");
      if (Rows[r].NumCols < C) {
        int previousCols = Rows[r].NumCols;
        T * Cols1 = Rows[r].Cols;
        Rows[r].Cols = new T[C]; //Making a new Cols array with the updated size.
        Rows[r].NumCols = C;

        //Then copy in the old values of the old Cols
        for (int i = 0; i < C; i++) {
          if (i < previousCols) {
            Rows[r].Cols[i] = Cols1[i];
          } else {
            Rows[r].Cols[i] = T {}; //Default value for the rest of the elements
          }
        }
      }
      // else rows retained 
    }

    //
    // grow
    //
    // Grows the size of the matrix so that it contains at least R rows,
    // and every row contains at least C columns.
    // 
    // If the matrix contains fewer than R rows, then rows are added
    // to the matrix; each new row will have C columns initialized to 
    // the default value of T.  If R <= numrows(), then all existing
    // rows are retained -- we never reduce the # of rows.
    //
    // If any row contains fewer than C columns, then columns are added
    // to increase the # of columns to C; existing values are retained
    // and additional columns are initialized to the default value of T.
    // If C <= numcols(r) for any row r, then all existing columns are
    // retained -- we never reduce the # of columns.
    // 
    void grow(int R, int C) {
      if (R < 1)
        throw invalid_argument("mymatrix::grow: # of rows");
      if (C < 1)
        throw invalid_argument("mymatrix::grow: # of cols");

      if (NumRows < R) {
        //Make a new matrix here?
        int numRows1 = NumRows;
        ROW * Rows1 = Rows; //Has R rows, so more than the old.
        Rows = new ROW[R];
        NumRows = R;

        int numCols1;

        for (int r = 0; r < NumRows; ++r) {

          if (r < numRows1) { //if the current row is within the number of rows, then the row gets same number of elements as old array.
            numCols1 = Rows1[r].NumCols;
          } else {
            numCols1 = 1; //New rows created default to set with 1 element. Changed later with growCols throughout the list.
          }

          Rows[r].Cols = new T[numCols1]; // an array with 4 elements of type T:
          Rows[r].NumCols = numCols1;

          if (r < numRows1) { //Either copies old elements into the new one or initializes the new elements with default value

            for (int c = 0; c < Rows[r].NumCols; ++c) {
              Rows[r].Cols[c] = Rows1[r].Cols[c];
            }
          } else {

            for (int c = 0; c < Rows[r].NumCols; ++c) {
              Rows[r].Cols[c] = T {};
            }
          }

        }

        // Grow cols for each row.. Last step
        for (int r = 0; r < NumRows; r++) {

          if (Rows[r].NumCols < C) {
            growcols(r, C);
          }

        }

      } else { // Grow cols anyway for each row.. Last step, just doesn't add rows now
        for (int r = 0; r < NumRows; r++) {

          if (Rows[r].NumCols < C) {
            growcols(r, C);
          }

        }
      }
      //else keep rows the same

    }

    //
    // size
    //
    // Returns the total # of elements in the matrix.
    //
    int size() const {

      int count1 = 0;
      for (int r = 0; r < NumRows; ++r) {
        for (int c = 0; c < Rows[r].NumCols; ++c) {
          count1++;
        }
      }

      return (count1);

    }

    //
    // at
    //
    // Returns a reference to the element at location (r, c); this
    // allows you to access the element or change it:
    //
    //    M.at(r, c) = ...
    //    cout << M.at(r, c) << endl;
    //
    T & at(int r, int c) const {
      if (r < 0 || r >= NumRows)
        throw invalid_argument("mymatrix::at: row");
      if (c < 0 || c >= Rows[r].NumCols)
        throw invalid_argument("mymatrix::at: col");
      return (Rows[r].Cols[c]);
    }

    //
    // ()
    //
    // Returns a reference to the element at location (r, c); this
    // allows you to access the element or change it:
    //
    //    M(r, c) = ...
    //    cout << M(r, c) << endl;
    //
    T & operator()(int r, int c) const {
      if (r < 0 || r >= NumRows)
        throw invalid_argument("mymatrix::(): row");
      if (c < 0 || c >= Rows[r].NumCols)
        throw invalid_argument("mymatrix::(): col");

      return (Rows[r].Cols[c]);
    }

    //
    // scalar multiplication
    //
    // Multiplies every element of this matrix by the given scalar value,
    // producing a new matrix that is returned.  "This" matrix is not
    // changed.
    //
    // Example:  M2 = M1 * 2;
    //
    mymatrix < T > operator * (T scalar) {
      mymatrix < T > result;

      result.Rows = new ROW[NumRows]; // an array with same number of ROW structs:

      // initialize each row to have same columns:
      for (int r = 0; r < NumRows; ++r) {

        result.Rows[r].Cols = new T[Rows[r].NumCols];
        result.Rows[r].NumCols = Rows[r].NumCols;

        // initialize the elements to the multiple times same elements
        for (int c = 0; c < result.Rows[r].NumCols; ++c) {
          result.Rows[r].Cols[c] = (scalar * (T(Rows[r].Cols[c])));

        }
      }

      return result;
    }

    //
    // matrix multiplication
    //
    // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
    // M2 is the "other" matrix.  This produces a new matrix, which is returned.
    // "This" matrix is not changed, and neither is the "other" matrix.
    //
    // Example:  M3 = M1 * M2;
    //
    // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
    // addition, the sizes of M1 and M2 must be compatible in the following sense:
    // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
    // multiplication can be performed, and the resulting matrix is of size RxC.
    //
    mymatrix < T > operator * (const mymatrix < T > & other) {

      //Checking if this matrix has the same number of elements in each column throughout
      int columnCounter = Rows[0].NumCols;
      for (int i = 0; i < NumRows; i++) {
        if (Rows[i].NumCols != columnCounter) {
          throw runtime_error("mymatrix::*: this not rectangular");
          break;
        }

      }
      columnCounter = other.Rows[0].NumCols; //resetting counter to check other matrix

      for (int i = 0; i < other.NumRows; i++) {
        if (other.Rows[i].NumCols != columnCounter) {
          throw runtime_error("mymatrix::*: other not rectangular");
          break;
        }

      }
      if (Rows[0].NumCols != other.NumRows) {
        throw runtime_error("mymatrix::*: size mismatch");
      }
      int RowsOfResult = NumRows;
      int ColsOfResult = other.Rows[0].NumCols;
      //Result matrix will have size: RowsOfResult * ColsOfResult
      mymatrix < T > result(RowsOfResult, ColsOfResult);
      //Sizes match so we can multiply : 
      int sum = T {};
      for (int r = 0; r < RowsOfResult; r++) {
        for (int i = 0; i < ColsOfResult; i++) {
          T * C = getVerticalList(i, other, other.NumRows); //Gets the column of elements
          sum = dotProduct(Rows[r], C, other.NumRows); //Gets the dot product of 2 lists
          result.at(r, i) = sum;
        }
        sum = T {};
      }

      return result;
    }

    //
    // _output
    //
    // Outputs the contents of the matrix; for debugging purposes.
    //
    void _output() {
      for (int r = 0; r < this -> NumRows; ++r) {
        for (int c = 0; c < this -> Rows[r].NumCols; ++c) {
          cout << this -> Rows[r].Cols[c] << " ";
        }
        cout << endl;
      }
    }

  };