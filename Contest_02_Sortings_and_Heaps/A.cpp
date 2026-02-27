#include <iostream>
#include <stack>
#include <string>

int main() {
  std::string scream;
  std::cin >> scream;
  std::stack<char> staples;
  bool flag = true;
  for (size_t i = 0; i < scream.size(); i++) {
    if (scream[i] == '(' || scream[i] == '{' || scream[i] == '[') {
      staples.push(scream[i]);
    } else if (!staples.empty() &&
               ((scream[i] == ')' && staples.top() == '(') ||
                (scream[i] == '}' && staples.top() == '{') ||
                (scream[i] == ']' && staples.top() == '['))) {
      staples.pop();
    } else {
      flag = false;
    }
  }
  if (staples.empty() && flag) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}