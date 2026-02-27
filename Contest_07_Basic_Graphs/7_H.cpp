#include <iostream>
#include <vector>

const int cMax = 1e7;

struct Graph {
  int size;
  std::vector<std::vector<std::pair<int, int>>> graph;
  std::vector<bool> visited;

  std::vector<int> coef_x;
  std::vector<int> add_x;

  Graph(int size)
      : size(size),
        graph(size),
        visited(size, false),
        coef_x(size),
        add_x(size) {}
};

void ReadGraph(Graph& graph, int edges) {
  int u;
  int v;
  int cost;
  for (int i = 0; i < edges; i++) {
    std::cin >> u >> v >> cost;
    graph.graph[u - 1].push_back({v - 1, cost});
    graph.graph[v - 1].push_back({u - 1, cost});
  }
}

void DFS(Graph& graph, int index) {
  graph.visited[index] = true;

  for (std::pair<int, int> to : graph.graph[index]) {
    if (!graph.visited[to.first]) {
      graph.coef_x[to.first] = -graph.coef_x[index];
      graph.add_x[to.first] = to.second - graph.add_x[index];
      DFS(graph, to.first);
    }
  }
}

bool CheckX(Graph& graph, int x) {
  std::vector<int> values(graph.size);
  for (int i = 0; i < graph.size; i++) {
    values[i] = graph.coef_x[i] * x + graph.add_x[i];
  }

  std::vector<bool> used(graph.size, false);
  for (int i = 0; i < graph.size; i++) {
    if (used[values[i] - 1]) {
      return false;
    }
    used[values[i] - 1] = true;
  }

  for (int i = 0; i < graph.size; i++) {
    for (std::pair<int, int> to : graph.graph[i]) {
      if (values[i] + values[to.first] != to.second) {
        return false;
      }
    }
  }

  for (int i : values) {
    std::cout << i << " ";
  }
  return true;
}

void FindPermutation(Graph& graph) {
  graph.coef_x[0] = 1;
  graph.add_x[0] = 0;
  DFS(graph, 0);

  int min_x = 1;
  int max_x = cMax;

  for (int i = 0; i < graph.size; i++) {
    if (graph.coef_x[i] == 1) {
      min_x = std::max(min_x, 1 - graph.add_x[i]);
      max_x = std::min(max_x, graph.size - graph.add_x[i]);
    } else {
      min_x = std::max(min_x, graph.add_x[i] - graph.size);
      max_x = std::min(max_x, graph.add_x[i] - 1);
    }
  }

  for (int x = min_x; x <= max_x; x++) {
    if (CheckX(graph, x)) {
      break;
    }
  }
}

int main() {
  int nodes;
  int edges;
  std::cin >> nodes >> edges;
  Graph graph(nodes);
  ReadGraph(graph, edges);

  FindPermutation(graph);
}