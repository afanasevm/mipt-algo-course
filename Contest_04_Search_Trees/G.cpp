#include <chrono>
#include <iostream>
#include <random>

class Node {
  Node* left_child_ = nullptr;
  Node* right_child_ = nullptr;
  int value_;
  int key_;
  int right_border_;
  int quantity_ = 1;

  ~Node() {
    delete left_child_;
    delete right_child_;
  }

  friend class Treap;
};

class Treap {
  Node* root_ = nullptr;
  int size_ = 0;
  long long sum_squares_ = 0;

  bool Exists(int value) {
    Node* node = root_;
    while (node != nullptr) {
      if (node->value_ == value) {
        return true;
      }
      if (node->value_ < value) {
        node = node->right_child_;
      } else {
        node = node->left_child_;
      }
    }
    return false;
  }

  static void UpdateQuantity(Node* node) {
    int result = 1;
    if (node->left_child_ != nullptr) {
      result += node->left_child_->quantity_;
    }
    if (node->right_child_ != nullptr) {
      result += node->right_child_->quantity_;
    }
    node->quantity_ = result;
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
      UpdateQuantity(left);
      return left;
    }
    right->left_child_ = Merge(left, right->left_child_);
    UpdateQuantity(right);
    return right;
  }

  std::pair<Node*, Node*> Split(Node* node, int value) {
    if (node == nullptr) {
      return std::pair(nullptr, nullptr);
    }
    if (node->value_ > value) {
      std::pair<Node*, Node*> result = Split(node->left_child_, value);
      node->left_child_ = result.second;
      UpdateQuantity(node);
      return std::pair(result.first, node);
    }
    std::pair<Node*, Node*> result = Split(node->right_child_, value);
    node->right_child_ = result.first;
    UpdateQuantity(node);
    return std::pair(node, result.second);
  }

  Node* Kth(int value) {
    Node* result = nullptr;
    if (root_ == nullptr) {
      return result;
    }
    Node* node = root_;
    int left_quantity;
    while (node != nullptr) {
      if (node->left_child_ != nullptr) {
        left_quantity = node->left_child_->quantity_;
      } else {
        left_quantity = 0;
      }
      if (left_quantity + 1 == value) {
        result = node;
        break;
      }
      if (left_quantity + 1 < value) {
        value -= left_quantity + 1;
        node = node->right_child_;
      } else {
        node = node->left_child_;
      }
    }
    return result;
  }

public:
  void Insert(int value, int second_value) {
    if (Exists(value)) {
      return;
    }
    Node* node = new Node;
    node->value_ = value;
    node->right_border_ = second_value;
    std::mt19937 rnd(
      std::chrono::steady_clock::now().time_since_epoch().count());
    node->key_ = rnd();
    std::pair<Node*, Node*> temp = Split(root_, value);
    root_ = Merge(Merge(temp.first, node), temp.second);
    size_ += 1;
    long long distance = second_value - value + 1;
    sum_squares_ += distance * distance;
  }

  int Delete(int value) {
    if (!Exists(value)) {
      return -1;
    }
    std::pair<Node*, Node*> temp = Split(root_, value);
    std::pair<Node*, Node*> temp1 = Split(temp.first, value - 1);
    root_ = Merge(temp1.first, temp.second);
    int result = temp1.second->right_border_;
    long long distance = temp1.second->right_border_ - temp1.second->value_ + 1;
    sum_squares_ -= distance * distance;
    delete temp1.second;
    size_ -= 1;
    return result;
  }

  void DeleteGrouping(int value) {
    if (value == 1) {
      Node* node = Kth(value);
      Node* next = Kth(value + 1);
      int left_border = node->value_;
      int right_border = next->right_border_;
      Delete(node->value_);
      Delete(next->value_);
      Insert(left_border, right_border);
    } else if (value == size_) {
      Node* node = Kth(value);
      Node* prev = Kth(value - 1);
      int left_border = prev->value_;
      int right_border = node->right_border_;
      Delete(prev->value_);
      Delete(node->value_);
      Insert(left_border, right_border);
    } else {
      Node* node = Kth(value);
      Node* prev = Kth(value - 1);
      Node* next = Kth(value + 1);
      int left_border = prev->value_;
      int right_border = next->right_border_;
      int border = (node->value_ + node->right_border_ - 1) / 2;
      Delete(prev->value_);
      Delete(node->value_);
      Delete(next->value_);
      Insert(left_border, border);
      Insert(border + 1, right_border);
    }
  }

  void DividePlot(int value) {
    Node* node = Kth(value);
    int left_border = node->value_;
    int right_border = node->right_border_;
    int border = (left_border + right_border - 1) / 2;
    Delete(node->value_);
    Insert(left_border, border);
    Insert(border + 1, right_border);
  }

  long long GetSumSquares() const { return sum_squares_; }

  ~Treap() { delete root_; }
};

int main() {
  Treap tree;
  int quantity_patrols;
  int number;
  std::cin >> quantity_patrols >> number;
  number = 0;
  int value;
  for (int i = 0; i < quantity_patrols; i++) {
    std::cin >> value;
    tree.Insert(number, number + value - 1);
    number += value;
  }
  std::cout << tree.GetSumSquares() << "\n";
  int quantity_requests;
  int instruction;
  std::cin >> quantity_requests;
  for (int i = 0; i < quantity_requests; i++) {
    std::cin >> instruction >> value;
    if (instruction == 1) {
      tree.DeleteGrouping(value);
    } else if (instruction == 2) {
      tree.DividePlot(value);
    }
    std::cout << tree.GetSumSquares() << "\n";
  }
}