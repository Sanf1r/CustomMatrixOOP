#include "s21_matrix_oop.h"

void S21Matrix::RowSwap(int a, int b) noexcept {
  for (int i = 0; i < columns_; i++) {
    double temp = (*this)(a, i);
    (*this)(a, i) = (*this)(b, i);
    (*this)(b, i) = temp;
  }
}

void swap(S21Matrix& one, S21Matrix& two) noexcept {
  using std::swap;
  swap(one.rows_, two.rows_);
  swap(one.columns_, two.columns_);
  swap(one.matrix_, two.matrix_);
}

void S21Matrix::FillOrCut(const S21Matrix& other, int mode) noexcept {
  if (mode) {
    if (columns_ < other.columns_) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
          (*this)(i, j) = other(i, j);
        }
      }
    } else {
      for (int i = 0; i < other.rows_; i++) {
        for (int j = 0; j < other.columns_; j++) {
          (*this)(i, j) = other(i, j);
        }
      }
    }
  } else {
    if (rows_ < other.rows_) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
          (*this)(i, j) = other(i, j);
        }
      }
    } else {
      for (int i = 0; i < other.rows_; i++) {
        for (int j = 0; j < other.columns_; j++) {
          (*this)(i, j) = other(i, j);
        }
      }
    }
  }
}

S21Matrix S21Matrix::MinorMatrix(int target_row, int target_column) const {
  S21Matrix temp_matrix(rows_ - 1, columns_ - 1);
  int k = 0, m = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == target_row) continue;
    for (int j = 0; j < columns_; j++) {
      if (j == target_column) continue;
      temp_matrix(k, m++) = (*this)(i, j);
    }
    k++;
    m = 0;
  }
  return temp_matrix;
}