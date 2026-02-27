#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int Max(int first, int second) {
  if (first > second) {
    return first;
  }
  return second;
}

int Min(int first, int second) {
  if (first < second) {
    return first;
  }
  return second;
}

void UpdateTreeSegments(std::vector<int>& tree,
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

int Cheer(std::vector<int>& tree, std::pair<size_t, size_t> borders,
          std::pair<size_t, size_t> indexes, size_t element) {
  if (indexes.first > indexes.second) {
    return 0;
  }
  if (indexes == borders) {
    return tree[element];
  }
  size_t middle = (borders.first + borders.second) / 2;
  return Cheer(tree, std::pair(borders.first, middle),
               std::pair(indexes.first, Min(middle, indexes.second)),
               element * 2 + 1) +
         Cheer(tree, std::pair(middle + 1, borders.second),
               std::pair(Max(middle + 1, indexes.first), indexes.second),
               element * 2 + 2);
}

int main() {
  const int kLength = 42195;
  const int kUsers = 100000;
  const int kSymbols = 6;
  std::vector<int> tree(kLength * 4);
  size_t quantity_users = 0;
  std::vector users(kUsers, 0);
  int quantity;
  std::cin >> quantity;
  std::string instruction;
  size_t user;
  int time;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction;
    if (instruction == "RUN") {
      std::cin >> user >> time;
      if (users[user - 1] == 0) {
        quantity_users += 1;
      } else {
        UpdateTreeSegments(tree, std::pair(0, kLength - 1), users[user - 1], -1,
                           0);
      }
      users[user - 1] = time;
      UpdateTreeSegments(tree, std::pair(0, kLength - 1), time, 1, 0);
    } else if (instruction == "CHEER") {
      std::cin >> user;
      if (users[user - 1] == 0) {
        std::cout << 0 << '\n';
      } else if (quantity_users == 1) {
        std::cout << 1 << '\n';
      } else {
        std::cout << std::setprecision(kSymbols)
                  << static_cast<float>(Cheer(tree, std::pair(0, kLength - 1),
                                              std::pair(0, users[user - 1] - 1),
                                              0)) /
                     (quantity_users - 1)
                  << '\n';
      }
    }
  }
}