#include <iostream>
#include <set>
#include <vector>

struct Graph {
  int size;
  std::vector<std::set<int>> graph;
  std::vector<int> parent;
  std::vector<bool> visited;

  int timer = 0;
  std::vector<int> tin;
  std::vector<int> tout;

  std::vector<int> ret;
  std::vector<int> component;

  Graph(int size)
      : size(size),
        graph(size),
        parent(size, -1),
        visited(size, false),
        tin(size),
        tout(size),
        ret(size),
        component(size) {}
};

void ReadGraph(Graph& graph, int edges) {
  int u;
  int v;
  for (int i = 0; i < edges; i++) {
    std::cin >> u >> v;
    graph.graph[u - 1].insert(v - 1);
    graph.graph[v - 1].insert(u - 1);
  }
}

void DFSFindBridges(Graph& graph, int index,
                    std::set<std::pair<int, int>>& bridges) {
  graph.visited[index] = true;
  graph.tin[index] = ++graph.timer;
  graph.ret[index] = graph.timer;

  for (int to : graph.graph[index]) {
    if (to == graph.parent[index]) {
      continue;
    }
    if (!graph.visited[to]) {
      graph.parent[to] = index;
      DFSFindBridges(graph, to, bridges);
      graph.ret[index] = std::min(graph.ret[index], graph.ret[to]);
      if (graph.ret[to] == graph.tin[to]) {
        bridges.insert({index, to});
      }
    } else {
      graph.ret[index] = std::min(graph.ret[index], graph.tin[to]);
    }
  }
  graph.tout[index] = ++graph.timer;
}

void DFS(Graph& graph, int index, int component) {
  graph.visited[index] = true;
  graph.tin[index] = ++graph.timer;
  graph.component[index] = component;

  for (int to : graph.graph[index]) {
    if (to == graph.parent[index]) {
      continue;
    }
    if (!graph.visited[to]) {
      graph.parent[to] = index;
      DFS(graph, to, component);
    }
  }
  graph.tout[index] = ++graph.timer;
}

int DFSCountLeaves(Graph& graph, int index) {
  int result = 0;
  int count = 0;
  graph.visited[index] = true;
  graph.tin[index] = ++graph.timer;

  for (int to : graph.graph[index]) {
    count++;
    if (to == graph.parent[index]) {
      continue;
    }
    if (!graph.visited[to]) {
      graph.parent[to] = index;
      result += DFSCountLeaves(graph, to);
    }
  }
  graph.tout[index] = ++graph.timer;

  if (count == 1) {
    result++;
  }
  return result;
}

void CompressComponents(Graph& graph, std::set<std::pair<int, int>>& bridges) {
  for (std::pair<int, int> bridge : bridges) {
    graph.graph[bridge.first].erase(bridge.second);
    graph.graph[bridge.second].erase(bridge.first);
  }

  graph.parent = std::vector<int>(graph.size, -1);
  graph.visited = std::vector<bool>(graph.size, false);
  graph.tin = std::vector<int>(graph.size);
  graph.tout = std::vector<int>(graph.size);
  graph.timer = 0;

  int components = 0;
  for (int i = 0; i < graph.size; i++) {
    if (!graph.visited[i]) {
      DFS(graph, i, components++);
    }
  }

  Graph compressed_graph(components);
  for (std::pair<int, int> edge : bridges) {
    compressed_graph.graph[graph.component[edge.first]].insert(
        graph.component[edge.second]);
    compressed_graph.graph[graph.component[edge.second]].insert(
        graph.component[edge.first]);
  }

  int result = 0;
  for (int i = 0; i < components; i++) {
    if (!compressed_graph.visited[i]) {
      result += DFSCountLeaves(compressed_graph, i);
    }
  }
  std::cout << (result + 1) / 2;
}

int main() {
  int nodes;
  int edges;
  std::cin >> nodes >> edges;
  Graph graph(nodes);
  ReadGraph(graph, edges);

  std::set<std::pair<int, int>> bridges;
  for (int i = 0; i < nodes; i++) {
    if (!graph.visited[i]) {
      DFSFindBridges(graph, i, bridges);
    }
  }

  CompressComponents(graph, bridges);
}