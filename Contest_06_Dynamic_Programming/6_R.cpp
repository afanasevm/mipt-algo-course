#include <iostream>
#include <vector>

const int cMax = 1e9;

int main() {
  int size;
  std::cin >> size;

  std::vector<std::vector<int>> graph(size, std::vector<int>(size));
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      std::cin >> graph[i][j];
    }
  }

  std::vector<std::vector<int>> dp((1 << size), std::vector<int>(size, cMax));
  std::vector<std::vector<int>> prev((1 << size), std::vector<int>(size, -1));

  for (int i = 0; i < size; i++) {
    dp[0][i] = 0;
  }

  for (int mask = 0; mask < (1 << size); mask++) {
    for (int i = 0; i < size; i++) {
      if ((mask & (1 << i)) != 0) {
        for (int j = 0; j < size; j++) {
          if (dp[mask - (1 << i)][j] + graph[i][j] < dp[mask][i]) {
            dp[mask][i] = dp[mask - (1 << i)][j] + graph[i][j];
            prev[mask][i] = j;
          }
        }
      }
    }
  }

  int answer = cMax;
  int index;
  int mask = (1 << size) - 1;
  for (int i = 0; i < size; i++) {
    if (dp[mask][i] < answer) {
      answer = dp[mask][i];
      index = i;
    }
  }

  std::cout << answer << "\n";
  for (int i = 0; i < size; i++) {
    std::cout << index + 1 << " ";
    int prev_index = index;
    index = prev[mask][index];
    mask -= 1 << prev_index;
  }
}