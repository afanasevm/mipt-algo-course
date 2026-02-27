#include <iostream>
#include <queue>
#include <vector>

const int cMaxCost = 1000000000;
const int cQuantity = 1000000;

struct Decks {
  int quantity_decks;
  int current_deck;
  int cost_up;
  int cost_down;
  int cost_entry;
  int cost_exit;
  int quantity_teleports;
  std::vector<std::vector<int>> teleports;
};

std::vector<int> Dijkstra(Decks& decks) {
  std::vector<std::vector<std::pair<int, int>>> edges(decks.quantity_decks);
  for (int i = 0; i < decks.quantity_decks - decks.quantity_teleports; i++) {
    if (i < decks.quantity_decks - decks.quantity_teleports - 1) {
      edges[i].push_back({i + 1, decks.cost_up});
    }
    if (i > 0) {
      edges[i].push_back({i - 1, decks.cost_down});
    }
  }
  for (int i = 0; i < decks.quantity_teleports; i++) {
    for (size_t j = 0; j < decks.teleports[i].size(); j++) {
      edges[decks.teleports[i][j] - 1].push_back(
          {cQuantity + i, decks.cost_entry});
      edges[cQuantity + i].push_back(
          {decks.teleports[i][j] - 1, decks.cost_exit});
    }
  }

  std::vector<int> dist(decks.quantity_decks, cMaxCost);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      not_used;

  not_used.push({0, 0});

  while (!not_used.empty()) {
    std::pair<int, int> node = not_used.top();
    not_used.pop();
    if (dist[node.second] == cMaxCost) {
      dist[node.second] = node.first;
      for (size_t i = 0; i < edges[node.second].size(); i++) {
        if (dist[edges[node.second][i].first] == cMaxCost) {
          not_used.push({node.first + edges[node.second][i].second,
                         edges[node.second][i].first});
        }
      }
    }
    if (dist[decks.current_deck - 1] != cMaxCost) {
      break;
    }
  }

  return dist;
}

int main() {
  Decks decks;
  std::cin >> decks.current_deck >> decks.cost_up >> decks.cost_down >>
      decks.cost_entry >> decks.cost_exit >> decks.quantity_teleports;
  decks.quantity_decks = cQuantity + decks.quantity_teleports;
  decks.teleports = std::vector<std::vector<int>>(decks.quantity_teleports);
  for (int i = 0; i < decks.quantity_teleports; i++) {
    int quantity;
    std::cin >> quantity;
    decks.teleports[i] = std::vector<int>(quantity);
    for (int j = 0; j < quantity; j++) {
      std::cin >> decks.teleports[i][j];
    }
  }

  int answer = Dijkstra(decks)[decks.current_deck - 1];
  std::cout << answer;
}