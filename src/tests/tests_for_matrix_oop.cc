#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

void s21_fill_matrix(double num, S21Matrix& matrix) {
  for (int i = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getColumns(); j++) {
      matrix(i, j) = num++;
    }
  }
}

TEST(TestConstructors, 1) {
  S21Matrix one(-1, -1);
  ASSERT_EQ(one.getRows(), 0);
  ASSERT_EQ(one.getColumns(), 0);
}

TEST(TestConstructors, 2) {
  S21Matrix one(10, 10);
  S21Matrix two(one);
  ASSERT_EQ(one.EqMatrix(two), true);
}
TEST(TestConstructors, 3) {
  S21Matrix one(10, 10);
  S21Matrix two(one);
  S21Matrix three(std::move(one));
  ASSERT_EQ(three.EqMatrix(two), true);
}
TEST(TestConstructors, 4) {
  S21Matrix one(10, 10);
  one.setColumns(5);
  one.setColumns(15);
  ASSERT_EQ(one.getColumns(), 15);
}

TEST(TestConstructors, 5) {
  S21Matrix one(10, 10);
  one.setRows(5);
  one.setRows(15);
  ASSERT_EQ(one.getRows(), 15);
}

TEST(TestEqMatrix, 1) {
  S21Matrix one(10, 10);
  S21Matrix two(10, 10);

  s21_fill_matrix(1.0, one);
  s21_fill_matrix(1.0, two);

  ASSERT_EQ(one.EqMatrix(two), true);
}
TEST(TestEqMatrix, 2) {
  S21Matrix one;
  S21Matrix two;
  s21_fill_matrix(1.0, one);
  s21_fill_matrix(2.0, two);
  ASSERT_EQ(one.EqMatrix(two), true);
}

TEST(TestEqMatrix, 3) {
  S21Matrix one(2, 3);
  S21Matrix two(2, 2);

  s21_fill_matrix(1.0, one);
  s21_fill_matrix(1.0, two);
  ASSERT_EQ(one.EqMatrix(two), false);
}

TEST(TestEqMatrix, 4) {
  S21Matrix one(0, 0);
  S21Matrix two(0, 5);

  s21_fill_matrix(1.0, one);
  s21_fill_matrix(1.0, two);
  ASSERT_EQ(one.EqMatrix(two), false);
}

TEST(TestEqMatrix, 5) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);

  one(0, 0) = 2.0;
  one(0, 1) = 5.0;
  one(1, 0) = 6.0;
  one(1, 1) = 3.0;

  two(0, 0) = 2.0;
  two(0, 1) = 5.0;
  two(1, 0) = 6.0;
  two(1, 1) = 3.0005;

  ASSERT_EQ(one.EqMatrix(two), false);
}

TEST(TestSumMatrix, 1) {
  S21Matrix one(1, 1);
  S21Matrix two(1, 1);

  one(0, 0) = 1.25;
  two(0, 0) = 2.25;

  one.SumMatrix(two);

  ASSERT_EQ(one(0, 0), 3.5);
}

TEST(TestSumMatrix, 2) {
  S21Matrix one(4, 4);
  S21Matrix two(4, 4);

  s21_fill_matrix(-3.0, one);
  s21_fill_matrix(5.0, two);

  one.SumMatrix(two);

  S21Matrix three(4, 4);

  int k = 2;
  for (int i = 0; i < three.getRows(); i++) {
    for (int j = 0; j < three.getColumns(); j++) {
      three(i, j) = k;
      k += 2;
    }
  }

  ASSERT_EQ(three.EqMatrix(one), true);
}

TEST(TestSubMatrix, 1) {
  S21Matrix one(1, 1);
  S21Matrix two(1, 1);

  one(0, 0) = 1.25;
  two(0, 0) = 2.25;

  one.SubMatrix(two);

  ASSERT_EQ(one(0, 0), -1);
}

TEST(TestMulNumber, 1) {
  S21Matrix one(1, 1);

  one(0, 0) = 8;
  one.MulNumber(5);

  ASSERT_EQ(one(0, 0), 40);
}

TEST(TestMulMatrix, 1) {
  S21Matrix one(4, 2);
  S21Matrix two(2, 4);

  s21_fill_matrix(-5.0, one);
  s21_fill_matrix(1.0, two);

  one.MulMatrix(two);

  S21Matrix three(4, 4);

  three(0, 0) = -25.0;
  three(0, 1) = -34.0;
  three(0, 2) = -43.0;
  three(0, 3) = -52.0;
  three(1, 0) = -13.0;
  three(1, 1) = -18.0;
  three(1, 2) = -23.0;
  three(1, 3) = -28.0;
  three(2, 0) = -1.0;
  three(2, 1) = -2.0;
  three(2, 2) = -3.0;
  three(2, 3) = -4.0;
  three(3, 0) = 11.0;
  three(3, 1) = 14.0;
  three(3, 2) = 17.0;
  three(3, 3) = 20.0;

  ASSERT_EQ(three.EqMatrix(one), true);
}

