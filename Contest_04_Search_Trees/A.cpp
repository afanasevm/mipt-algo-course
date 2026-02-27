#include <iostream>
#include <stack>
#include <vector>

class Node {
  Node* parent_ = nullptr;
  Node* left_child_ = nullptr;
  Node* right_child_ = nullptr;
  int key_;
  int priority_;
  int number_;

  ~Node() {
    delete left_child_;
    delete right_child_;
  }

  friend class Treap;
};

class Treap {
  Node* root_ = nullptr;
  std::stack<Node*> right_branch_;
  std::vector<Node*> nodes_;

public:
  void Insert(int number, int key, int priority) {
    Node* node = new Node;
    node->number_ = number;
    node->key_ = key;
    node->priority_ = priority;
    if (root_ == nullptr) {
      root_ = node;
    } else {
      while (!right_branch_.empty() &&
             right_branch_.top()->priority_ > node->priority_) {
        right_branch_.pop();
      }
      if (right_branch_.empty()) {
        root_->parent_ = node;
        node->left_child_ = root_;
        root_ = node;
      } else {
        node->left_child_ = right_branch_.top()->right_child_;
        if (node->left_child_ != nullptr) {
          node->left_child_->parent_ = node;
        }
        right_branch_.top()->right_child_ = node;
        node->parent_ = right_branch_.top();
      }
    }
    right_branch_.push(node);
    nodes_.push_back(node);
  }

  void GetTree() {
    std::cout << "YES"
              << "\n";
    for (Node* unit : nodes_) {
      if (unit->parent_ != nullptr) {
        std::cout << unit->parent_->number_ << " ";
      } else {
        std::cout << "0 ";
      }
      if (unit->left_child_ != nullptr) {
        std::cout << unit->left_child_->number_ << " ";
      } else {
        std::cout << "0 ";
      }
      if (unit->right_child_ != nullptr) {
        std::cout << unit->right_child_->number_ << "\n";
      } else {
        std::cout << "0\n";
      }
    }
  }

  ~Treap() { delete root_; }
};

int main() {
  int quantity;
  std::cin >> quantity;
  int key;
  int priority;
  Treap tree;
  for (int i = 0; i < quantity; i++) {
    std::cin >> key >> priority;
    tree.Insert(i + 1, key, priority);
  }
  tree.GetTree();
}