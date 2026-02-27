#include <iostream>
#include <vector>

std::vector<int> Partition(std::vector<int>& array, int index_start,
                           int index_end) {
  int pivot = array[index_end];
  std::vector<int> pivot_indexes = {index_start, index_start};
  for (int i = index_start; i <= index_end; i++) {
    if (array[i] < pivot) {
      std::swap(array[i], array[pivot_indexes[0]]);
      pivot_indexes[0] += 1;
    }
  }
  pivot_indexes[1] = pivot_indexes[0];
  for (int i = pivot_indexes[0]; i <= index_end; i++) {
    if (array[i] == pivot) {
      std::swap(array[i], array[pivot_indexes[1]]);
      pivot_indexes[1] += 1;
    }
  }
  return pivot_indexes;
}

void QuickSort(std::vector<int>& array, int index_start, int index_end) {
  if (index_start < index_end) {
    std::vector<int> pivot_indexes = Partition(array, index_start, index_end);
    QuickSort(array, index_start, pivot_indexes[0] - 1);
    QuickSort(array, pivot_indexes[1], index_end);
  }
}

int main() {
  int number;
  int quantity;
  std::cin >> number >> quantity;
  std::vector<int> coordinates(number);
  std::cin >> coordinates[0];
  for (int i = 1; i < number; i++) {
    std::cin >> coordinates[i];
  }

  QuickSort(coordinates, 0, number - 1);
  long long left_border = 0;
  long long right_border =
      (coordinates[number - 1] - coordinates[0]) / quantity + 1;
  while (left_border < right_border) {
    long long middle = (left_border + right_border) / 2;
    long long count = 0;
    long long index = coordinates[0] - 1;
    for (int i = 0; i < number; i++) {
      if (index < coordinates[i]) {
        index = coordinates[i] + middle;
        count += 1;
      }
    }
    if (count <= quantity) {
      right_border = middle;
    } else {
      left_border = middle + 1;
    }
  }
  std::cout << left_border;
}
