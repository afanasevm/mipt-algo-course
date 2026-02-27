#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void UpdateTree(std::vector<std::vector<int>>& tree, size_t size, size_t first,
                size_t second) {
  for (size_t i = first; i < size; i = i | (i + 1)) {
    for (size_t j = second; j < size; j = j | (j + 1)) {
      tree[i][j] += 1;
    }
  }
}

int GetPrefSum(std::vector<std::vector<int>>& tree, int x1, int y1) {
  int result = 0;
  for (int i = x1; i >= 0; i = (i & (i + 1)) - 1) {
    for (int j = y1; j >= 0; j = (j & (j + 1)) - 1) {
      result += tree[i][j];
    }
  }
  return result;
}

int GetRectangleSum(std::vector<std::vector<int>>& tree, size_t x1, size_t y1,
                    size_t x2, size_t y2) {
  return GetPrefSum(tree, x2, y2) - GetPrefSum(tree, x1 - 1, y2) -
         GetPrefSum(tree, x2, y1 - 1) + GetPrefSum(tree, x1 - 1, y1 - 1);
}

int main() {
  int size;
  int quantity;
  std::cin >> size >> quantity;
  std::vector<std::vector<int>> tree(size, std::vector<int>(size, 0));
  std::string instruction;
  size_t x1;
  size_t y1;
  size_t x2;
  size_t y2;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction;
    if (instruction == "ADD") {
      std::cin >> x1 >> y1;
      UpdateTree(tree, size, x1 - 1, y1 - 1);
    } else if (instruction == "GET") {
      std::cin >> x1 >> y1 >> x2 >> y2;
      std::cout << GetRectangleSum(tree, std::min(x1, x2) - 1,
                                   std::min(y1, y2) - 1, std::max(x1, x2) - 1,
                                   std::max(y1, y2) - 1)
                << '\n';
    }
  }
}