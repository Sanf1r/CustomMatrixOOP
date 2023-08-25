#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix();                            // default constructor
  S21Matrix(int rows, int columns);       // parameterized constructor
  S21Matrix(const S21Matrix& other);      // copy constructor
  S21Matrix(S21Matrix&& other) noexcept;  // move constructor
  ~S21Matrix();                           // destructor

  // some operators overloads
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double number) const;
  friend S21Matrix operator*(double number, const S21Matrix& other);
  bool operator==(const S21Matrix& other) noexcept;
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double number);
  double& operator()(int row, int columns);
  double operator()(int row, int columns) const;

  // Some public methods
  // Checks matrices for equality with each other
  bool EqMatrix(const S21Matrix& other) const noexcept;
  // Adds the second matrix to the current one
  void SumMatrix(const S21Matrix& other);
  // Subtracts another matrix from the current one
  void SubMatrix(const S21Matrix& other);
  // Multiplies the current matrix by a number
  void MulNumber(const double number);
  // Multiplies the current matrix by the second matrix
  void MulMatrix(const S21Matrix& other);
  // Creates a new transposed matrix from the current one and returns it
  S21Matrix Transpose() const;
  // Calculates the algebraic addition matrix of the current one and returns it
  S21Matrix CalcComplements() const;
  // Calculates and returns the determinant of the current matrix
  double Determinant() const;
  // Calculates and returns the inverse matrix
  S21Matrix InverseMatrix() const;

  // Getters and setters
  int getRows() const { return rows_; }
  int getColumns() const { return columns_; }
  void setRows(int in);
  void setColumns(int in);

 private:
  int rows_, columns_;
  double* matrix_;
  // Some private methods
  // Helper method used for Gauss algorithm
  void RowSwap(int a, int b) noexcept;
  // Helper method for filling matrix with 0 or cut rows or columns
  void FillOrCut(const S21Matrix& other, int mode) noexcept;
  // Calculates and returns the minor matrix of target row and column
  S21Matrix MinorMatrix(int target_row, int target_column) const;
  // Friend swap function from std for copy-and-swap
  friend void swap(S21Matrix& one, S21Matrix& two) noexcept;
};

#endif  // SRC_S21_MATRIX_OOP_H_
