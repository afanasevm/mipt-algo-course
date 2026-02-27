#include <climits>
#include <iostream>
#include <queue>
#include <vector>

struct Graph {
  int size;
  int edges;
  int infected;
  std::vector<int> infected_v;
  std::vector<std::vector<std::pair<long, long>>> graph;
  std::vector<long long> time_infected;
  std::vector<long long> dist;
  int start;
  int end;

  Graph(int size, int edges, int infected)
      : size(size),
        edges(edges),
        infected(infected),
        graph(size),
        time_infected(size, LONG_LONG_MAX),
        dist(size, LONG_LONG_MAX) {}
};

void ReadGraph(Graph& graph) {
  for (int i = 0; i < graph.infected; i++) {
    int infect;
    std::cin >> infect;
    graph.infected_v.push_back(infect - 1);
  }

  for (int i = 0; i < graph.edges; i++) {
    int v;
    int to;
    long long cost;
    std::cin >> v >> to >> cost;
    graph.graph[v - 1].push_back({to - 1, cost});
    graph.graph[to - 1].push_back({v - 1, cost});
  }

  std::cin >> graph.start;
  graph.start--;
  std::cin >> graph.end;
  graph.end--;
}

long long Dijkstra(Graph& graph) {
  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>,
                      std::greater<std::pair<long long, int>>>
      not_used;
  for (int i : graph.infected_v) {
    not_used.push({0, i});
  }

  while (!not_used.empty()) {
    std::pair<long long, int> node = not_used.top();
    not_used.pop();
    if (graph.time_infected[node.second] == LONG_LONG_MAX) {
      graph.time_infected[node.second] = node.first;
      for (std::pair<int, long long> to : graph.graph[node.second]) {
        if (graph.time_infected[to.first] == LONG_LONG_MAX) {
          not_used.push({to.second + node.first, to.first});
        }
      }
    }
  }

  if (graph.time_infected[graph.start] == 0) {
    return -1;
  }

  not_used.push({0, graph.start});

  while (!not_used.empty()) {
    std::pair<long long, int> node = not_used.top();
    not_used.pop();
    if (graph.dist[node.second] == LONG_LONG_MAX) {
      graph.dist[node.second] = node.first;
      for (std::pair<int, long long> to : graph.graph[node.second]) {
        if ((graph.dist[to.first] == LONG_LONG_MAX) &&
            (to.second + node.first < graph.time_infected[to.first])) {
          not_used.push({to.second + node.first, to.first});
        }
      }
    }
  }

  if (graph.dist[graph.end] == LONG_LONG_MAX) {
    return -1;
  }

  return graph.dist[graph.end];
}

int main() {
  int size;
  int edges;
  int infected;
  std::cin >> size >> edges >> infected;
  Graph graph(size, edges, infected);
  ReadGraph(graph);

  std::cout << Dijkstra(graph);
}