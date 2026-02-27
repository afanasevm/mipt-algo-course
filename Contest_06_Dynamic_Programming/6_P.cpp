#include <iostream>
#include <vector>

const int cMod = 1000000009;

struct Matrix {
  long long up_left;
  long long up_right;
  long long down_left;
  long long down_right;
};

Matrix MultiplyMatrix(Matrix& first, Matrix& second) {
  Matrix result;
  result.up_left =
      (first.up_left * second.up_left + first.up_right * second.down_left) %
      cMod;
  result.up_right =
      (first.up_left * second.up_right + first.up_right * second.down_right) %
      cMod;
  result.down_left =
      (first.down_left * second.up_left + first.down_right * second.down_left) %
      cMod;
  result.down_right = (first.down_left * second.up_right +
                       first.down_right * second.down_right) %
                      cMod;
  return result;
}

Matrix PowerMatrix(Matrix matrix, long long power) {
  if (power == 0) {
    return Matrix{1, 0, 0, 1};
  }
  if (power % 2 == 1) {
    Matrix temp = PowerMatrix(matrix, power - 1);
    return MultiplyMatrix(temp, matrix);
  }
  Matrix temp = PowerMatrix(matrix, power / 2);
  return MultiplyMatrix(temp, temp);
}

long long CalculateFibonacci(long long number) {
  if (number == 0) {
    return 1;
  }
  if (number < 0) {
    return 0;
  }
  return PowerMatrix({1, 1, 1, 0}, number).up_left % cMod;
}

int main() {
  int number_platforms;
  int number_lines;
  std::cin >> number_platforms >> number_lines;
  std::vector<std::vector<long long>> platforms(number_platforms,
                                                std::vector<long long>(3));

  for (int i = 0; i < number_platforms; i++) {
    std::cin >> platforms[i][0] >> platforms[i][1] >> platforms[i][2];
    platforms[i][2] %= cMod;
  }

  long long line;
  long long result;
  for (int i = 0; i < number_lines; i++) {
    std::cin >> line;
    result = 0;
    for (int j = 0; j < number_platforms; j++) {
      result = (CalculateFibonacci(platforms[j][1] - platforms[j][0] - line) *
                    platforms[j][2] +
                result) %
               cMod;
    }
    std::cout << result << "\n";
  }
}