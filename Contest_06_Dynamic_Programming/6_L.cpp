#include <iostream>
#include <vector>

bool IsSameSign(int first, int second, int third) {
  return ((first < second && second < third) ||
          (first > second && second > third));
}

int main() {
  int quantity;
  std::cin >> quantity;

  std::vector<int> result(1);
  std::cin >> result[0];

  for (int i = 1; i < quantity; i++) {
    int digit;
    std::cin >> digit;

    if (digit == result.back()) {
      continue;
    }

    if (result.size() == 1) {
      result.push_back(digit);
      continue;
    }

    if (IsSameSign(result[result.size() - 2], result[result.size() - 1],
                   digit)) {
      result.pop_back();
    }

    result.push_back(digit);
  }

  std::cout << result.size() << "\n";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << result[i] << " ";
  }
}