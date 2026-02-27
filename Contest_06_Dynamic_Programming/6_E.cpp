#include <iostream>
#include <vector>

int main() {
  int quantity;
  int weight;
  std::cin >> quantity >> weight;

  std::vector<int> weights(quantity);
  std::vector<int> costs(quantity);
  for (int i = 0; i < quantity; i++) {
    std::cin >> weights[i];
  }
  for (int i = 0; i < quantity; i++) {
    std::cin >> costs[i];
  }

  std::vector<std::vector<int>> dp(quantity + 1,
                                   std::vector<int>(weight + 1, 0));
  std::vector<std::vector<int>> prev(quantity + 1,
                                     std::vector<int>(weight + 1, 0));
  for (int i = 1; i <= quantity; i++) {
    for (int j = 1; j <= weight; j++) {
      if (weights[i - 1] <= j &&
          (dp[i - 1][j - weights[i - 1]] + costs[i - 1]) >= dp[i - 1][j]) {
        dp[i][j] = dp[i - 1][j - weights[i - 1]] + costs[i - 1];
        prev[i][j] = j - weights[i - 1];
      } else {
        dp[i][j] = dp[i - 1][j];
        prev[i][j] = j;
      }
    }
  }

  int answer_weight = 0;
  for (int i = 0; i <= weight; i++) {
    if (dp[quantity][i] > dp[quantity][answer_weight]) {
      answer_weight = i;
    }
  }

  int prev_weight;
  for (int i = quantity; i > 0; i--) {
    prev_weight = answer_weight;
    answer_weight = prev[i][answer_weight];
    if (answer_weight != prev_weight) {
      std::cout << i << "\n";
    }
  }
}