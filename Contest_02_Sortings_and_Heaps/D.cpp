#include <deque>
#include <iostream>
#include <string>

void Enqueue(std::deque<int>& deque, std::deque<int>& min_deque, int number) {
  deque.push_back(number);
  while (!min_deque.empty() && (min_deque.back() > number)) {
    min_deque.pop_back();
  }
  min_deque.push_back(number);
  std::cout << "ok\n";
}

void Dequeue(std::deque<int>& deque, std::deque<int>& min_deque) {
  if (!deque.empty()) {
    std::cout << deque.front() << "\n";
    if (deque.front() == min_deque.front()) {
      min_deque.pop_front();
    }
    deque.pop_front();
  } else {
    std::cout << "error\n";
  }
}

void Front(std::deque<int>& deque) {
  if (!deque.empty()) {
    std::cout << deque.front() << "\n";
  } else {
    std::cout << "error\n";
  }
}

void Size(std::deque<int>& deque) { std::cout << deque.size() << "\n"; }

void Clear(std::deque<int>& deque, std::deque<int>& min_deque) {
  deque.clear();
  min_deque.clear();
  std::cout << "ok\n";
}

void Min(std::deque<int>& min_deque) {
  if (!min_deque.empty()) {
    std::cout << min_deque.front() << "\n";
  } else {
    std::cout << "error\n";
  }
}

int main() {
  int quantity;
  std::cin >> quantity;
  std::deque<int> deque;
  std::deque<int> min_deque;
  std::string instruction;
  int number;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction;
    if (instruction == "enqueue") {
      std::cin >> number;
      Enqueue(deque, min_deque, number);
    } else if (instruction == "dequeue") {
      Dequeue(deque, min_deque);
    } else if (instruction == "front") {
      Front(deque);
    } else if (instruction == "size") {
      Size(deque);
    } else if (instruction == "clear") {
      Clear(deque, min_deque);
    } else if (instruction == "min") {
      Min(min_deque);
    }
  }
}