#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

bool Comp(std::vector<int>& left, std::vector<int>& right) {
  if (left[2] < right[2]) {
    return true;
  }
  if (left[2] == right[2] && left[0] > right[0]) {
    return true;
  }
  return (left[2] == right[2] && left[0] == right[0] && left[1] > right[1]);
}

int main() {
  int quantity;
  int colors;
  int weight;
  std::cin >> quantity >> colors >> weight;

  std::vector<std::vector<int>> items(quantity, std::vector<int>(3));
  for (int i = 0; i < quantity; i++) {
    std::cin >> items[i][0] >> items[i][1] >> items[i][2];
  }
  std::sort(items.begin(), items.end(), Comp);

  std::vector<std::pair<int, std::set<int>>> dp_prev(
      weight + 1, std::pair<int, std::set<int>>({0, {}}));
  std::vector<std::pair<int, std::set<int>>> dp_next(
      weight + 1, std::pair<int, std::set<int>>({0, {}}));

  for (int i = 1; i <= quantity; i++) {
    for (int j = 1; j <= weight; j++) {
      if ((items[i - 1][0] <= j) &&
          ((dp_prev[j - items[i - 1][0]].first + items[i - 1][1]) >
           dp_prev[j].first) &&
          ((dp_prev[j - items[i - 1][0]].second.find(items[i - 1][2])) ==
           (dp_prev[j - items[i - 1][0]].second.end()))) {
        dp_next[j] = dp_prev[j - items[i - 1][0]];
        dp_next[j].first += items[i - 1][1];
        dp_next[j].second.insert(items[i - 1][2]);
      } else {
        dp_next[j] = dp_prev[j];
      }
    }

    std::swap(dp_prev, dp_next);
    for (int j = 0; j <= weight; j++) {
      dp_next[j] = {0, {}};
    }
  }

  int answer = 0;
  for (int i = 0; i <= weight; i++) {
    answer = std::max(answer, dp_prev[i].first);
  }
  std::cout << answer;
}