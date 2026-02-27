#include <iostream>
#include <vector>

int main() {
  int number;
  std::cin >> number;
  std::vector<int> digits(number);
  for (int index = 0; index < number; index++) {
    std::cin >> digits[index];
  }

  std::vector<int> prefix_min(number);
  std::vector<int> postfix_min(number);
  prefix_min[0] = digits[0];
  postfix_min[number - 1] = digits[number - 1];
  for (int i = 1; i < number; i++) {
    if (prefix_min[i - 1] <= digits[i]) {
      prefix_min[i] = prefix_min[i - 1];
    } else {
      prefix_min[i] = digits[i];
    }
    if (postfix_min[number - i] <= digits[number - i - 1]) {
      postfix_min[number - i - 1] = postfix_min[number - i];
    } else {
      postfix_min[number - i - 1] = digits[number - i - 1];
    }
  }

  int number_of_requests;
  std::cin >> number_of_requests;
  for (int i = 0; i < number_of_requests; i++) {
    int left_border;
    int right_border;
    std::cin >> left_border >> right_border;
    int result;
    if (prefix_min[left_border - 1] < postfix_min[right_border - 1]) {
      result = prefix_min[left_border - 1];
    } else {
      result = postfix_min[right_border - 1];
    }
    std::cout << result << "\n";
  }
}
