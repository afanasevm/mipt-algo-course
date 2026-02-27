#include <algorithm>
#include <iostream>
#include <vector>

const int cMax = 1e9;
const int cMaxCost = 1e5;

struct Graph {
  int size;
  std::vector<std::vector<std::pair<int, int>>> edges_in;
  std::vector<std::vector<int>> dp;
  std::vector<std::vector<int>> prev;

  Graph(int size)
      : size(size),
        edges_in(size),
        dp(size + 1, std::vector<int>(size, cMax)),
        prev(size + 1, std::vector<int>(size, -1)) {}
};

void ReadGraph(Graph& graph) {
  for (int i = 0; i < graph.size; i++) {
    for (int j = 0; j < graph.size; j++) {
      int cost;
      std::cin >> cost;
      if (cost != cMaxCost) {
        graph.edges_in[j].push_back({i, cost});
      }
    }
  }
}

void BellmanFord(Graph& graph) {
  for (int i = 0; i < graph.size; i++) {
    graph.dp[0][i] = 0;
  }
  for (int i = 1; i <= graph.size; i++) {
    for (int j = 0; j < graph.size; j++) {
      graph.dp[i][j] = graph.dp[i - 1][j];
      graph.prev[i][j] = graph.prev[i - 1][j];
      for (std::pair<int, int> to : graph.edges_in[j]) {
        if (graph.dp[i - 1][to.first] != cMax) {
          if (graph.dp[i][j] > graph.dp[i - 1][to.first] + to.second) {
            graph.dp[i][j] = graph.dp[i - 1][to.first] + to.second;
            graph.prev[i][j] = to.first;
          }
        }
      }
    }
  }

  std::pair<int, int> index_modified = {-1, -1};
  for (int i = 0; i < graph.size; i++) {
    if (graph.dp[graph.size][i] < graph.dp[graph.size - 1][i]) {
      index_modified = {graph.size, i};
    }
  }

  if (index_modified == std::make_pair(-1, -1)) {
    std::cout << "NO";
    return;
  }

  std::vector<int> result;
  while (std::count(result.begin(), result.end(), index_modified.second + 1) ==
         0) {
    result.push_back(index_modified.second + 1);
    index_modified = {index_modified.first - 1,
                      graph.prev[index_modified.first][index_modified.second]};
  }
  result.push_back(index_modified.second + 1);
  std::reverse(result.begin(), result.end());
  while (result.back() != result.front()) {
    result.pop_back();
  }

  std::cout << "YES\n" << result.size() << "\n";
  for (int v : result) {
    std::cout << v << " ";
  }
}

int main() {
  int size;
  std::cin >> size;
  Graph graph(size);
  ReadGraph(graph);

  BellmanFord(graph);
}