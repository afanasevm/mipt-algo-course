#include <iostream>
#include <queue>
#include <vector>

const int cMax = 2009000999;

struct Graph {
  int size;
  int edges;
  int start;
  std::vector<std::vector<std::pair<int, int>>> graph;
  std::vector<int> dist;

  Graph(int size, int edges)
      : size(size), edges(edges), graph(size), dist(size, cMax) {}
};

void ReadGraph(Graph& graph) {
  int v;
  int to;
  int cost;
  for (int i = 0; i < graph.edges; i++) {
    std::cin >> v >> to >> cost;
    graph.graph[v].push_back({to, cost});
    graph.graph[to].push_back({v, cost});
  }
  std::cin >> graph.start;
}

void Dijkstra(Graph& graph) {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      not_used;
  not_used.push({0, graph.start});

  while (!not_used.empty()) {
    std::pair<int, int> node = not_used.top();
    not_used.pop();
    if (graph.dist[node.second] == cMax) {
      graph.dist[node.second] = node.first;
      for (size_t i = 0; i < graph.graph[node.second].size(); i++) {
        std::pair<int, int> to = graph.graph[node.second][i];
        if (graph.dist[to.first] == cMax) {
          not_used.push({node.first + to.second, to.first});
        }
      }
    }
  }
}

void PrintDist(Graph& graph) {
  for (int i = 0; i < graph.size; i++) {
    std::cout << graph.dist[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  int quantity;
  std::cin >> quantity;

  for (int i = 0; i < quantity; i++) {
    int size;
    int edges;
    std::cin >> size >> edges;
    Graph graph(size, edges);
    ReadGraph(graph);

    Dijkstra(graph);

    PrintDist(graph);
  }
}