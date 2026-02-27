#include <deque>
#include <iostream>
#include <vector>

void MinimumSubsection(int size, int length,
                       std::vector<std::vector<int>>& digits) {
  std::deque<int> deque;
  int number;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (j >= length) {
        number = digits[i][j - length];
        digits[i][j - length] = deque.front();
        if (number == deque.front()) {
          deque.pop_front();
        }
      }
      while (!deque.empty() && (deque.back() > digits[i][j])) {
        deque.pop_back();
      }
      deque.push_back(digits[i][j]);
    }
    digits[i][size - length] = deque.front();
    deque.clear();
  }
}

void MinimumSubcolumn(int size, int length,
                      std::vector<std::vector<int>>& digits) {
  std::deque<int> deque;
  int number;
  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size; i++) {
      if (i >= length) {
        number = digits[i - length][j];
        digits[i - length][j] = deque.front();
        if (number == deque.front()) {
          deque.pop_front();
        }
      }
      while (!deque.empty() && (deque.back() > digits[i][j])) {
        deque.pop_back();
      }
      deque.push_back(digits[i][j]);
    }
    digits[size - length][j] = deque.front();
    deque.clear();
  }
}

int main() {
  int size;
  int length;
  std::cin >> size >> length;
  std::vector<std::vector<int>> digits(size, std::vector<int>(size));
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      std::cin >> digits[i][j];
    }
  }
  MinimumSubsection(size, length, digits);
  MinimumSubcolumn(size, length, digits);
  for (int i = 0; i < size - length + 1; i++) {
    for (int j = 0; j < size - length + 1; j++) {
      std::cout << digits[i][j] << " ";
    }
    std::cout << "\n";
  }
}