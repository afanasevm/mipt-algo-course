#include <deque>
#include <iostream>
#include <string>

void FixDeque(std::deque<int>& left_deque, std::deque<int>& right_deque) {
  if (left_deque.size() < right_deque.size()) {
    left_deque.push_back(right_deque.front());
    right_deque.pop_front();
  }
}

int main() {
  int quantity;
  std::cin >> quantity;
  std::deque<int> left_deque;
  std::deque<int> right_deque;
  std::string instruction;
  int number;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction;
    if (instruction == "+") {
      std::cin >> number;
      right_deque.push_back(number);
    } else if (instruction == "*") {
      std::cin >> number;
      right_deque.push_front(number);
    } else {
      std::cout << left_deque.front() << "\n";
      left_deque.pop_front();
    }
    FixDeque(left_deque, right_deque);
  }
}