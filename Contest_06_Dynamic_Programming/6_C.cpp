#include <cmath>
#include <iostream>
#include <vector>

int CalculateTries(int height, int quantity) {
  if (quantity == 0 && height == 1) {
    return 0;
  }
  if (quantity == 0) {
    return -1;
  }
  if (quantity >= ceil(log2(height))) {
    return ceil(log2(height));
  }

  std::vector<std::vector<int>> dp(height + 1,
                                   std::vector<int>(quantity + 1, 1));
  for (int i = 1; i <= height; i++) {
    for (int j = 1; j <= quantity; j++) {
      if (j > i) {
        dp[i][j] = dp[i][i];
      } else {
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      }
    }
  }

  int min_quantity = height;
  for (int i = 0; i <= height; i++) {
    if (dp[i][quantity] >= height && i < min_quantity) {
      min_quantity = i;
    }
  }

  return min_quantity;
}

int main() {
  int height;
  int quantity;
  std::cin >> height >> quantity;

  std::cout << CalculateTries(height, quantity);
}