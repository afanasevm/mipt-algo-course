#include <iostream>

int main() {
  int quantity;
  int width;
  int length;
  std::cin >> quantity;
  for (int i = 0; i < quantity; i++) {
    std::cin >> width >> length;
    std::cout << width * length - 1 << "\n";
  }
}