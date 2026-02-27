#include <iomanip>
#include <iostream>
#include <vector>
const int kLength = 5;

int Median(std::vector<int>& array, int index_start, int index_end) {
  for (int i = index_start; i < index_end; i++) {
    bool swapped = false;
    for (int j = index_start; j < index_end - i; j++) {
      if (array[j] > array[j + 1]) {
        std::swap(array[j], array[j + 1]);
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
  }
  return array[(index_end + index_start) / 2];
}

std::vector<int> Partition(std::vector<int>& array, int index_start,
                           int index_end, int pivot) {
  std::vector<int> indexes = {index_start, index_start};
  for (int i = index_start; i <= index_end; i++) {
    if (array[i] < pivot) {
      std::swap(array[i], array[indexes[0]]);
      indexes[0]++;
    }
  }
  indexes[1] = indexes[0];
  for (int i = indexes[0]; i <= index_end; i++) {
    if (array[i] == pivot) {
      std::swap(array[i], array[indexes[1]]);
      indexes[1]++;
    }
  }
  return indexes;
}

int QuickSelect(std::vector<int>& array, int index_start, int index_end,
                int kth) {
  if (index_start == index_end) {
    return array[index_start];
  }
  std::vector<int> medians;
  int index = index_start;
  while (index < index_end) {
    if (index_end - index + 1 >= kLength) {
      medians.push_back(Median(array, index, index + kLength - 1));
      index += kLength;
    } else {
      medians.push_back(Median(array, index, index_end));
      index = index_end;
    }
  }
  int pivot =
      QuickSelect(medians, 0, medians.size() - 1, (medians.size() - 1) / 2);
  std::vector<int> indexes = Partition(array, index_start, index_end, pivot);
  if (kth < indexes[0] - index_start) {
    return QuickSelect(array, index_start, indexes[0] - 1, kth);
  }
  if (kth < indexes[1] - index_start) {
    return pivot;
  }
  return QuickSelect(array, indexes[1], index_end,
                     kth - (indexes[1] - index_start));
}

void QuickSort(std::vector<int>& array, int index_start, int index_end) {
  if (index_start < index_end) {
    int pivot = QuickSelect(array, index_start, index_end,
                            (index_end - index_start + 1) / 2);
    std::vector<int> pivot_indexes =
        Partition(array, index_start, index_end, pivot);
    QuickSort(array, index_start, (pivot_indexes)[0] - 1);
    QuickSort(array, (pivot_indexes)[1], index_end);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int number;
  std::cin >> number;
  std::vector<int> digits(number);
  for (int i = 0; i < number; i++) {
    std::cin >> digits[i];
  }
  QuickSort(digits, 0, number - 1);
  for (int i = 0; i < number; i++) {
    std::cout << digits[i] << " ";
  }
}
