#include <chrono>
#include <iostream>
#include <random>

class Node {
  Node* left_child_ = nullptr;
  Node* right_child_ = nullptr;
  int value_;
  int key_;
  long long sum_ = 0;

  ~Node() {
    delete left_child_;
    delete right_child_;
  }

  friend class Treap;
};

class Treap {
  Node* root_ = nullptr;

  bool Exists(int value) {
    Node* unit = root_;
    while (unit != nullptr) {
      if (unit->value_ == value) {
        return true;
      }
      if (unit->value_ < value) {
        unit = unit->right_child_;
      } else {
        unit = unit->left_child_;
      }
    }
    return false;
  }

  static void UpdateSum(Node* node) {
    node->sum_ = node->value_;
    if (node->left_child_ != nullptr) {
      node->sum_ += node->left_child_->sum_;
    }
    if (node->right_child_ != nullptr) {
      node->sum_ += node->right_child_->sum_;
    }
  }

  Node* Merge(Node* left, Node* right) {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->key_ < right->key_) {
      left->right_child_ = Merge(left->right_child_, right);
      UpdateSum(left);
      return left;
    }
    right->left_child_ = Merge(left, right->left_child_);
    UpdateSum(right);
    return right;
  }

  std::pair<Node*, Node*> Split(Node* node, int value) {
    if (node == nullptr) {
      return std::pair(nullptr, nullptr);
    }
    if (node->value_ > value) {
      std::pair<Node*, Node*> result = Split(node->left_child_, value);
      node->left_child_ = result.second;
      UpdateSum(node);
      return std::pair(result.first, node);
    }
    std::pair<Node*, Node*> result = Split(node->right_child_, value);
    node->right_child_ = result.first;
    UpdateSum(node);
    return std::pair(node, result.second);
  }

public:
  void Insert(int value) {
    if (Exists(value)) {
      return;
    }
    std::mt19937 rnd(
      std::chrono::steady_clock::now().time_since_epoch().count());
    Node* node = new Node;
    node->value_ = value;
    node->sum_ = value;
    node->key_ = rnd();
    std::pair<Node*, Node*> temp = Split(root_, value);
    root_ = Merge(Merge(temp.first, node), temp.second);
  }

  long long Sum(int left, int right) {
    std::pair<Node*, Node*> result_right = Split(root_, right);
    std::pair<Node*, Node*> result_left = Split(result_right.first, left - 1);
    long long result = 0;
    if (result_left.second != nullptr) {
      result = result_left.second->sum_;
    }
    root_ = Merge(Merge(result_left.first, result_left.second),
                  result_right.second);
    return result;
  }

  ~Treap() { delete root_; }
};

int main() {
  const int kMagic = 1000000000;
  Treap tree;
  int quantity;
  std::cin >> quantity;
  long long previous_result = -1;
  char instruction;
  int value_first;
  int value_second;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction >> value_first;
    if (instruction == '+') {
      if (previous_result != -1) {
        value_first = (previous_result + value_first) % kMagic;
      }
      tree.Insert(value_first);
      previous_result = -1;
    } else if (instruction == '?') {
      std::cin >> value_second;
      previous_result = tree.Sum(value_first, value_second);
      std::cout << previous_result << "\n";
    }
  }
}