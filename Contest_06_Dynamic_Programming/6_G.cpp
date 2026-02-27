#include <iostream>
#include <vector>

int main() {
  int number;
  std::cin >> number;

  std::vector<std::vector<long long>> dp(number + 1,
                                         std::vector<long long>(number + 1, 0));
  dp[0][0] = 1;
  for (int i = 1; i <= number; i++) {
    for (int j = i / 2 + 1; j <= i; j++) {
      dp[i][j] = dp[i][j - 1] + dp[i - j][std::min(j / 2, i - j)];
    }
  }

  std::cout << dp[number][number];
}