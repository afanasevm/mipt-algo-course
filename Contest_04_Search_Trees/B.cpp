#include <algorithm>
#include <iostream>

class Node {
  Node* parent_ = nullptr;
  Node* left_child_ = nullptr;
  Node* right_child_ = nullptr;
  int height_ = 0;
  int value_ = 0;

  ~Node() {
    delete left_child_;
    delete right_child_;
  }

  friend class AvlTree;
};

class AvlTree {
  static const int kMax = 1000000001;
  Node* root_ = nullptr;

  static int Height(Node* node) {
    int first = 0;
    int second = 0;
    if (node->left_child_ != nullptr) {
      first = node->left_child_->height_;
    }
    if (node->right_child_ != nullptr) {
      second = node->right_child_->height_;
    }
    return std::max(first, second) + 1;
  }

  static int Balance(Node* node) {
    int result = 0;
    if (node->left_child_ != nullptr) {
      result += node->left_child_->height_;
    }
    if (node->right_child_ != nullptr) {
      result -= node->right_child_->height_;
    }
    return result;
  }

  static void LeftRotate(Node* node) {
    Node* temp = node->right_child_;
    temp->parent_ = node->parent_;
    node->right_child_ = temp->left_child_;
    if (temp->left_child_ != nullptr) {
      temp->left_child_->parent_ = node;
    }
    temp->left_child_ = node;
    node->parent_ = temp;
    node->height_ = Height(node);
    temp->height_ = Height(temp);
    node = temp;
    if (node->parent_ != nullptr) {
      if (node->value_ < node->parent_->value_) {
        node->parent_->left_child_ = node;
      } else {
        node->parent_->right_child_ = node;
      }
    }
  }

  static void RightRotate(Node* node) {
    Node* temp = node->left_child_;
    temp->parent_ = node->parent_;
    node->left_child_ = temp->right_child_;
    if (temp->right_child_ != nullptr) {
      temp->right_child_->parent_ = node;
    }
    temp->right_child_ = node;
    node->parent_ = temp;
    node->height_ = Height(node);
    temp->height_ = Height(temp);
    node = temp;
    if (node->parent_ != nullptr) {
      if (node->value_ < node->parent_->value_) {
        node->parent_->left_child_ = node;
      } else {
        node->parent_->right_child_ = node;
      }
    }
  }

  void FixTree(Node* node) {
    if (node != nullptr) {
      node->height_ = Height(node);
      if (Balance(node) == -2) {
        if (Balance(node->right_child_) < 1) {
          LeftRotate(node);
        } else {
          RightRotate(node->right_child_);
          LeftRotate(node);
        }
      } else if (Balance(node) == 2) {
        if (Balance(node->left_child_) > -1) {
          RightRotate(node);
        } else {
          LeftRotate(node->left_child_);
          RightRotate(node);
        }
      }
      root_ = node;
      node = node->parent_;
      FixTree(node);
    }
  }

 public:
  int Find(int value) {
    Node* unit = root_;
    int result = kMax;
    while (unit != nullptr) {
      if (unit->value_ == value) {
        result = value;
        break;
      }
      if (unit->value_ < value) {
        unit = unit->right_child_;
      } else {
        result = std::min(result, unit->value_);
        unit = unit->left_child_;
      }
    }
    if (result == kMax) {
      return -1;
    }
    return result;
  }

  void Insert(int value) {
    if (this->Find(value) != value) {
      Node* node = new Node;
      node->value_ = value;
      node->height_ = 1;
      if (root_ == nullptr) {
        root_ = node;
        return;
      }
      Node* unit = root_;
      Node* prev;
      while (unit != nullptr && unit->height_ > 1) {
        prev = unit;
        if (value < unit->value_) {
          unit = unit->left_child_;
        } else {
          unit = unit->right_child_;
        }
      }
      if (unit == nullptr) {
        unit = prev;
      }
      node->parent_ = unit;
      if (value < unit->value_) {
        unit->left_child_ = node;
      } else {
        unit->right_child_ = node;
      }
      FixTree(node);
    }
  }

  ~AvlTree() { delete root_; }
};

int main() {
  const int kDigit = 1000000000;
  AvlTree tree;
  int quantity;
  std::cin >> quantity;
  char instruction;
  int number;
  int previous_result = -1;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction >> number;
    if (instruction == '+') {
      if (previous_result != -1) {
        number = (number + previous_result) % kDigit;
      }
      tree.Insert(number);
      previous_result = -1;
    } else if (instruction == '?') {
      previous_result = tree.Find(number);
      std::cout << previous_result << '\n';
    }
  }
}