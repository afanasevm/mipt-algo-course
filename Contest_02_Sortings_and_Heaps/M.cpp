#include <deque>
#include <iostream>
#include <vector>

long long FindSecondMove(int quantity,
                         std::vector<long long> sum_of_semicircle) {
  std::deque<long long> deque;
  std::vector<long long> result(quantity);
  for (int i = 0; i < quantity / 2 + quantity % 2; i++) {
    while (!deque.empty() && (deque.back() < sum_of_semicircle[i])) {
      deque.pop_back();
    }
    deque.push_back(sum_of_semicircle[i]);
  }
  for (int i = 0; i < quantity; i++) {
    while (!deque.empty() &&
           (deque.back() <
            sum_of_semicircle[(quantity / 2 + quantity % 2 + i) % quantity])) {
      deque.pop_back();
    }
    deque.push_back(
      sum_of_semicircle[(quantity / 2 + quantity % 2 + i) % quantity]);
    if (deque.front() == sum_of_semicircle[i]) {
      deque.pop_front();
    }
    result[i] = deque.front();
  }
  long long min_second = result[0];
  for (int i = 0; i < quantity; i++) {
    if (result[i] < min_second) {
      min_second = result[i];
    }
  }
  return min_second;
}

int main() {
  int quantity;
  std::cin >> quantity;
  std::vector<int> digits(quantity);
  long long sum = 0;
  for (int i = 0; i < quantity; i++) {
    std::cin >> digits[i];
    sum += digits[i];
  }
  std::vector<long long> sum_of_semicircle(quantity, 0);
  for (int i = 0; i < quantity / 2; i++) {
    sum_of_semicircle[0] += digits[i];
  }
  for (int i = 1; i < quantity; i++) {
    sum_of_semicircle[i] = sum_of_semicircle[i - 1] +
                           digits[(quantity / 2 + i - 1) % quantity] -
                           digits[i - 1];
  }
  long long second = FindSecondMove(quantity, sum_of_semicircle);
  std::cout << sum - second << " " << second;
}