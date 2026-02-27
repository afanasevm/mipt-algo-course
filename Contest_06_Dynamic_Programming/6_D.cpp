#include <iostream>
#include <vector>

int main() {
  std::string first;
  std::string second;
  std::cin >> first >> second;

  int length_first = first.length();
  int length_second = second.length();

  std::vector<std::vector<int>> dp(length_first + 1,
                                   std::vector<int>(length_second + 1, 0));
  std::vector<std::vector<int>> prev(length_first + 1,
                                     std::vector<int>(length_second + 1, 0));
  for (int i = 1; i <= length_first; i++) {
    for (int j = 1; j <= length_second; j++) {
      if (first[i - 1] == second[j - 1] &&
          (dp[i - 1][j - 1] + 1) >= std::max(dp[i - 1][j], dp[i][j - 1])) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        prev[i][j] = 0;
      } else if (dp[i - 1][j] >= dp[i][j - 1]) {
        dp[i][j] = dp[i - 1][j];
        prev[i][j] = 1;
      } else {
        dp[i][j] = dp[i][j - 1];
        prev[i][j] = 2;
      }
    }
  }

  std::vector<int> answer_first;
  std::vector<int> answer_second;
  int index_first = length_first;
  int index_second = length_second;
  while (index_first != 0 && index_second != 0) {
    if (prev[index_first][index_second] == 0) {
      answer_first.push_back(index_first);
      answer_second.push_back(index_second);
      index_first--;
      index_second--;
    } else if (prev[index_first][index_second] == 1) {
      index_first--;
    } else {
      index_second--;
    }
  }

  std::cout << dp[length_first][length_second] << "\n";
  for (int i = dp[length_first][length_second] - 1; i >= 0; i--) {
    std::cout << answer_first[i] << " ";
  }
  std::cout << "\n";
  for (int i = dp[length_first][length_second] - 1; i >= 0; i--) {
    std::cout << answer_second[i] << " ";
  }
}