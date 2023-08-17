#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(default_constructor, test_1) {
  S21Matrix a;
  ASSERT_EQ(a.GetCols(), 2);
  ASSERT_EQ(a.GetRows(), 2);
}

TEST(initializer_list_constructor, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  ASSERT_EQ(a(1, 1), 4);
}

TEST(copy_constructor, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b(a);
  ASSERT_EQ(a == b, true);
}

TEST(copy_constructor, test_2) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b = a;
  ASSERT_EQ(a == b, true);
}

TEST(transfer_constructor, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b(a);
  S21Matrix c(std::move(a));
  ASSERT_EQ(b == c, true);
}

TEST(eq_matrix, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b(2, 2, {1, 2, 3, 4});
  ASSERT_EQ(a.EqMatrix(b), true);
}

TEST(eq_matrix, test_2) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b(2, 2, {1, 2, 3, 1});
  ASSERT_EQ(a.EqMatrix(b), false);
}

TEST(eq_matrix, test_3) {
  S21Matrix a(1, 1, {1});
  S21Matrix b(2, 2, {1, 2, 3, 1});
  ASSERT_EQ(a.EqMatrix(b), false);
}

TEST(sum_matrix, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b(2, 2, {1, 2, 3, 4});
  S21Matrix res(2, 2, {2, 4, 6, 8});
  ASSERT_EQ(res == a + b, true);
}

TEST(sum_matrix, test_2) {
  S21Matrix a(2, 2);
  S21Matrix b(3, 3);
  EXPECT_THROW(a.SumMatrix(b), MyException);
}

TEST(sum_matrix, test_3) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b(2, 2, {1, 2, 3, 4});
  a += b;
  S21Matrix res(2, 2, {2, 4, 6, 8});
  ASSERT_EQ(res == a, true);
}

TEST(sub_matrix, test_1) {
  S21Matrix a(2, 2, {5, 5, 5, 5});
  S21Matrix b(2, 2, {1, 2, 3, 4});
  S21Matrix res(2, 2, {4, 3, 2, 1});
  ASSERT_EQ(res == a - b, true);
}

TEST(sub_matrix, test_2) {
  S21Matrix a(2, 2, {5, 5, 5, 5});
  S21Matrix b(2, 2, {1, 2, 3, 4});
  a -= b;
  S21Matrix res(2, 2, {4, 3, 2, 1});
  ASSERT_EQ(res == a, true);
}

TEST(sub_matrix, test_3) {
  S21Matrix a(2, 2);
  S21Matrix b(3, 3);
  EXPECT_THROW(a.SubMatrix(b), MyException);
}

TEST(mul_number, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b = a * 2;
  S21Matrix res(2, 2, {2, 4, 6, 8});
  ASSERT_EQ(b == res, true);
}

TEST(mul_number, test_2) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  a *= 2;
  S21Matrix res(2, 2, {2, 4, 6, 8});
  ASSERT_EQ(a, res);
}

TEST(mul_number, test_3) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  a.MulNumber(2);
  S21Matrix res(2, 2, {2, 4, 6, 8});
  ASSERT_EQ(a, res);
}

TEST(mul_matrix, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b(2, 2, {1, 2, 3, 4});
  S21Matrix res = a * b;
  S21Matrix ans(2, 2, {7, 10, 15, 22});
  ASSERT_EQ(ans == res, true);
}

TEST(mul_matrix, test_2) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b(2, 2, {1, 2, 3, 4});
  a *= b;
  S21Matrix ans(2, 2, {7, 10, 15, 22});
  ASSERT_EQ(ans == a, true);
}

TEST(mul_matrix, test_3) {
  S21Matrix a(2, 2);
  S21Matrix b(3, 3);
  EXPECT_THROW(a.MulMatrix(b), MyException);
}

TEST(transpose, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b = a.Transpose();
  S21Matrix ans(2, 2, {1, 3, 2, 4});
  ASSERT_EQ(ans == b, true);
}

TEST(calc_complements, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b = a.CalcComplements();
  S21Matrix ans(2, 2, {4, -3, -2, 1});
  ASSERT_EQ(ans == b, true);
}

TEST(calc_complements, test_2) {
  S21Matrix a(2, 3, {1, 2, 3, 4, 1, 1});
  EXPECT_THROW(a.CalcComplements(), MyException);
}

TEST(calc_complements, test_3) {
  S21Matrix a(1, 1, {5});
  S21Matrix b = a.CalcComplements();
  S21Matrix ans(1, 1, {1});
  ASSERT_EQ(ans == b, true);
}

TEST(determinant, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  ASSERT_EQ(a.Determinant(), -2);
}

TEST(determinant, test_2) {
  S21Matrix a(1, 1, {100});
  ASSERT_EQ(a.Determinant(), 100);
}

TEST(determinant, test_3) {
  S21Matrix a(2, 3);
  EXPECT_THROW(a.Determinant(), MyException);
}

TEST(determinant, test_4) {
  S21Matrix a(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_EQ(a.Determinant(), 0);
}

TEST(inverse_matrix, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b = a.InverseMatrix();
  S21Matrix ans(2, 2, {-2, 1, 1.5, -0.5});
  ASSERT_EQ(ans == b, true);
}

TEST(inverse_matrix, test_2) {
  S21Matrix a(2, 2);
  EXPECT_THROW(a.InverseMatrix(), MyException);
}

TEST(set_cols_and_cols, test_1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  a.SetCols(3);
  a.SetRows(3);
  S21Matrix ans(3, 3, {1, 2, 0, 3, 4, 0, 0, 0, 0});
  ASSERT_EQ(ans == a, true);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
