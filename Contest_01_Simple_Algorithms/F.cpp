#include <iostream>
#include <vector>
const int kLength = 5;
const int kMinim = -100000000;

int Median(std::vector<int>& array, int index_start, int index_end) {
  int length = index_end - index_start + 1;
  int max1 = kMinim;
  int max2 = kMinim;
  int max3 = kMinim;
  for (int i = index_start; i <= index_end; i++) {
    if (array[i] > max1) {
      max3 = max2;
      max2 = max1;
      max1 = array[i];
    } else if (array[i] > max2) {
      max3 = max2;
      max2 = array[i];
    } else if (array[i] > max3) {
      max3 = array[i];
    }
  }
  if (length < 3) {
    return max1;
  }
  if (length < 5) {
    return max2;
  }
  return max3;
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

int main() {
  const int kDigit1 = 123;
  const int kDigit2 = 45;
  const int kDigit3 = 10000000 + 4321;
  int number;
  int order;
  std::cin >> number >> order;
  std::vector<int> digits(number);
  std::cin >> digits[0] >> digits[1];
  for (int i = 2; i < number; i++) {
    digits[i] = (digits[i - 1] * kDigit1 + digits[i - 2] * kDigit2) % kDigit3;
  }
  int result = QuickSelect(digits, 0, number - 1, order - 1);
  std::cout << result;
}
