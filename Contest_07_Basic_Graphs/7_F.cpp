#include <iostream>
#include <set>
#include <vector>

struct Graph {
  int size;
  std::vector<std::vector<int>> graph;
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
    graph.graph[u - 1].push_back(v - 1);
    graph.graph[v - 1].push_back(u - 1);
  }
}

void DFS(Graph& graph, int index, std::set<int>& result, bool is_root) {
  graph.visited[index] = true;
  graph.tin[index] = ++graph.timer;
  graph.ret[index] = graph.timer;
  int count = 0;

  for (int to : graph.graph[index]) {
    if (to == graph.parent[index]) {
      continue;
    }
    if (!graph.visited[to]) {
      count++;
      graph.parent[to] = index;
      DFS(graph, to, result, false);
      graph.ret[index] = std::min(graph.ret[index], graph.ret[to]);
      if (!is_root && graph.ret[to] >= graph.tin[index]) {
        result.insert(index);
      }
    } else {
      graph.ret[index] = std::min(graph.ret[index], graph.tin[to]);
    }
  }

  if (is_root && count > 1) {
    result.insert(index);
  }

  graph.tout[index] = ++graph.timer;
}

int main() {
  int nodes;
  int edges;
  std::cin >> nodes >> edges;
  Graph graph(nodes);
  ReadGraph(graph, edges);

  std::set<int> result;
  for (int i = 0; i < nodes; i++) {
    if (!graph.visited[i]) {
      DFS(graph, i, result, true);
    }
  }

  std::cout << result.size() << "\n";
  for (int node : result) {
    std::cout << node + 1 << " ";
  }
}