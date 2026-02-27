#include <iostream>
#include <vector>

int main() {
  const int cMax = 1e6;
  const int cMod = 1e9 + 7;

  int quantity;
  std::cin >> quantity;

  std::vector<int> dp(cMax + 1, 0);
  dp[0] = 1;
  long long sum = 1;

  for (int i = 0; i < quantity; i++) {
    int digit;
    std::cin >> digit;
    int prev = dp[digit];
    dp[digit] = sum;
    sum = (2 * sum - prev + cMod) % cMod;
  }

  std::cout << sum - 1;
}