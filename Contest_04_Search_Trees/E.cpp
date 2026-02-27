#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Segment {
  int size;
  int quantity;

  Segment(int size, int quantity) : size(size), quantity(quantity) {}
};

bool operator<(Segment left, Segment right) { return left.size < right.size; }

void Insert(std::set<Segment>& set, int value) {
  std::set<Segment>::iterator index = set.find({value, 1});
  if (index == set.end()) {
    set.insert({value, 1});
  } else {
    Segment temp = *index;
    set.erase(temp);
    temp.quantity++;
    set.insert(temp);
  }
}

void Delete(std::set<Segment>& set, int value) {
  std::set<Segment>::iterator index = set.find({value, 1});
  if (index->quantity == 1) {
    set.erase(index);
  } else {
    Segment temp = *index;
    set.erase(temp);
    temp.quantity--;
    set.insert(temp);
  }
}

int main() {
  int quantity_stations;
  int quantity_trails;
  int length_trails;
  std::cin >> quantity_stations >> quantity_trails >> length_trails;
  std::vector<std::pair<int, int>> stations_start(quantity_stations);
  std::vector<std::pair<int, int>> stations_end(quantity_stations);
  int station_x;
  int station_y_start;
  int station_y_end;
  for (int i = 0; i < quantity_stations; i++) {
    std::cin >> station_x >> station_y_start >> station_y_end;
    stations_start[i] = {station_y_start, station_x};
    stations_end[i] = {station_y_end, station_x};
  }
  std::sort(stations_start.begin(), stations_start.end());
  std::sort(stations_end.begin(), stations_end.end());
  std::set<Segment> segments_between_stations = {{length_trails, 1}};
  std::set<int> stations{0, length_trails};
  int index_start = 0;
  int index_end = 0;
  for (int i = 0; i <= quantity_trails; i++) {
    while (index_start < quantity_stations &&
           stations_start[index_start].first == i) {
      std::set<int>::iterator index =
        stations.insert(stations_start[index_start].second).first;
      Insert(segments_between_stations, *(++index)-- - *index);
      Insert(segments_between_stations, *index - *(--index)++);
      Delete(segments_between_stations, *(++index)-- - *(--index)++);
      index_start++;
    }
    std::cout << (--segments_between_stations.end())->size << "\n";
    while (index_end < quantity_stations &&
           stations_end[index_end].first == i) {
      std::set<int>::iterator index =
        stations.find(stations_end[index_end].second);
      Delete(segments_between_stations, *(++index)-- - *index);
      Delete(segments_between_stations, *index - *(--index)++);
      Insert(segments_between_stations, *(++index)-- - *(--index)++);
      stations.erase(stations_end[index_end].second);
      index_end++;
    }
  }
}