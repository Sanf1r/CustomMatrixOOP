#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.SumMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.SubMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.MulMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator*(const double number) const {
  S21Matrix temp(*this);
  temp.MulNumber(number);
  return temp;
}

S21Matrix operator*(double number, const S21Matrix& other) {
  return other * number;
}

bool S21Matrix::operator==(const S21Matrix& other) noexcept {
  bool res = EqMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21Matrix temp(other);
    swap(*this, temp);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    S21Matrix temp(std::move(other));
    swap(*this, temp);
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double number) {
  MulNumber(number);
  return *this;
}

double& S21Matrix::operator()(int row, int columns) {
  if ((row >= rows_ || row < 0) || (columns >= columns_ || columns < 0)) {
    throw std::out_of_range("Incorrect input, index is out of range\n");
  }
  return matrix_[row * columns_ + columns];
}

double S21Matrix::operator()(int row, int columns) const {
  if ((row >= rows_ || row < 0) || (columns >= columns_ || columns < 0)) {
    throw std::out_of_range("Incorrect input, index is out of range\n");
  }
  return matrix_[row * columns_ + columns];
}