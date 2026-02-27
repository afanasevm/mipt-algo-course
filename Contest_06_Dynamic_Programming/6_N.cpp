#include <iostream>
#include <vector>

int main() {
  int length_first;
  int length_second;
  std::cin >> length_first >> length_second;

  std::vector<int> first(length_first);
  std::vector<int> second(length_second);

  for (int i = 0; i < length_first; i++) {
    std::cin >> first[i];
  }
  for (int i = 0; i < length_second; i++) {
    std::cin >> second[i];
  }

  std::vector<std::vector<int>> dp(length_first + 1,
                                   std::vector<int>(length_second + 1, 0));

  for (int i = 1; i <= length_first; i++) {
    int best_candidate = 0;
    for (int j = 1; j <= length_second; j++) {
      dp[i][j] = dp[i - 1][j];
      if ((first[i - 1] == second[j - 1]) && (dp[i][j] < best_candidate + 1)) {
        dp[i][j] = best_candidate + 1;
      }
      if ((first[i - 1] > second[j - 1]) && dp[i - 1][j] > best_candidate) {
        best_candidate = dp[i - 1][j];
      }
    }
  }

  int result = 0;
  for (int i = 0; i <= length_second; i++) {
    result = std::max(result, dp[length_first][i]);
  }
  std::cout << result;
}