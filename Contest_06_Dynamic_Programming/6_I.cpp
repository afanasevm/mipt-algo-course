#include <iostream>
#include <string>
#include <vector>

const int cMax = 1e4;

int main() {
  std::string first;
  std::string second;
  int quantity;
  std::cin >> first >> second >> quantity;

  std::vector<std::vector<std::vector<int>>> dp(
      first.size() + 1,
      std::vector<std::vector<int>>(second.size() + 1,
                                    std::vector<int>(quantity + 1, cMax)));

  for (int k = 0; k <= quantity; k++) {
    dp[0][0][k] = 0;
  }

  for (size_t i = 0; i <= first.size(); i++) {
    for (size_t k = 0; k <= static_cast<size_t>(quantity); k++) {
      if (i <= k) {
        dp[i][0][k] = 0;
      }
    }
  }

  for (size_t j = 0; j <= second.size(); j++) {
    for (size_t k = 0; k <= static_cast<size_t>(quantity); k++) {
      if (j <= k) {
        dp[0][j][k] = 0;
      }
    }
  }

  for (size_t i = 1; i <= first.size(); i++) {
    for (size_t j = 1; j <= second.size(); j++) {
      for (int k = 0; k <= quantity; k++) {
        if (first[i - 1] == second[j - 1]) {
          dp[i][j][k] = std::min(dp[i][j][k], dp[i - 1][j - 1][k]);
        } else {
          dp[i][j][k] = std::min(dp[i][j][k], dp[i - 1][j - 1][k] + 1);
        }

        if (k > 0) {
          dp[i][j][k] = std::min(dp[i][j][k], dp[i - 1][j][k - 1]);
          dp[i][j][k] = std::min(dp[i][j][k], dp[i][j - 1][k - 1]);
          dp[i][j][k] = std::min(
              dp[i][j][k], dp[i - 1][j - 1][k - 1] +
                               static_cast<int>(first[i - 1] == second[j - 1]));
        }
      }
    }
  }

  int answer = cMax;
  for (int k = 0; k <= quantity; k++) {
    answer = std::min(answer, dp[first.size()][second.size()][k]);
  }
  if (answer == cMax) {
    answer = -1;
  }
  std::cout << answer;
}