TEST(TestMulMatrix, 3) {
  S21Matrix one(1, 1);
  S21Matrix two(1, 1);

  one(0, 0) = 10;
  two(0, 0) = 5;

  one.MulMatrix(two);

  ASSERT_EQ(one(0, 0), 50);
}

TEST(TestTranspose, 1) {
  S21Matrix one(1, 1);

  one(0, 0) = 5;
  one = std::move(one.Transpose());

  ASSERT_EQ(one(0, 0), 5);
}

TEST(TestTranspose, 2) {
  S21Matrix one(2, 3);
  S21Matrix two(3, 2);

  s21_fill_matrix(1.0, one);

  two(0, 0) = 1.0;
  two(0, 1) = 4.0;
  two(1, 0) = 2.0;
  two(1, 1) = 5.0;
  two(2, 0) = 3.0;
  two(2, 1) = 6.0;

  one = std::move(one.Transpose());

  ASSERT_EQ(one.EqMatrix(two), true);
}

TEST(TestCalcComplements, 1) {
  S21Matrix one(4, 4);
  S21Matrix two(4, 4);

  one(0, 0) = 112.0;
  one(0, 1) = 243.0;
  one(0, 2) = 3.0;
  one(0, 3) = -8.0;
  one(1, 0) = 47.0;
  one(1, 1) = 51.0;
  one(1, 2) = -66.0;
  one(1, 3) = 99.0;
  one(2, 0) = -74.0;
  one(2, 1) = 85.0;
  one(2, 2) = 97.0;
  one(2, 3) = 63.0;
  one(3, 0) = -13.0;
  one(3, 1) = 79.0;
  one(3, 2) = -99.0;
  one(3, 3) = -121.0;

  one = std::move(one.CalcComplements());

  two(0, 0) = -2879514.0;
  two(0, 1) = -1236631.0;
  two(0, 2) = -1685096.0;
  two(0, 3) = 880697.0;
  two(1, 0) = 1162090.0;
  two(1, 1) = -714015.0;
  two(1, 2) = 4046255.0;
  two(1, 3) = -3901600.0;
  two(2, 0) = 4362897.0;
  two(2, 1) = -2049432.0;
  two(2, 2) = -532912.0;
  two(2, 3) = -1370781.0;
  two(3, 0) = 3412773.0;
  two(3, 1) = -1569493.0;
  two(3, 2) = 3144517.0;
  two(3, 3) = 1284666.0;

  ASSERT_EQ(one.EqMatrix(two), true);
}

TEST(TestDeterminant, 1) {
  S21Matrix one(1, 1);
  double det = 0.0;

  s21_fill_matrix(1.0, one);

  det = one.Determinant();

  ASSERT_EQ(det, 1);
}

TEST(TestDeterminant, 2) {
  S21Matrix one(3, 3);
  double det = 0.0;

  one(0, 0) = 4000.87;
  one(0, 1) = 454.0;
  one(0, 2) = 4.0;
  one(1, 0) = 2.0;
  one(1, 1) = 1.897;
  one(1, 2) = 3.0;
  one(2, 0) = 0.000087;
  one(2, 1) = 2.5668;
  one(2, 2) = 1.0;

  det = one.Determinant();

  ASSERT_DOUBLE_EQ(det, -24105.996724156);
}

TEST(TestInverseMatrix, 1) {
  S21Matrix one(4, 4);
  S21Matrix two(4, 4);

  one(0, 0) = -1.0;
  one(0, 1) = 2.0;
  one(0, 2) = 7.0;
  one(0, 3) = 9.0;
  one(1, 0) = 1.0;
  one(1, 1) = 0.0;
  one(1, 2) = 0.0;
  one(1, 3) = 0.0;
  one(2, 0) = 47.0;
  one(2, 1) = 13.0;
  one(2, 2) = 17.0;
  one(2, 3) = 21.0;
  one(3, 0) = 22.0;
  one(3, 1) = 7.0;
  one(3, 2) = 1.0;
  one(3, 3) = 3.0;

  two(0, 0) = 0.0;
  two(0, 1) = 1.0;
  two(0, 2) = 0.0;
  two(0, 3) = 0.0;
  two(1, 0) = -5.0 / 23.0;
  two(1, 1) = -121.0 / 23.0;
  two(1, 2) = 2.0 / 23.0;
  two(1, 3) = 1.0 / 23.0;
  two(2, 0) = -18.0 / 23.0;
  two(2, 1) = -379.0 / 46.0;
  two(2, 2) = 19.0 / 46.0;
  two(2, 3) = -25.0 / 46.0;
  two(3, 0) = 53.0 / 69.0;
  two(3, 1) = 1061.0 / 138.0;
  two(3, 2) = -47.0 / 138.0;
  two(3, 3) = 19.0 / 46.0;

  one = one.InverseMatrix();

  ASSERT_EQ(one.EqMatrix(two), true);
}

