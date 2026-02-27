#include <algorithm>
#include <iostream>
#include <vector>

struct DSU {
  std::vector<int> parent;
  std::vector<int> size_v;

  DSU(int size) : parent(size), size_v(size, 1) {
    for (int i = 0; i < size; i++) {
      parent[i] = i;
    }
  }

  int Get(int index) {
    if (parent[index] == index) {
      return index;
    }
    parent[index] = Get(parent[index]);
    return parent[index];
  }

  void Unite(int index1, int index2) {
    index1 = Get(index1);
    index2 = Get(index2);
    if (size_v[index1] < size_v[index2]) {
      std::swap(index1, index2);
    }
    parent[index2] = index1;
    size_v[index1] += size_v[index2];
  }
};

struct Graph {
  int size;
  int edges;
  std::vector<std::vector<int>> graph;
  DSU dsu;

  Graph(int size, int edges)
      : size(size),
        edges(edges),
        graph(edges, std::vector<int>(3)),
        dsu(size) {}
};

void ReadGraph(Graph& graph) {
  for (int i = 0; i < graph.edges; i++) {
    std::cin >> graph.graph[i][1] >> graph.graph[i][2] >> graph.graph[i][0];
    graph.graph[i][1]--;
    graph.graph[i][2]--;
  }
}

void Kruskals(Graph& graph) {
  long long sum = 0;

  std::sort(
      graph.graph.begin(), graph.graph.end(),
      [](std::vector<int>& a, std::vector<int>& b) { return a[0] < b[0]; });

  for (auto edge : graph.graph) {
    if (graph.dsu.Get(edge[1]) != graph.dsu.Get(edge[2])) {
      graph.dsu.Unite(edge[1], edge[2]);
      sum += edge[0];
    }
  }

  std::cout << sum;
}

int main() {
  int size;
  int edges;
  std::cin >> size >> edges;
  Graph graph(size, edges);
  ReadGraph(graph);

  Kruskals(graph);
}