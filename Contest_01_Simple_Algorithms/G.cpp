#include <iostream>
#include <vector>
const int kBitsInByte = 8;
const int kByte = 256;
const int kBitsInNumber = 64;

void LeastSignificantDigit(std::vector<unsigned long long>& digits,
                           int number) {
  std::vector<int> count(kByte);
  std::vector<unsigned long long> answer(number);
  unsigned long long bytes = kByte - 1;
  unsigned long long degree = 1;
  for (int j = 0; j < kBitsInNumber / kBitsInByte; j++) {
    for (int i = 0; i < kByte; i++) {
      count[i] = 0;
    }
    for (int i = 0; i < number; i++) {
      count[(digits[i] / degree) & bytes]++;
    }
    for (int i = 1; i < kByte; i++) {
      count[i] += count[i - 1];
    }
    for (int i = number - 1; i >= 0; i--) {
      answer[count[(digits[i] / degree) & bytes]-- - 1] = digits[i];
    }
    for (int i = 0; i < number; i++) {
      digits[i] = answer[i];
    }
    degree *= kByte;
  }
}

int main() {
  int quantity;
  std::cin >> quantity;
  std::vector<unsigned long long> numbers(quantity);
  for (int i = 0; i < quantity; i++) {
    std::cin >> numbers[i];
  }
  LeastSignificantDigit(numbers, quantity);
  for (int i = 0; i < quantity; i++) {
    std::cout << numbers[i] << "\n";
  }
}
