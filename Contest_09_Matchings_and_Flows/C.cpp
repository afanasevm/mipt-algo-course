#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

enum class Color { White, Gray, Black };

struct Graph {
  int quantity_nodes;
  std::vector<std::set<int>> edges;
  std::vector<Color> color;

  Graph(int left_size, int right_size, std::vector<std::vector<int>>& edjes,
        std::vector<int>& matching)
      : quantity_nodes(left_size + right_size) {
    edges = std::vector<std::set<int>>(quantity_nodes);
    for (int i = 0; i < left_size; i++) {
      for (auto j : edjes[i]) {
        if (j == matching[i]) {
          edges[left_size + j].insert(i);
        } else {
          edges[i].insert(left_size + j);
        }
      }
    }
    color = std::vector<Color>(quantity_nodes, Color::White);
  }
};

void DFS(Graph& graph, int index) {
  graph.color[index] = Color::Gray;
  for (int next_node : graph.edges[index]) {
    if (graph.color[next_node] == Color::White) {
      DFS(graph, next_node);
    }
  }
  graph.color[index] = Color::Black;
}

int main() {
  int left_size;
  int right_size;
  std::cin >> left_size >> right_size;
  std::vector<std::vector<int>> edjes(left_size);
  for (int i = 0; i < left_size; i++) {
    int size;
    std::cin >> size;
    for (int j = 0; j < size; j++) {
      int node;
      std::cin >> node;
      edjes[i].push_back(node - 1);
    }
  }
  std::vector<int> matching(left_size);
  for (int i = 0; i < left_size; i++) {
    std::cin >> matching[i];
    --matching[i];
  }

  Graph graph(left_size, right_size, edjes, matching);
  for (int i = 0; i < left_size; i++) {
    if (matching[i] == -1) {
      DFS(graph, i);
    }
  }

  std::vector<int> result_left;
  for (int i = 0; i < left_size; i++) {
    if (graph.color[i] == Color::White) {
      result_left.push_back(i + 1);
    }
  }
  std::vector<int> result_right;
  for (int i = 0; i < right_size; i++) {
    if (graph.color[i + left_size] == Color::Black) {
      result_right.push_back(i + 1);
    }
  }

  std::cout << result_left.size() + result_right.size() << "\n";
  std::cout << result_left.size() << " ";
  for (int i : result_left) {
    std::cout << i << " ";
  }
  std::cout << "\n";
  std::cout << result_right.size() << " ";
  for (int i : result_right) {
    std::cout << i << " ";
  }
}
