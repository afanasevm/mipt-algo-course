#include <algorithm>
#include <iostream>
#include <vector>

bool Augment(int node, std::vector<bool>& used, std::vector<int>& match,
             std::vector<std::vector<int>>& edjes) {
  if (used[node]) {
    return false;
  }
  used[node] = true;
  for (int to : edjes[node]) {
    if (match[to] == -1 || Augment(match[to], used, match, edjes)) {
      match[to] = node;
      return true;
    }
  }
  return false;
}

std::vector<std::pair<int, int>> MaximumMatching(
    int quantity_nodes_left, int quantity_nodes_right,
    std::vector<std::vector<int>>& edjes) {
  std::vector<bool> used(quantity_nodes_left, false);
  std::vector<int> match(quantity_nodes_right, -1);
  for (int node = 0; node < quantity_nodes_left; node++) {
    if (Augment(node, used, match, edjes)) {
      used = std::vector<bool>(quantity_nodes_left, false);
    }
  }

  std::vector<std::pair<int, int>> result;
  for (int i = 0; i < quantity_nodes_right; i++) {
    if (match[i] != -1) {
      result.push_back({match[i], i});
    }
  }
  return result;
}

int main() {
  int quantity_nodes_left;
  int quantity_nodes_right;
  std::cin >> quantity_nodes_left >> quantity_nodes_right;

  std::vector<std::vector<int>> edjes(quantity_nodes_left);
  for (int i = 0; i < quantity_nodes_left; i++) {
    int temp_value;
    std::cin >> temp_value;
    while (temp_value != 0) {
      edjes[i].push_back(temp_value - 1);
      std::cin >> temp_value;
    }
  }

  std::vector<std::pair<int, int>> answer =
      MaximumMatching(quantity_nodes_left, quantity_nodes_right, edjes);
  std::cout << answer.size() << "\n";
  for (std::pair<int, int> ans : answer) {
    std::cout << ans.first + 1 << " " << ans.second + 1 << "\n";
  }
}
