#ifndef _S21_MATRIX_H_
#define _S21_MATRIX_H_

#include <stdlib.h>

#include <cmath>
#include <ctime>
#include <initializer_list>

#include "my_exception.h"

const double kEps = 10e-6;

class S21Matrix {
 public:
  S21Matrix();  // Default constructor
  S21Matrix(int rows, int cols);
  S21Matrix(int rows, int cols, std::initializer_list<double> values);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();  // Destructor

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // Operators...
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double& num) const noexcept;
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator=(const S21Matrix& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double& num) noexcept;
  double& operator()(int i, int j) const;

  // Other methods..
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(const int& value);
  void SetCols(const int& value);
  // void PrintMatrix() const noexcept;

 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

  // Other methods..
  void CreateMatrix();
  void FreeMatrix() noexcept;
  void MinorMatrix(const S21Matrix& matrix, const int& i,
                   const int& j) noexcept;
  void CopyValues(const S21Matrix& other) noexcept;
};

#endif  //_S21_MATRIX_H_