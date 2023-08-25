#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix{0, 0} {}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0) {
    rows_ = columns_ = 0;
  } else {
    rows_ = rows;
    columns_ = cols;
  }
  matrix_ = new double[rows_ * columns_]{};
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  columns_ = other.columns_;
  matrix_ = new double[other.rows_ * other.columns_]{};
  std::memcpy(matrix_, other.matrix_,
              other.rows_ * other.columns_ * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  swap(*this, other);
  other.rows_ = 0;
  other.columns_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { delete matrix_; }

void S21Matrix::setRows(int in) {
  if (in < 0) {
    throw std::logic_error("Error in setRows!\n");
  }
  S21Matrix temp = (*this);
  delete matrix_;
  rows_ = in;
  matrix_ = new double[rows_ * columns_]{};
  FillOrCut(temp, 0);
}

void S21Matrix::setColumns(int in) {
  if (in < 0) {
    throw std::logic_error("Error in setColumns!\n");
  }
  S21Matrix temp(*this);
  delete matrix_;
  columns_ = in;
  matrix_ = new double[rows_ * columns_]{};
  FillOrCut(temp, 1);
}