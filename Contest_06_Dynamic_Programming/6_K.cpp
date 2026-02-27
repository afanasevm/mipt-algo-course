#include <algorithm>
#include <iostream>
#include <vector>

const int cMax = 2147483647;

int main() {
  int length;
  std::cin >> length;

  std::vector<int> digits(length + 2);
  digits[0] = -cMax;
  digits[length + 1] = cMax;
  for (int i = 1; i <= length; i++) {
    std::cin >> digits[i];
  }

  std::vector<int> dp(length + 1, 0);
  dp[0] = length + 1;
  std::vector<int> prev(length + 1, -1);
  for (int i = 1; i <= length; i++) {
    std::vector<int>::iterator iter = std::lower_bound(
        dp.begin(), dp.end(), i,
        [&](int left, int right) { return digits[left] >= digits[right]; });
    if (iter != dp.end()) {
      prev[i] = dp[iter - dp.begin() - 1];
      *iter = i;
    }
  }

  int answer = (std::lower_bound(dp.begin(), dp.end(), 0, std::greater<int>()) -
                dp.begin() - 1);
  std::vector<int> result(answer);
  int index = dp[answer];
  for (int i = answer - 1; i >= 0; i--) {
    result[i] = index;
    index = prev[index];
  }

  std::cout << answer << "\n";
  for (int i = 0; i < answer; i++) {
    std::cout << result[i] << " ";
  }
}