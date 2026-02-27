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
  int height;
  int length;
  int cost_a;
  int cost_b;
  std::cin >> height >> length >> cost_a >> cost_b;
  cost_a = std::min(cost_a, 2 * cost_b);
  int quantity_free = height * length;
  std::vector<std::vector<bool>> table(height,
                                       std::vector<bool>(length, false));
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < length; j++) {
      char chr;
      std::cin >> chr;
      if (chr == '.') {
        table[i][j] = true;
        --quantity_free;
      }
    }
  }

  std::vector<std::vector<int>> edjes(height * length);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < length; j++) {
      if ((i + j) % 2 == 0 && !table[i][j]) {
        if (i > 0 && !table[i - 1][j]) {
          edjes[i * length + j].push_back((i - 1) * length + j);
        }
        if (i < (height - 1) && !table[i + 1][j]) {
          edjes[i * length + j].push_back((i + 1) * length + j);
        }
        if (j > 0 && !table[i][j - 1]) {
          edjes[i * length + j].push_back(i * length + j - 1);
        }
        if (j < (length - 1) && !table[i][j + 1]) {
          edjes[i * length + j].push_back(i * length + j + 1);
        }
      }
    }
  }

  int answer = MaximumMatching(height * length, height * length, edjes).size();
  std::cout << (quantity_free - answer * 2) * cost_b + cost_a * answer;
}
