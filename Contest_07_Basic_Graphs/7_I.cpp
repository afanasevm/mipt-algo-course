#include <iostream>
#include <vector>

struct Graph {
  int size;
  std::vector<std::vector<std::pair<int, int>>> graph;
  std::vector<bool> visited;

  std::vector<int> nodes;
  std::vector<int> edges;

  Graph(int size)
      : size(size), graph(size), visited(size, false), nodes(size) {}
};

void ReadGraph(Graph& graph, int edges) {
  graph.edges = std::vector<int>(edges, 0);

  int u;
  int v;
  for (int i = 0; i < edges; i++) {
    std::cin >> u >> v;
    graph.graph[u - 1].push_back({v - 1, i});
    graph.graph[v - 1].push_back({u - 1, i});
  }

  char c;
  for (int i = 0; i < graph.size; i++) {
    std::cin >> c;
    graph.nodes[i] = c - '0';
  }
}

int DFS(Graph& graph, int index, int parent) {
  graph.visited[index] = true;
  int sum = 0;

  for (std::pair<int, int> to : graph.graph[index]) {
    if (to.first == parent) {
      continue;
    }
    if (!graph.visited[to.first]) {
      int child_sum = DFS(graph, to.first, index);
      graph.edges[to.second] = child_sum;
      sum ^= child_sum;
    }
  }

  return sum ^ graph.nodes[index];
}

void CheckEdgeValues(Graph& graph) {
  for (int i = 0; i < graph.size; i++) {
    int sum = 0;
    for (std::pair<int, int> to : graph.graph[i]) {
      sum ^= graph.edges[to.second];
    }

    if (sum != graph.nodes[i]) {
      std::cout << -1 << "\n";
      return;
    }
  }

  for (int i : graph.edges) {
    std::cout << i;
  }
  std::cout << "\n";
}

void FindEdgesValues(Graph& graph) {
  for (int i = 0; i < graph.size; i++) {
    DFS(graph, i, -1);
  }

  CheckEdgeValues(graph);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int quantity;
  std::cin >> quantity;
  for (int i = 0; i < quantity; i++) {
    int nodes;
    int edges;
    std::cin >> nodes >> edges;
    Graph graph(nodes);
    ReadGraph(graph, edges);

    FindEdgesValues(graph);
  }
}