#include <iostream>
#include <vector>

std::vector<int> FindClique(int size, std::vector<int>& graph) {
  std::vector<int> clique(1 << size, 0);
  clique[0] = 1;

  int oldest = -1;
  for (int mask = 1; mask < (1 << size); mask++) {
    if ((mask & (mask - 1)) == 0) {
      oldest++;
    }
    int mask_v = mask - (1 << oldest);
    if ((clique[mask_v] == 1) && ((mask_v & graph[oldest]) == mask_v)) {
      clique[mask] = 1;
    }
  }

  return clique;
}

void FindNumberSubclique(int size, std::vector<int>& clique) {
  for (int i = 0; i < size; i++) {
    for (int mask = 0; mask < (1 << size); mask++) {
      if ((mask & (1 << i)) == 0) {
        clique[mask + (1 << i)] += clique[mask];
      }
    }
  }
}

std::vector<int> FindCorr(int size, std::vector<long long>& graph) {
  std::vector<int> corr((1 << ((size + 1) / 2)), 0);
  corr[0] = (1 << (size / 2)) - 1;
  int oldest = -1;

  for (int mask = 1; mask < (1 << ((size + 1) / 2)); mask++) {
    if ((mask & (mask - 1)) == 0) {
      oldest++;
    }
    corr[mask] =
        corr[mask - (1 << oldest)] & (graph[oldest] >> ((size + 1) / 2));
  }

  return corr;
}

int main() {
  int size;
  std::cin >> size;

  std::vector<long long> graph(size, 0);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      char k;
      std::cin >> k;
      graph[i] |= ((k == '1' ? 1LL : 0LL) << j);
    }
  }

  int size_left = (size + 1) / 2;
  int size_right = size - size_left;

  std::vector<int> graph_left(size_left, 0);
  for (int i = 0; i < size_left; i++) {
    graph_left[i] = graph[i] & ((1 << size_left) - 1);
  }
  std::vector<int> clique_left(FindClique(size_left, graph_left));

  std::vector<int> graph_right(size_right, 0);
  for (int i = 0; i < size_right; i++) {
    graph_right[i] = graph[i + size_left] >> size_left;
  }
  std::vector<int> clique_right(FindClique(size_right, graph_right));
  FindNumberSubclique(size_right, clique_right);

  std::vector<int> corr(FindCorr(size, graph));
  long long answer = 0;
  for (long long mask = 0; mask < (1 << size_left); mask++) {
    if (clique_left[mask] == 1) {
      answer = answer + clique_right[corr[mask]];
    }
  }

  std::cout << answer;
}