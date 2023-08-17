#include "s21_matrix_oop.h"

// int main(int argc, char const *argv[])
// {
// 	// S21Matrix a;
// 	// a = w;
// 	// try {
// 	// 	S21Matrix b (3, 3);
// 	// 	b.PrintMatrix();
// 	// } catch (std::exception& e) {
// 	// 	std::cout << "aboba" << std::endl << e.what() << std::endl;
// 	// }
// 	S21Matrix aboba(2, 2, {1, 2, 3, 4});
// 	aboba.SetRows(6);
// 	aboba.PrintMatrix();
// 	// S21Matrix a(2, 2, {1, 2, 3, 4});
// 	// aboba.MulMatrix(a);
// 	// S21Matrix aboba(1, 1, {3});
// 	// S21Matrix aboba1(2, 2);
// 	// aboba.FillingMatrix();
// 	// aboba.PrintMatrix();
// 	// (aboba * 3.).PrintMatrix();
// 	// a += aboba;
// 	// a += aboba;
// 	// a += aboba;
// 	// a.PrintMatrix();
// 	// S21Matrix b = a + aboba;
// 	// b.PrintMatrix();
// 	// a.PrintMatrix();
// 	// aboba.MulNumber(2);
// 	// aboba.PrintMatrix();
// 	// std::cout << aboba.Determinant() << std::endl;
// 	// aboba.Transpose().PrintMatrix();
// 	// try {
// 	// aboba.InverseMatrix().PrintMatrix();
// 	// } catch (MyException& e){
// 	// 	std::cout << e.what() << std::endl;
// 	// }
// 	// aboba.Transpose();
// 	// aboba.PrintMatrix();
// 	return 0;
// }

