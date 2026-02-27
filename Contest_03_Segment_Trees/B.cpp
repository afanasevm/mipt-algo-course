#include <iostream>
#include <vector>

int Min(int first, int second) {
  if (first < second) {
    return first;
  }
  return second;
}

int Max(int first, int second) {
  if (first > second) {
    return first;
  }
  return second;
}

void BuildTreeSegments(std::vector<int>& tree, std::vector<int>& array,
                       std::pair<size_t, size_t> borders, size_t element) {
  if (borders.first == borders.second) {
    tree[element] = array[borders.first];
  } else {
    size_t middle = (borders.first + borders.second) / 2;
    BuildTreeSegments(tree, array, std::pair(borders.first, middle),
                      element * 2 + 1);
    BuildTreeSegments(tree, array, std::pair(middle + 1, borders.second),
                      element * 2 + 2);
    tree[element] = tree[element * 2 + 1] + tree[element * 2 + 2];
  }
}

void UpdateTreeSegments(std::vector<int>& tree,
                        std::pair<size_t, size_t> borders, size_t index,
                        int value, size_t element) {
  if (borders.first == borders.second) {
    tree[element] = value;
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

int SumTreeSegments(std::vector<int>& tree, std::pair<size_t, size_t> borders,
                    std::pair<size_t, size_t> indexes, size_t element) {
  if (indexes.first > indexes.second) {
    return 0;
  }
  if (indexes == borders) {
    return tree[element];
  }
  size_t middle = (borders.first + borders.second) / 2;
  return SumTreeSegments(tree, std::pair(borders.first, middle),
                         std::pair(indexes.first, Min(middle, indexes.second)),
                         element * 2 + 1) +
         SumTreeSegments(
           tree, std::pair(middle + 1, borders.second),
           std::pair(Max(middle + 1, indexes.first), indexes.second),
           element * 2 + 2);
}

int main() {
  size_t length;
  std::cin >> length;
  std::vector<int> array(length);
  for (size_t i = 0; i < length; i++) {
    std::cin >> array[i];
    if (i % 2 != 0) {
      array[i] = -array[i];
    }
  }
  std::vector<int> tree(length * 4);
  BuildTreeSegments(tree, array, std::pair(0, length - 1), 0);
  int quantity;
  std::cin >> quantity;
  int command;
  int digit1;
  int digit2;
  int result;
  for (int i = 0; i < quantity; i++) {
    std::cin >> command >> digit1 >> digit2;
    if (command == 1) {
      result = SumTreeSegments(tree, std::pair(0, length - 1),
                               std::pair(digit1 - 1, digit2 - 1), 0);
      if (digit1 % 2 == 0) {
        result = -result;
      }
      std::cout << result << '\n';
    } else {
      if (digit1 % 2 == 0) {
        digit2 = -digit2;
      }
      UpdateTreeSegments(tree, std::pair(0, length - 1), digit1 - 1, digit2, 0);
    }
  }
}