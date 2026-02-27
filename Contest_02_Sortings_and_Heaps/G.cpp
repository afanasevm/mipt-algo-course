#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int number;
  int quantity;
  long long a_0;
  long long x;
  long long y;
  std::cin >> number >> quantity;
  std::cin >> a_0 >> x >> y;
  const int kTwo = 1073741824;
  std::vector<int> result(quantity);
  for (int i = 0; i < quantity; i++) {
    a_0 = (a_0 * x + y) % kTwo;
    result[i] = a_0;
  }
  std::make_heap(result.begin(), result.end());
  for (int i = 0; i < (number - quantity); i++) {
    a_0 = (a_0 * x + y) % kTwo;
    if (a_0 < result[0]) {
      result.push_back(a_0);
      std::push_heap(result.begin(), result.end());
      std::pop_heap(result.begin(), result.end());
      result.pop_back();
    }
  }
  std::sort(result.begin(), result.end());
  for (int i = 0; i < quantity; i++) {
    std::cout << result[i] << " ";
  }
}