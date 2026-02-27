#include <iostream>
#include <vector>

void Merge(std::vector<std::pair<int, int>>& array1,
           std::vector<std::pair<int, int>>& array2,
           std::vector<std::pair<int, int>>& digits, std::vector<int>& result) {
  int index1 = 0;
  int index2 = 0;
  int index3 = 0;
  int size1 = array1.size();
  int size2 = array2.size();
  while (index1 < size1 and index2 < size2) {
    if (array1[index1].first <= array2[index2].first) {
      digits[index3++] = array1[index1];
      result[array1[index1].second] += index2;
      index1++;
    } else {
      digits[index3++] = array2[index2];
      index2++;
    }
  }
  while (index1 < size1) {
    digits[index3++] = array1[index1];
    result[array1[index1].second] += index2;
    index1++;
  }
  while (index2 < size2) {
    digits[index3++] = array2[index2];
    index2++;
  }
}

void MergeSort(std::vector<std::pair<int, int>>& digits,
               std::vector<int>& result) {
  int length = digits.size();
  if (length > 1) {
    std::vector<std::pair<int, int>> array1((length + 1) / 2);
    std::vector<std::pair<int, int>> array2(length / 2);
    for (int i = 0; i < (length + 1) / 2; i++) {
      array1[i] = digits[i];
    }
    for (int i = (length + 1) / 2; i < length; i++) {
      array2[i - (length + 1) / 2] = digits[i];
    }
    MergeSort(array1, result);
    MergeSort(array2, result);
    Merge(array1, array2, digits, result);
  }
}

int main() {
  int number;
  std::cin >> number;
  std::vector<std::pair<int, int>> digits(number);
  int digit;
  for (int i = 0; i < number; i++) {
    std::cin >> digit;
    digits[i] = std::pair(digit, i);
  }
  std::vector<int> result(number);
  MergeSort(digits, result);
  for (int i = 0; i < number; i++) {
    std::cout << result[i] << " ";
  }
}