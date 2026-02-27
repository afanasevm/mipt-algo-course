#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

enum struct Color { White, Grey, Black };

struct Graph {
  int size;
  std::vector<std::set<int>> graph;
  std::vector<int> parent;
  std::vector<Color> color;

  int timer = 0;
  std::vector<int> tin;
  std::vector<int> tout;

  bool acyclic = true;

  Graph(int size)
      : size(size),
        graph(size),
        parent(size, -1),
        color(size, Color::White),
        tin(size),
        tout(size) {}
};

void ReadGraph(Graph& graph, int edges) {
  int u;
  int v;
  for (int i = 0; i < edges; i++) {
    std::cin >> u >> v;
    graph.graph[u - 1].insert(v - 1);
  }
}

void DFS(Graph& graph, int index) {
  graph.color[index] = Color::Grey;
  graph.tin[index] = ++graph.timer;

  for (int to : graph.graph[index]) {
    if (graph.color[to] == Color::White) {
      graph.parent[to] = index;
      DFS(graph, to);
    }
    if (graph.color[to] == Color::Grey) {
      graph.acyclic = false;
    }
  }

  graph.color[index] = Color::Black;
  graph.tout[index] = ++graph.timer;
}

void PrintTopSort(Graph& graph) {
  if (!graph.acyclic) {
    std::cout << -1;
    return;
  }

  std::vector<std::pair<int, int>> sorted_nodes(graph.size);
  for (int i = 0; i < graph.size; i++) {
    sorted_nodes[i] = {graph.tout[i], i};
  }
  std::sort(sorted_nodes.begin(), sorted_nodes.end(),
            std::greater<std::pair<int, int>>());
  for (int i = 0; i < graph.size; i++) {
    std::cout << sorted_nodes[i].second + 1 << " ";
  }
}

int main() {
  int nodes;
  int edges;
  std::cin >> nodes >> edges;
  Graph graph(nodes);
  ReadGraph(graph, edges);

  for (int i = 0; i < nodes; i++) {
    if (graph.color[i] == Color::White) {
      DFS(graph, i);
    }
  }

  PrintTopSort(graph);
}