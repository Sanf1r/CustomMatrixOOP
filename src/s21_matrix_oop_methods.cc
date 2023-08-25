#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  bool eq = true;

  if (rows_ == other.rows_ && columns_ == other.columns_) {
    for (int i = 0; i < rows_ * columns_; i++) {
      if (fabs(matrix_[i] - other.matrix_[i]) > 1e-7) {
        eq = false;
      }
    }
  } else {
    eq = false;
  }

  return eq;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    throw std::logic_error("Error in SumMatrix!\n");
  }
  for (int i = 0; i < rows_ * columns_; i++) {
    matrix_[i] += other.matrix_[i];
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    throw std::logic_error("Error in SubMatrix!\n");
  }
  for (int i = 0; i < rows_ * columns_; i++) {
    matrix_[i] -= other.matrix_[i];
  }
}

void S21Matrix::MulNumber(const double number) {
  if (std::isnan(number)) {
    throw std::invalid_argument("Error in MulNumber!\n");
  }
  for (int i = 0; i < rows_ * columns_; i++) {
    matrix_[i] *= number;
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (columns_ != other.rows_) {
    throw std::logic_error("Error in MulMatrix!\n");
  }
  S21Matrix temp_matrix(rows_, other.columns_);
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < columns_; k++) {
      for (int j = 0; j < other.columns_; j++) {
        temp_matrix(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = temp_matrix;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix temp_matrix(columns_, rows_);
  for (int i = 0; i < columns_; i++) {
    for (int j = 0; j < rows_; j++) {
      temp_matrix(i, j) = (*this)(j, i);
    }
  }
  return temp_matrix;
}

double S21Matrix::Determinant() const {
  double det = 1;
  if (rows_ != columns_) {
    throw std::logic_error("Error in Determinant!\n");
  }
  S21Matrix temp_matrix(*this);
  for (int i = 0; i < rows_; ++i) {
    int z = i;
    for (int j = i + 1; j < rows_; ++j) {
      if (fabs(temp_matrix(j, i)) > fabs(temp_matrix(z, i))) z = j;
    }
    if (fabs(temp_matrix(z, i)) < 1E-9) {
      det = 0;
      break;
    }
    temp_matrix.RowSwap(i, z);
    if (i != z) det = -det;
    det *= temp_matrix(i, i);
    for (int j = i + 1; j < rows_; ++j) {
      temp_matrix(i, j) /= temp_matrix(i, i);
    }
    for (int j = 0; j < rows_; ++j) {
      if (j != i && fabs(temp_matrix(j, i)) > 1E-9) {
        for (int k = i + 1; k < rows_; ++k) {
          temp_matrix(j, k) -= temp_matrix(i, k) * temp_matrix(j, i);
        }
      }
    }
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix temp_matrix(rows_, columns_);
  if (rows_ != columns_) {
    throw std::logic_error("Error in CalcComplements!\n");
  }
  S21Matrix minor_matrix(*this);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      minor_matrix = MinorMatrix(i, j);
      double det = minor_matrix.Determinant();
      temp_matrix(i, j) = powf(-1, i + j) * det;
    }
  }
  return temp_matrix;
}

S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix temp_matrix(rows_, columns_);
  double det = (*this).Determinant();
  if (det == 0) {
    throw std::logic_error("Error in InverseMatrix!\n");
  }
  temp_matrix = CalcComplements();
  temp_matrix = temp_matrix.Transpose();
  temp_matrix.MulNumber(1 / det);
  return temp_matrix;
}