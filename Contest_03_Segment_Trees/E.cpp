#include <algorithm>
#include <iostream>
#include <vector>

void UpdateTreeSegments(std::vector<long long>& tree,
                        std::pair<size_t, size_t> borders, size_t index,
                        int value, size_t element) {
  if (borders.first == borders.second) {
    tree[element] += value;
  } else {
    size_t middle = (borders.first + borders.second) / 2;
    if (index <= middle) {
      UpdateTreeSegments(tree, std::pair(borders.first, middle), index, value,
                         element * 2 + 1);
    } else {
      UpdateTreeSegments(tree, std::pair(middle + 1, borders.second), index,
                         value, element * 2 + 2);
    }
    tree[element] = tree[element * 2 + 1] + tree[element * 2 + 2];
  }
}

long long SumTreeSegments(std::vector<long long>& tree,
                          std::pair<size_t, size_t> borders,
                          std::pair<size_t, size_t> indexes, size_t element) {
  if (indexes.first > indexes.second) {
    return 0;
  }
  if (indexes == borders) {
    return tree[element];
  }
  size_t middle = (borders.first + borders.second) / 2;
  return SumTreeSegments(
    tree, std::pair(borders.first, middle),
    std::pair(indexes.first, std::min(middle, indexes.second)),
    element * 2 + 1) +
         SumTreeSegments(
           tree, std::pair(middle + 1, borders.second),
           std::pair(std::max(middle + 1, indexes.first), indexes.second),
           element * 2 + 2);
}

int BinarySearch(std::vector<int>& digits, int value) {
  int left = 0;
  int right = digits.size() - 1;
  while (left < right) {
    int middle = (left + right) / 2;
    if (digits[middle] < value) {
      left = middle + 1;
    } else if (digits[middle] == value) {
      left = middle;
      break;
    } else {
      right = middle - 1;
    }
  }
  return left;
}

int main() {
  int quantity;
  std::cin >> quantity;
  std::vector<std::pair<char, int>> requests(quantity);
  std::vector<int> digits_raw;
  int number;
  char instruction;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction >> number;
    digits_raw.push_back(number);
    requests[i] = std::pair(instruction, number);
  }
  std::sort(digits_raw.begin(), digits_raw.end());
  std::vector<int> digits = {digits_raw[0]};
  for (size_t i = 1; i < digits_raw.size(); i++) {
    if (digits_raw[i] != digits_raw[i - 1]) {
      digits.push_back(digits_raw[i]);
    }
  }
  int length = digits.size();
  std::vector<long long> tree(length * 4, 0);
  for (int i = 0; i < quantity; i++) {
    if (requests[i].first == '+') {
      int index = BinarySearch(digits, requests[i].second);
      UpdateTreeSegments(tree, std::pair(0, length - 1), index,
                         requests[i].second, 0);
    } else if (requests[i].first == '?') {
      int index = BinarySearch(digits, requests[i].second);
      std::cout << SumTreeSegments(tree, std::pair(0, length - 1),
                                   std::pair(0, index), 0)
                << '\n';
    }
  }
}