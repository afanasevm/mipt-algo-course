#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int quantity_a;
  int quantity_b;
  int length;
  std::cin >> quantity_a >> quantity_b >> length;

  std::vector<std::vector<int>> predictions_a(quantity_a);
  for (int i = 0; i < quantity_a; i++) {
    std::vector<int> times(length);
    for (int j = 0; j < length; j++) {
      std::cin >> times[j];
    }
    predictions_a[i] = times;
  }

  std::vector<std::vector<int>> predictions_b(quantity_b);
  for (int i = 0; i < quantity_b; i++) {
    std::vector<int> times(length);
    for (int j = 0; j < length; j++) {
      std::cin >> times[j];
    }
    predictions_b[i] = times;
  }

  int requests;
  const int kMinim = 100000;
  std::cin >> requests;
  for (int i = 0; i < requests; i++) {
    int number_a;
    int number_b;
    std::cin >> number_a >> number_b;
    int index = -1;
    int minim = kMinim;
    for (int j = 0; j < length; j++) {
      int x = std::max(predictions_a[number_a - 1][j],
                       predictions_b[number_b - 1][j]);
      if (x < minim) {
        index = j;
        minim = x;
      }
    }
    std::cout << index + 1 << "\n";
  }
}
