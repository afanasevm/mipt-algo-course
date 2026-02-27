#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_set>

const int cQuantity = 9;
const std::string cFinal = "123456780";
const std::vector<std::tuple<int, int, char>> cMoves{
    {-1, 0, 'U'}, {1, 0, 'D'}, {0, 1, 'R'}, {0, -1, 'L'}};

void BFS(std::string start_position) {
  std::queue<std::pair<std::string, std::string>> queue;
  queue.push({start_position, ""});
  std::unordered_set<std::string> visited;

  while (!queue.empty()) {
    auto [position, path] = queue.front();
    queue.pop();
    visited.insert(position);

    if (position == cFinal) {
      std::cout << path.size() << "\n";
      std::cout << path;
      return;
    }

    int ind_zero = position.find("0");
    int x = ind_zero / 3;
    int y = ind_zero % 3;

    for (auto [dx, dy, direction] : cMoves) {
      int new_x = x + dx;
      int new_y = y + dy;
      if (new_x > 2 || new_x < 0 || new_y > 2 || new_y < 0) {
        continue;
      }
      int new_ind_zero = new_x * 3 + new_y;
      std::string new_position = position;
      new_position[ind_zero] = new_position[new_ind_zero];
      new_position[new_ind_zero] = '0';

      if (visited.find(new_position) == visited.end()) {
        queue.push({new_position, path + direction});
      }
    }
  }

  std::cout << -1;
}

int main() {
  std::string position;
  for (int i = 0; i < cQuantity; i++) {
    char c;
    std::cin >> c;
    position += c;
  }

  BFS(position);
}