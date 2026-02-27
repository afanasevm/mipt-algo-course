#include <iostream>
#include <vector>

const int cMax = 30000;

struct Graph {
  int size;
  int edges;
  std::vector<std::vector<std::pair<int, int>>> edges_in;
  std::vector<std::vector<int>> dp;

  Graph(int size, int edges)
      : size(size),
        edges(edges),
        edges_in(size),
        dp(size, std::vector<int>(size, cMax)) {}
};

void ReadGraph(Graph& graph) {
  for (int i = 0; i < graph.edges; i++) {
    int v;
    int to;
    int cost;
    std::cin >> v >> to >> cost;
    graph.edges_in[to - 1].push_back({v - 1, cost});
  }
}

void BellmanFord(Graph& graph) {
  graph.dp[0][0] = 0;
  for (int i = 1; i < graph.size; i++) {
    for (int j = 0; j < graph.size; j++) {
      graph.dp[i][j] = graph.dp[i - 1][j];
      for (std::pair<int, int> to : graph.edges_in[j]) {
        if (graph.dp[i - 1][to.first] != cMax) {
          graph.dp[i][j] =
              std::min(graph.dp[i][j], graph.dp[i - 1][to.first] + to.second);
        }
      }
    }
  }

  for (int v : graph.dp[graph.size - 1]) {
    std::cout << v << " ";
  }
}

int main() {
  int size;
  int edges;
  std::cin >> size >> edges;
  Graph graph(size, edges);
  ReadGraph(graph);

  BellmanFord(graph);
}