// Методы
bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    return false;
  } else {
    for (auto i = 0; i < this->rows_; i++) {
      for (auto j = 0; j < this->cols_; j++) {
        if (this->matrix_[i][j] - other.matrix_[i][j] > kEps) return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw MyException(
        "Exception in method SumMatrix! Different dimensions of matrices\n");
  } else {
    for (auto i = 0; i < this->rows_; i++) {
      for (auto j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw MyException(
        "Exception in method SubMatrix! Different dimensions of matrices\n");
  } else {
    for (auto i = 0; i < this->rows_; i++) {
      for (auto j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (auto i = 0; i < this->rows_; i++) {
    for (auto j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw MyException(
        "Exception in method MulMatrix! The number of columns of the first "
        "matrix is not equal to the number of rows of the second\n");
  } else {
    S21Matrix temp(*this);
    this->FreeMatrix();
    this->cols_ = other.cols_;
    CreateMatrix();
    for (auto i = 0; i < this->rows_; i++) {
      for (auto j = 0; j < this->cols_; j++) {
        for (auto k = 0; k < temp.cols_; k++) {
          this->matrix_[i][j] += temp.matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
  }
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix temp(this->cols_, this->rows_);
  for (auto i = 0; i < this->rows_; i++) {
    for (auto j = 0; j < this->cols_; j++) {
      temp.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return temp;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix temp(this->rows_, this->cols_);
  if (this->cols_ != this->rows_) {
    throw MyException(
        "Exception in method CalcComplements! Matrix is not square.");
  } else {
    if (this->rows_ == 1) {
      temp.matrix_[0][0] = 1;
    } else {
      for (auto i = 0; i < this->rows_; i++) {
        for (auto j = 0; j < this->cols_; j++) {
          S21Matrix buff(this->rows_ - 1, this->cols_ - 1);
          buff.MinorMatrix(*this, i, j);
          temp.matrix_[i][j] = buff.Determinant() * pow(-1., (double)(i + j));
        }
      }
    }
  }
  return temp;
}

double S21Matrix::Determinant() const {
  double det = 0;
  if (this->cols_ != this->rows_) {
    throw MyException("Exception in method Determinant! Matrix is not square.");
  } else {
    int degree = 1;
    int order = this->rows_;
    if (order == 1) {
      return this->matrix_[0][0];
    } else if (order == 2) {
      det = this->matrix_[0][0] * this->matrix_[1][1] -
            this->matrix_[0][1] * this->matrix_[1][0];
    } else {
      for (int i = 0; i < order; i++) {
        S21Matrix temp(order - 1, order - 1);
        temp.MinorMatrix(*this, 0, i);
        det += degree * this->matrix_[0][i] * temp.Determinant();
        degree = -degree;
      }
    }
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = this->Determinant();
  if (!det) {
    throw MyException(
        "Exception in method InverseMatrix! The determinant is zero.");
  }

  S21Matrix result(this->rows_, this->cols_);
  if (this->rows_ > 1) {
    result = this->CalcComplements().Transpose();
    result.MulNumber(1. / det);
  } else {
    result.matrix_[0][0] = 1. / this->matrix_[0][0];
  }
  return result;
}

// Операторы
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw MyException(
        "Exception in operator \"+\"! Different dimensions of matrices\n");
  }
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw MyException(
        "Exception in operator \"-\"! Different dimensions of matrices\n");
  }
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  if (this->cols_ != other.rows_)
    throw MyException(
        "Exception in operator \"*\"! The number of columns of the first "
        "matrix is not equal to the number of rows of the second\n");
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double& num) const noexcept {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) noexcept {
  if (this->matrix_ != other.matrix_) {
    this->FreeMatrix();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->CreateMatrix();
    for (auto i = 0; i < this->rows_; i++) {
      for (auto j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double& num) noexcept {
  this->MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int i, int j) const {
  if (i >= this->rows_ || j >= this->cols_ || i < 0 || j < 0)
    throw std::out_of_range("you are out of range\n");
  return this->matrix_[i][j];
}

// Конструкторы
S21Matrix::S21Matrix() : S21Matrix::S21Matrix(2, 2) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_{rows}, cols_{cols} {
  CreateMatrix();
}

S21Matrix::S21Matrix(int rows, int cols, std::initializer_list<double> values)
    : rows_{rows}, cols_{cols} {
  CreateMatrix();
  auto iter = values.begin();
  for (auto i = 0; i < this->rows_; i++) {
    for (auto j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = *iter++;
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_{other.rows_}, cols_{other.cols_} {
  CreateMatrix();
  for (auto i = 0; i < this->rows_; i++) {
    for (auto j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_{other.rows_}, cols_{other.cols_} {
  this->matrix_ = other.matrix_;
  other.rows_ = other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { FreeMatrix(); }

// Приватные методы
void S21Matrix::CreateMatrix() {
  if (this->rows_ <= 0 || this->cols_ <= 0)
    throw MyException(
        "Exception in method CreateMatrix! Values of rows and cols must be "
        "biger then zero\n");

  this->matrix_ = new double*[rows_]();
  for (auto i = 0; i < rows_; i++) {
    this->matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::FreeMatrix() noexcept {
  if (this->matrix_) {
    for (auto i = 0; i < this->rows_; i++) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
  }
}

void S21Matrix::MinorMatrix(const S21Matrix& matrix, const int& i,
                            const int& j) noexcept {
  int iBuff{0}, jBuff{0};
  for (auto k = 0; k < matrix.rows_; k++) {
    if (k == i) continue;
    for (auto l = 0; l < matrix.cols_; l++) {
      if (l == j) continue;
      this->matrix_[iBuff][jBuff] = matrix.matrix_[k][l];
      jBuff++;
    }
    iBuff++;
    jBuff = 0;
  }
}

// Дополнительные публичные методы

int S21Matrix::GetRows() const noexcept { return this->rows_; }

int S21Matrix::GetCols() const noexcept { return this->cols_; }

void S21Matrix::SetRows(const int& value) {
  if (value <= 0)
    throw MyException("The number of rows must be greater than zero!");

  S21Matrix temp(*this);
  this->FreeMatrix();
  this->rows_ = value;
  this->CopyValues(temp);
}

void S21Matrix::SetCols(const int& value) {
  if (value <= 0)
    throw MyException("The number of cols must be greater than zero!");
    
  S21Matrix temp(*this);
  this->FreeMatrix();
  this->cols_ = value;
  this->CopyValues(temp);
}

void S21Matrix::CopyValues(const S21Matrix& other) noexcept {
  const int result_cols = std::min(other.cols_, this->cols_);
  const int result_rows = std::min(other.rows_, this->rows_);
  this->CreateMatrix();
  for (auto i = 0; i < result_rows; i++) {
    for (auto j = 0; j < result_cols; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}