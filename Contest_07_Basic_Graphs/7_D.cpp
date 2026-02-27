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

void ReadGraph(Graph& graph, Graph& graph_rev, int edges) {
  int u;
  int v;
  for (int i = 0; i < edges; i++) {
    std::cin >> u >> v;
    graph.graph[u - 1].insert(v - 1);
    graph_rev.graph[v - 1].insert(u - 1);
  }
}

void DFS(Graph& graph, int index, int component) {
  graph.color[index] = Color::Grey;
  graph.tin[index] = ++graph.timer;
  graph.component[index] = component;

  for (int to : graph.graph[index]) {
    if (graph.color[to] == Color::White) {
      graph.parent[to] = index;
      DFS(graph, to, component);
    }
  }

  graph.color[index] = Color::Black;
  graph.tout[index] = ++graph.timer;
}

void FindStrongComponents(Graph& graph, Graph& graph_rev) {
  for (int i = 0; i < graph.size; i++) {
    if (graph.color[i] == Color::White) {
      DFS(graph, i, 0);
    }
  }

  std::vector<std::pair<int, int>> sorted_nodes(graph.size);
  for (int i = 0; i < graph.size; i++) {
    sorted_nodes[i] = {graph.tout[i], i};
  }
  std::sort(sorted_nodes.begin(), sorted_nodes.end(),
            std::greater<std::pair<int, int>>());

  int j = 1;
  for (int i = 0; i < graph_rev.size; i++) {
    if (graph_rev.color[sorted_nodes[i].second] == Color::White) {
      DFS(graph_rev, sorted_nodes[i].second, j++);
    }
  }

  std::cout << j - 1 << "\n";
  for (int i = 0; i < graph_rev.size; i++) {
    std::cout << graph_rev.component[i] << " ";
  }
}

int main() {
  int nodes;
  int edges;
  std::cin >> nodes >> edges;
  Graph graph(nodes);
  Graph graph_rev(nodes);
  ReadGraph(graph, graph_rev, edges);

  FindStrongComponents(graph, graph_rev);
}