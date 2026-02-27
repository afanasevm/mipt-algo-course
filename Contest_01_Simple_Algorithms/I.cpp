#include <iostream>
#include <vector>

long long Merge(std::vector<int>& array1, std::vector<int>& array2,
                std::vector<int>& digits) {
  int index1 = 0;
  int index2 = 0;
  int index3 = 0;
  int size1 = array1.size();
  int size2 = array2.size();
  int result = 0;
  while (index1 < size1 and index2 < size2) {
    if (array1[index1] <= array2[index2]) {
      digits[index3++] = array1[index1];
      index1++;
      result += index2;
    } else {
      digits[index3++] = array2[index2];
      index2++;
    }
  }
  while (index1 < size1) {
    digits[index3++] = array1[index1];
    index1++;
    result += index2;
  }
  while (index2 < size2) {
    digits[index3++] = array2[index2];
    index2++;
  }
  return result;
}

long long MergeSort(std::vector<int>& digits) {
  int length = digits.size();
  if (length <= 1) {
    return 0;
  }
  std::vector<int> array1((length + 1) / 2);
  std::vector<int> array2(length / 2);
  for (int i = 0; i < (length + 1) / 2; i++) {
    array1[i] = digits[i];
  }
  for (int i = (length + 1) / 2; i < length; i++) {
    array2[i - (length + 1) / 2] = digits[i];
  }
  return MergeSort(array1) + MergeSort(array2) + Merge(array1, array2, digits);
}

int main() {
  int number;
  std::cin >> number;
  std::vector<int> digits(number);
  for (int i = 0; i < number; i++) {
    std::cin >> digits[i];
  }
  int res = MergeSort(digits);
  std::cout << res;
}
