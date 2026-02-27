#include <iostream>
#include <vector>

struct Graph {
  int size;
  std::vector<std::vector<bool>> reach;

  Graph(int size) : size(size), reach(size, std::vector<bool>(size, false)) {}
};

void ReadGraph(Graph& graph) {
  for (int i = 0; i < graph.size; i++) {
    for (int j = 0; j < graph.size; j++) {
      int k;
      std::cin >> k;
      graph.reach[i][j] = (k != 0);
    }
  }
}

void Floyd(Graph& graph) {
  for (int k = 0; k < graph.size; k++) {
    for (int i = 0; i < graph.size; i++) {
      for (int j = 0; j < graph.size; j++) {
        graph.reach[i][j] =
            graph.reach[i][j] || (graph.reach[i][k] && graph.reach[k][j]);
      }
    }
  }

  for (int i = 0; i < graph.size; i++) {
    for (int j = 0; j < graph.size; j++) {
      if (graph.reach[i][j]) {
        std::cout << "1 ";
      } else {
        std::cout << "0 ";
      }
    }
    std::cout << "\n";
  }
}

int main() {
  int size;
  std::cin >> size;
  Graph graph(size);
  ReadGraph(graph);

  Floyd(graph);
}