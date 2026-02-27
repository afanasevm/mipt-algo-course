#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

struct Graph {
  int size;
  int edges;
  int time;
  std::vector<std::vector<std::tuple<int, int, int>>> graph;
  std::vector<std::vector<int>> min_cost;
  std::vector<std::vector<std::pair<int, int>>> prev;
  int start;
  int end;

  Graph(int size, int edges, int time)
      : size(size),
        edges(edges),
        time(time),
        graph(size),
        min_cost(size, std::vector<int>(time + 1, INT_MAX)),
        prev(size, std::vector<std::pair<int, int>>(time + 1, {-1, -1})),
        start(0),
        end(size - 1) {}
};

void ReadGraph(Graph& graph) {
  for (int i = 0; i < graph.edges; i++) {
    int v;
    int to;
    int cost;
    int time;
    std::cin >> v >> to >> cost >> time;
    graph.graph[v - 1].push_back({to - 1, cost, time});
    graph.graph[to - 1].push_back({v - 1, cost, time});
  }
}

void Dijkstra(Graph& graph) {
  using Node = std::tuple<int, int, int>;
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> not_used;

  not_used.push({0, 0, 0});

  while (!not_used.empty()) {
    Node node = not_used.top();
    not_used.pop();
    if (graph.min_cost[std::get<2>(node)][std::get<1>(node)] <
        std::get<0>(node)) {
      continue;
    }
    graph.min_cost[std::get<2>(node)][std::get<1>(node)] = std::get<0>(node);
    for (Node to : graph.graph[std::get<2>(node)]) {
      int new_time = std::get<2>(to) + std::get<1>(node);
      if (new_time > graph.time) {
        continue;
      }
      if (graph.min_cost[std::get<0>(to)][new_time] >
          std::get<0>(node) + std::get<1>(to)) {
        graph.min_cost[std::get<0>(to)][new_time] =
            std::get<0>(node) + std::get<1>(to);
        graph.prev[std::get<0>(to)][new_time] = {std::get<2>(node),
                                                 std::get<1>(node)};
        not_used.push(
            {std::get<0>(node) + std::get<1>(to), new_time, std::get<0>(to)});
      }
    }
  }

  int ind_ans = -1;
  int ans = INT_MAX;
  for (int i = 0; i <= graph.time; i++) {
    if (graph.min_cost[graph.size - 1][i] < ans) {
      ans = graph.min_cost[graph.size - 1][i];
      ind_ans = i;
    }
  }

  if (ind_ans == -1) {
    std::cout << -1;
    return;
  }

  std::cout << ans << "\n";

  std::vector<int> path;
  int cur_v = graph.end;
  int cur_time = ind_ans;
  while (cur_v != 0) {
    path.push_back(cur_v);
    int prev_v = graph.prev[cur_v][cur_time].first;
    int prev_time = graph.prev[cur_v][cur_time].second;
    cur_v = prev_v;
    cur_time = prev_time;
  }
  path.push_back(0);
  std::reverse(path.begin(), path.end());

  std::cout << path.size() << "\n";
  for (int v : path) {
    std::cout << v + 1 << " ";
  }
}

int main() {
  int size;
  int edges;
  int time;
  std::cin >> size >> edges >> time;
  Graph graph(size, edges, time);
  ReadGraph(graph);

  Dijkstra(graph);
}