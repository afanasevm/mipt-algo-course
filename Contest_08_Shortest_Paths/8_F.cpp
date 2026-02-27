#include <iostream>
#include <map>
#include <vector>

const int cMax = 1e9 + 1;

struct Graph {
  int size;
  int edges;
  int points;
  std::vector<std::vector<std::pair<int, int>>> graph;
  std::map<std::pair<int, int>, int> index_edges;
  std::vector<int> points_v;
  std::vector<std::vector<std::vector<int>>> dp;
  std::vector<std::vector<std::vector<int>>> prev;

  Graph(int size, int edges, int points)
      : size(size),
        edges(edges),
        points(points),
        graph(size),
        points_v(points),
        dp(size, std::vector<std::vector<int>>(
                     size, std::vector<int>(size + 1, cMax))),
        prev(size, std::vector<std::vector<int>>(
                       size, std::vector<int>(size + 1, -1))) {}
};

void ReadGraph(Graph& graph) {
  for (int i = 0; i < graph.edges; i++) {
    int u;
    int v;
    int cost;
    std::cin >> u >> v >> cost;
    graph.graph[u - 1].push_back({v - 1, -cost});
    graph.index_edges.insert({{u - 1, v - 1}, i + 1});
  }

  for (int i = 0; i < graph.points; i++) {
    std::cin >> graph.points_v[i];
    graph.points_v[i]--;
  }
}

void FindPath(Graph& graph, int u, int v, int k, std::vector<int>& answer) {
  if (u == v) {
    return;
  }
  if (k == 0 || graph.prev[u][v][k] == -1) {
    answer.push_back(graph.index_edges.find({u, v})->second);
    return;
  }

  int mid = graph.prev[u][v][k];
  FindPath(graph, u, mid, k - 1, answer);
  FindPath(graph, mid, v, k - 1, answer);
}

void Floyd(Graph& graph) {
  for (int i = 0; i < graph.size; i++) {
    graph.dp[i][i][0] = 0;
    for (std::pair<int, int> to : graph.graph[i]) {
      graph.dp[i][to.first][0] = to.second;
    }
  }

  for (int k = 1; k <= graph.size; k++) {
    for (int i = 0; i < graph.size; i++) {
      for (int j = 0; j < graph.size; j++) {
        if (graph.dp[i][j][k - 1] >
            graph.dp[i][k - 1][k - 1] + graph.dp[k - 1][j][k - 1]) {
          graph.dp[i][j][k] =
              graph.dp[i][k - 1][k - 1] + graph.dp[k - 1][j][k - 1];
          graph.prev[i][j][k] = k - 1;
        } else {
          graph.dp[i][j][k] = graph.dp[i][j][k - 1];
          graph.prev[i][j][k] = graph.prev[i][j][k - 1];
        }
      }
    }
  }

  std::vector<std::vector<bool>> reach(graph.size,
                                       std::vector<bool>(graph.size, false));
  for (int i = 0; i < graph.size; i++) {
    for (std::pair<int, int> to : graph.graph[i]) {
      reach[i][to.first] = true;
    }
  }
  for (int i = 0; i < graph.size; i++) {
    reach[i][i] = true;
  }

  for (int k = 0; k < graph.size; k++) {
    for (int i = 0; i < graph.size; i++) {
      for (int j = 0; j < graph.size; j++) {
        reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
      }
    }
  }

  for (int i = 0; i < graph.points - 1; i++) {
    int from = graph.points_v[i];
    int to = graph.points_v[i + 1];
    for (int v = 0; v < graph.size; v++) {
      if (reach[from][v] && reach[v][to] && graph.dp[v][v][graph.size] < 0) {
        std::cout << "infinitely kind\n";
        return;
      }
    }
  }

  std::vector<int> answer;
  for (int i = 0; i < graph.points - 1; i++) {
    int u = graph.points_v[i];
    int v = graph.points_v[i + 1];
    FindPath(graph, u, v, graph.size, answer);
  }

  std::cout << answer.size() << "\n";
  for (int v : answer) {
    std::cout << v << " ";
  }
}

int main() {
  int size;
  int edges;
  int points;
  std::cin >> size >> edges >> points;
  Graph graph(size, edges, points);
  ReadGraph(graph);

  Floyd(graph);
}