TEST(TestInverseMatrix, 2) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);

  one(0, 0) = 2.0;
  one(0, 1) = 5.0;
  one(1, 0) = 6.0;
  one(1, 1) = 3.0;

  two(0, 0) = -1.0 / 8;
  two(0, 1) = 5.0 / 24;
  two(1, 0) = 1.0 / 4;
  two(1, 1) = -1.0 / 12;

  one = one.InverseMatrix();

  ASSERT_EQ(one.EqMatrix(two), true);
}

TEST(TestOperators, 1) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);

  s21_fill_matrix(1.0, one);
  s21_fill_matrix(1.0, two);

  S21Matrix three = one + two;
  one.SumMatrix(two);

  ASSERT_EQ(one.EqMatrix(three), true);
}

TEST(TestOperators, 2) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);

  s21_fill_matrix(1.0, one);
  s21_fill_matrix(1.0, two);

  S21Matrix three = one - two;
  one.SubMatrix(two);

  ASSERT_EQ(one.EqMatrix(three), true);
}

TEST(TestOperators, 3) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);

  s21_fill_matrix(1.0, one);
  s21_fill_matrix(1.0, two);

  S21Matrix three = one * two;
  one.MulMatrix(two);

  ASSERT_EQ(one.EqMatrix(three), true);
}

TEST(TestOperators, 4) {
  S21Matrix one(2, 2);
  double num = 5.0;

  s21_fill_matrix(1.0, one);

  S21Matrix three = one * num;
  one.MulNumber(num);

  ASSERT_EQ(one.EqMatrix(three), true);
}

TEST(TestOperators, 5) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);
  int num;

  s21_fill_matrix(1.0, one);
  s21_fill_matrix(1.0, two);

  if (one == two) num = 21;

  ASSERT_EQ(num, 21);
}

TEST(TestOperators, 6) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);

  s21_fill_matrix(1.0, one);
  s21_fill_matrix(1.0, two);

  one += two;

  two(0, 0) = 2;
  two(0, 1) = 4;
  two(1, 0) = 6;
  two(1, 1) = 8;

  ASSERT_EQ(one.EqMatrix(two), true);
}

TEST(TestOperators, 7) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);

  s21_fill_matrix(1.0, one);
  s21_fill_matrix(1.0, two);

  one -= two;

  two = S21Matrix(2, 2);

  ASSERT_EQ(one.EqMatrix(two), true);
}

TEST(TestOperators, 8) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);

  s21_fill_matrix(1.0, one);
  s21_fill_matrix(1.0, two);

  one *= two;

  two(0, 0) = 7;
  two(0, 1) = 10;
  two(1, 0) = 15;
  two(1, 1) = 22;

  ASSERT_EQ(one.EqMatrix(two), true);
}

TEST(TestOperators, 9) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);
  double num = 5.0;

  s21_fill_matrix(1.0, one);

  one *= num;

  two(0, 0) = 5;
  two(0, 1) = 10;
  two(1, 0) = 15;
  two(1, 1) = 20;

  ASSERT_EQ(one.EqMatrix(two), true);
}

TEST(TestOperators, 10) {
  S21Matrix one(1, 1);

  one(0, 0) = 21;

  one = 4 * one;

  ASSERT_EQ(one(0, 0), 84);
}

//
// Tests for throw exceptions cause leaks in gtest
//

TEST(TestThrow, 1) {
  S21Matrix one(2, 2);

  EXPECT_ANY_THROW(one(5, 6));
}

TEST(TestThrow, 2) {
  const S21Matrix one(2, 2);

  EXPECT_ANY_THROW(one(5, 6));
}

TEST(TestThrow, 3) {
  S21Matrix one(10, 10);
  EXPECT_ANY_THROW(one.setRows(-1));
}
TEST(TestThrow, 4) {
  S21Matrix one(10, 10);
  EXPECT_ANY_THROW(one.setColumns(-3));
}

TEST(TestThrow, 5) {
  S21Matrix one(1, 1);
  S21Matrix two(1, 5);

  EXPECT_ANY_THROW(one.SumMatrix(two));
}

TEST(TestThrow, 6) {
  S21Matrix one(1, 1);
  S21Matrix two(1, 5);

  EXPECT_ANY_THROW(one.SubMatrix(two));
}

TEST(TestThrow, 7) {
  S21Matrix one(1, 1);

  EXPECT_ANY_THROW(one.MulNumber(NAN));
}

TEST(TestThrow, 8) {
  S21Matrix one(1, 1);
  S21Matrix two(2, 2);

  EXPECT_ANY_THROW(one.MulMatrix(two));
}

TEST(TestThrow, 9) {
  S21Matrix one(2, 4);

  EXPECT_ANY_THROW(one.CalcComplements());
}

TEST(TestThrow, 10) {
  S21Matrix one(2, 4);

  EXPECT_ANY_THROW(one.Determinant());
}

TEST(TestThrow, 11) {
  S21Matrix one(3, 3);
  S21Matrix two;

  s21_fill_matrix(1.0, one);

  EXPECT_ANY_THROW(one = one.InverseMatrix(););
}