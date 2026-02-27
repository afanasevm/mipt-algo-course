#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
  int number;
  std::cin >> number;
  std::vector<double> volume(number);
  for (int i = 0; i < number; i++) {
    std::cin >> volume[i];
  }

  std::vector<double> prefix_sum(number + 1);
  prefix_sum[0] = 0;
  for (int i = 0; i < number; i++) {
    prefix_sum[i + 1] = prefix_sum[i] + std::log(volume[i]);
  }

  int number_of_requests;
  const int kDecimalPlaces = 6;
  std::cin >> number_of_requests;
  for (int index = 0; index < number_of_requests; index++) {
    int left_border;
    int right_border;
    std::cin >> left_border >> right_border;
    double result =
        exp((prefix_sum[right_border + 1] - prefix_sum[left_border]) /
            (right_border - left_border + 1));
    std::cout << std::fixed << std::setprecision(kDecimalPlaces) << result
              << "\n";
  }
}
