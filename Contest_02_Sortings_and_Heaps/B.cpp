#include <iostream>
#include <stack>
#include <vector>

void MinLeft(std::vector<long long>& array, int length,
             std::vector<int>& result) {
  std::stack<int> stack;
  for (int i = 0; i < length; i++) {
    while (!stack.empty() && (array[stack.top()] >= array[i])) {
      stack.pop();
    }
    if (stack.empty()) {
      result[i] = -1;
    } else {
      result[i] = stack.top();
    }
    stack.push(i);
  }
}

void MinRight(std::vector<long long>& array, int length,
              std::vector<int>& result) {
  std::stack<int> stack;
  for (int i = length - 1; i >= 0; i--) {
    while (!stack.empty() && (array[stack.top()] >= array[i])) {
      stack.pop();
    }
    if (stack.empty()) {
      result[i] = length;
    } else {
      result[i] = stack.top();
    }
    stack.push(i);
  }
}

int main() {
  int quantity;
  std::cin >> quantity;
  std::vector<long long> weights(quantity);
  for (int i = 0; i < quantity; i++) {
    std::cin >> weights[i];
  }
  std::vector<int> indexes_left(quantity);
  std::vector<int> indexes_right(quantity);
  MinLeft(weights, quantity, indexes_left);
  MinRight(weights, quantity, indexes_right);
  long long max_square = 0;
  long long square;
  for (int i = 0; i < quantity; i++) {
    square = (indexes_right[i] - indexes_left[i] - 1) * weights[i];
    if (square > max_square) {
      max_square = square;
    }
  }
  std::cout << max_square;
}