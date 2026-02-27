#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

enum struct Color { White, Black };

struct Graph {
  int size;
  std::vector<std::set<int>> graph;
  std::vector<int> parent;
  std::vector<Color> color;

  int timer = 0;
  std::vector<int> tin;
  std::vector<int> tout;

  std::vector<int> component;

  Graph(int size)
      : size(size),
        graph(size),
        parent(size, -1),
        color(size, Color::White),
        tin(size),
        tout(size),
        component(size) {}
};

void ReadGraph(Graph& graph, int edges) {
  int u;
  int v;
  for (int i = 0; i < edges; i++) {
    std::cin >> u >> v;
    graph.graph[u - 1].insert(v - 1);
    graph.graph[v - 1].insert(u - 1);
  }
}

void DFS(Graph& graph, int index, int component) {
  graph.color[index] = Color::Black;
  graph.tin[index] = ++graph.timer;
  graph.component[index] = component;

  for (int to : graph.graph[index]) {
    if (graph.color[to] == Color::White) {
      graph.parent[to] = index;
      DFS(graph, to, component);
    }
  }

  graph.tout[index] = ++graph.timer;
}

void PrintComponent(Graph& graph, int quantity) {
  std::vector<std::vector<int>> components(quantity);
  for (int i = 0; i < graph.size; i++) {
    components[graph.component[i]].push_back(i);
  }

  std::cout << quantity << "\n";
  for (int i = 0; i < quantity; i++) {
    std::cout << components[i].size() << "\n";
    for (size_t j = 0; j < components[i].size(); j++) {
      std::cout << components[i][j] + 1 << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  int nodes;
  int edges;
  std::cin >> nodes >> edges;
  Graph graph(nodes);
  ReadGraph(graph, edges);

  int j = 0;
  for (int i = 0; i < nodes; i++) {
    if (graph.color[i] == Color::White) {
      DFS(graph, i, j++);
    }
  }

  PrintComponent(graph, j);
}