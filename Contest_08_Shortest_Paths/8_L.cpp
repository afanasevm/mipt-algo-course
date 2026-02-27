#include <algorithm>
#include <iostream>
#include <string>
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

int main() {
  int size;
  int edge;
  int request;
  std::cin >> size >> edge >> request;

  std::vector<std::pair<int, int>> edges(edge);
  for (int i = 0; i < edge; i++) {
    int from;
    int to;
    std::cin >> from >> to;
    edges[i] = {from, to};
  }

  std::vector<std::vector<int>> requests(request, std::vector<int>(3));
  for (int i = 0; i < request; i++) {
    std::string req;
    int from;
    int to;
    std::cin >> req >> from >> to;
    if (req == "ask") {
      requests[i][0] = 1;
    } else if (req == "cut") {
      requests[i][0] = 0;
    }
    requests[i][1] = from - 1;
    requests[i][2] = to - 1;
  }

  DSU dsu(size);
  std::reverse(requests.begin(), requests.end());
  std::vector<std::string> answer;
  for (std::vector<int> req : requests) {
    if (req[0] == 1) {
      if (dsu.Get(req[1]) == dsu.Get(req[2])) {
        answer.push_back("YES");
      } else {
        answer.push_back("NO");
      }
    } else if (req[0] == 0) {
      dsu.Unite(req[1], req[2]);
    }
  }
  std::reverse(answer.begin(), answer.end());
  for (std::string ans : answer) {
    std::cout << ans << "\n";
  }
}