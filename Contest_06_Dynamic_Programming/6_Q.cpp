#include <iostream>
#include <vector>

const int cMod = 1e9 + 7;
const int cMaxHeight = 17;

struct Matrix {
  int size;
  std::vector<std::vector<long long>> data;

  Matrix(int size)
      : size(size),
        data(std::vector<std::vector<long long>>(
            size, std::vector<long long>(size, 0))) {}

  Matrix(int size, int filled_size) : Matrix(size) {
    for (int i = 0; i < filled_size; i++) {
      data[i][i] = 1;
      if (i < filled_size - 1) {
        data[i][i + 1] = 1;
        data[i + 1][i] = 1;
      }
    }
  }
};

Matrix MultiplyMatrix(Matrix& first, Matrix& second) {
  Matrix result(first.size);
  for (int i = 0; i < result.size; i++) {
    for (int j = 0; j < result.size; j++) {
      for (int k = 0; k < result.size; k++) {
        result.data[i][j] =
            (result.data[i][j] + first.data[i][k] * second.data[k][j]) % cMod;
      }
    }
  }
  return result;
}

Matrix PowerMatrix(Matrix& matrix, long long power) {
  if (power == 0) {
    Matrix result(matrix.size);
    for (int i = 0; i < matrix.size; i++) {
      result.data[i][i] = 1;
    }
    return result;
  }
  if (power % 2 == 1) {
    Matrix temp(PowerMatrix(matrix, power - 1));
    return MultiplyMatrix(matrix, temp);
  }
  Matrix temp(PowerMatrix(matrix, power / 2));
  return MultiplyMatrix(temp, temp);
}

int main() {
  int number_lines;
  long long length;
  std::cin >> number_lines >> length;

  Matrix result(cMaxHeight);
  for (int i = 0; i < result.size; i++) {
    result.data[i][i] = 1;
  }

  long long first_coordinate;
  long long second_coordinate;
  long long height;

  for (int i = 0; i < number_lines; i++) {
    std::cin >> first_coordinate >> second_coordinate >> height;
    Matrix temp(cMaxHeight, height + 1);
    temp = PowerMatrix(temp, second_coordinate - first_coordinate);
    result = MultiplyMatrix(result, temp);
  }

  std::cout << result.data[0][0];
}