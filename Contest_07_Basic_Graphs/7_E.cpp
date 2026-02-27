#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Graph {
  int size;
  std::vector<std::vector<std::pair<int, int>>> graph;
  std::map<std::pair<int, int>, int> edge_count;
  std::vector<int> parent;
  std::vector<bool> visited;

  int timer = 0;
  std::vector<int> tin;
  std::vector<int> tout;

  std::vector<int> ret;

  Graph(int size)
      : size(size),
        graph(size),
        parent(size, -1),
        visited(size, false),
        tin(size),
        tout(size),
        ret(size) {}
};

void ReadGraph(Graph& graph, int edges) {
  int u;
  int v;
  for (int i = 0; i < edges; i++) {
    std::cin >> u >> v;
    graph.graph[u - 1].push_back({v - 1, i});
    graph.graph[v - 1].push_back({u - 1, i});

    graph.edge_count[{std::min(u - 1, v - 1), std::max(u - 1, v - 1)}]++;
  }
}

void DFS(Graph& graph, int index, std::vector<int>& result) {
  graph.visited[index] = true;
  graph.tin[index] = ++graph.timer;
  graph.ret[index] = graph.timer;

  for (std::pair<int, int> to : graph.graph[index]) {
    if (to.first == graph.parent[index]) {
      continue;
    }
    if (!graph.visited[to.first]) {
      graph.parent[to.first] = index;
      DFS(graph, to.first, result);
      graph.ret[index] = std::min(graph.ret[index], graph.ret[to.first]);
      if (graph.ret[to.first] == graph.tin[to.first] &&
          graph.edge_count[{std::min(index, to.first),
                            std::max(index, to.first)}] == 1) {
        result.push_back(to.second);
      }
    } else {
      graph.ret[index] = std::min(graph.ret[index], graph.tin[to.first]);
    }
  }

  graph.tout[index] = ++graph.timer;
}

int main() {
  int nodes;
  int edges;
  std::cin >> nodes >> edges;
  Graph graph(nodes);
  ReadGraph(graph, edges);

  std::vector<int> result;
  for (int i = 0; i < nodes; i++) {
    if (!graph.visited[i]) {
      DFS(graph, i, result);
    }
  }

  std::sort(result.begin(), result.end());
  std::cout << result.size() << "\n";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << result[i] + 1 << " ";
  }
}