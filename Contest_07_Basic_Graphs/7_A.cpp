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

  int index_cycle = -1;

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
      graph.parent[to] = index;
      graph.index_cycle = to;
    }
  }

  graph.color[index] = Color::Black;
  graph.tout[index] = ++graph.timer;
}

void FindCycle(Graph& graph) {
  if (graph.index_cycle == -1) {
    std::cout << "NO";
    return;
  }

  std::vector<int> answer;
  answer.push_back(graph.index_cycle);
  while (graph.parent[answer.back()] != graph.index_cycle) {
    answer.push_back(graph.parent[answer.back()]);
  }
  std::reverse(answer.begin(), answer.end());

  std::cout << "YES"
            << "\n";
  for (size_t i = 0; i < answer.size(); i++) {
    std::cout << answer[i] + 1 << " ";
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

  FindCycle(graph);
}