#include <iostream>
#include <vector>

std::vector<int> Partition(std::vector<std::vector<int>>& array,
                           int index_start, int index_end) {
  int pivot = array[index_end][0];
  std::vector<int> pivot_indexes = {index_start, index_start};
  for (int i = index_start; i <= index_end; i++) {
    if (array[i][0] < pivot) {
      std::swap(array[i], array[pivot_indexes[0]]);
      pivot_indexes[0] += 1;
    }
  }
  pivot_indexes[1] = pivot_indexes[0];
  for (int i = pivot_indexes[0]; i <= index_end; i++) {
    if (array[i][0] == pivot) {
      std::swap(array[i], array[pivot_indexes[1]]);
      pivot_indexes[1] += 1;
    }
  }
  return pivot_indexes;
}

void QuickSort(std::vector<std::vector<int>>& array, int index_start,
               int index_end) {
  if (index_start < index_end) {
    std::vector<int> pivot_indexes = Partition(array, index_start, index_end);
    QuickSort(array, index_start, pivot_indexes[0] - 1);
    QuickSort(array, pivot_indexes[1], index_end);
  }
}

int main() {
  int number;
  std::cin >> number;
  std::vector<std::vector<int>> times;
  for (int i = 0; i < number; i++) {
    int border_l;
    int border_r;
    std::cin >> border_l >> border_r;
    times.push_back({border_l, border_r});
  }

  QuickSort(times, 0, number - 1);
  int count = 1;
  std::vector<std::vector<int>> periods;
  int last_l = times[0][0];
  int last_r = times[0][1];
  for (int i = 1; i < number; i++) {
    if (times[i][0] <= last_r) {
      last_r = std::max(last_r, times[i][1]);
    } else {
      periods.push_back({last_l, last_r});
      count++;
      last_l = times[i][0];
      last_r = times[i][1];
    }
  }
  periods.push_back({last_l, last_r});

  std::cout << count << "\n";
  for (int i = 0; i < count; i++) {
    std::cout << periods[i][0] << " " << periods[i][1] << "\n";
  }
}
