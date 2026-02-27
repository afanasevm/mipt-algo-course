#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class Node {
  static std::mt19937 rnd;
  Node* left_child_ = nullptr;
  Node* right_child_ = nullptr;
  int value_;
  int key_;
  int quantity_;

  Node(int value) {
    value_ = value;
    key_ = rnd();
    quantity_ = 1;
  }

  ~Node() {
    delete left_child_;
    delete right_child_;
  }

  friend class Treap;
  friend class TreeSegments;
};

class Treap {
  Node* root_ = nullptr;

  static void UpdateQuantity(Node* node) {
    node->quantity_ = 1;
    if (node->left_child_ != nullptr) {
      node->quantity_ += node->left_child_->quantity_;
    }
    if (node->right_child_ != nullptr) {
      node->quantity_ += node->right_child_->quantity_;
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
      UpdateQuantity(left);
      return left;
    }
    right->left_child_ = Merge(left, right->left_child_);
    UpdateQuantity(right);
    return right;
  }

  std::pair<Node*, Node*> Split(Node* node, int value) {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (node->value_ > value) {
      std::pair<Node*, Node*> result = Split(node->left_child_, value);
      node->left_child_ = result.second;
      UpdateQuantity(node);
      return {result.first, node};
    }
    std::pair<Node*, Node*> result = Split(node->right_child_, value);
    node->right_child_ = result.first;
    UpdateQuantity(node);
    return {node, result.second};
  }

  Node* DeleteOneElement(Node* node) {
    Node* temp = Merge(node->left_child_, node->right_child_);
    node->left_child_ = nullptr;
    node->right_child_ = nullptr;
    delete node;
    return temp;
  }

  void Insert(int value) {
    Node* node = new Node(value);
    std::pair<Node*, Node*> temp = Split(root_, value);
    root_ = Merge(Merge(temp.first, node), temp.second);
  }

  void Delete(int value) {
    std::pair<Node*, Node*> temp = Split(root_, value);
    std::pair<Node*, Node*> temp1 = Split(temp.first, value - 1);
    temp1.second = DeleteOneElement(temp1.second);
    root_ = Merge(Merge(temp1.first, temp1.second), temp.second);
  }

  int FindQuantity(int value) {
    int result = 0;
    std::pair<Node*, Node*> temp = Split(root_, value);
    if (temp.first != nullptr) {
      result = temp.first->quantity_;
    }
    root_ = Merge(temp.first, temp.second);
    return result;
  }

  Treap() {}

  Treap(int value) { Insert(value); }

  ~Treap() { delete root_; }

  friend class NodeWithTreap;
  friend class TreeSegments;
};

class NodeWithTreap {
  NodeWithTreap* left_child_ = nullptr;
  NodeWithTreap* right_child_ = nullptr;
  int left_border_;
  int right_border_;
  Treap* treap_ = nullptr;

  ~NodeWithTreap() {
    delete treap_;
    delete left_child_;
    delete right_child_;
  }

  friend class TreeSegments;
};

class TreeSegments {
  NodeWithTreap* root_ = nullptr;

  void InsertChildren(Treap* node, Node* child) {
    if (child != nullptr) {
      node->Insert(child->value_);
      InsertChildren(node, child->left_child_);
      InsertChildren(node, child->right_child_);
    }
  }

  void MergeChildren(NodeWithTreap* node) {
    node->left_border_ = node->left_child_->left_border_;
    node->right_border_ = node->right_child_->right_border_;
    node->treap_ = new Treap;
    InsertChildren(node->treap_, node->left_child_->treap_->root_);
    InsertChildren(node->treap_, node->right_child_->treap_->root_);
  }

  void Build(NodeWithTreap* node, int left_border, int right_border,
             std::vector<int>& array) {
    if (node == nullptr) {
      node = new NodeWithTreap;
      root_ = node;
    }
    if (left_border == right_border) {
      node->left_border_ = left_border;
      node->right_border_ = right_border;
      node->treap_ = new Treap(array[left_border]);
    } else {
      node->left_child_ = new NodeWithTreap;
      node->right_child_ = new NodeWithTreap;
      int middle = (left_border + right_border) / 2;
      Build(node->left_child_, left_border, middle, array);
      Build(node->right_child_, middle + 1, right_border, array);
      MergeChildren(node);
    }
  }

  int FindQuantity(NodeWithTreap* node, int index_l, int index_r, int index_x,
                   int index_y) {
    if (index_l > index_r) {
      return 0;
    }
    int result = 0;
    if (node->left_border_ == index_l && node->right_border_ == index_r) {
      result = node->treap_->FindQuantity(index_y) -
               node->treap_->FindQuantity(index_x - 1);
    } else {
      int middle = (node->left_border_ + node->right_border_) / 2;
      result = FindQuantity(node->left_child_, index_l,
                            std::min(middle, index_r), index_x, index_y) +
               FindQuantity(node->right_child_, std::max(index_l, middle + 1),
                            index_r, index_x, index_y);
    }
    return result;
  }

public:
  void BuildTreeSegments(std::vector<int>& array, int quantity) {
    Build(root_, 0, quantity - 1, array);
  }

  int FindQuantity(int index_l, int index_r, int index_x, int index_y) {
    return FindQuantity(root_, index_l, index_r, index_x, index_y);
  }

  void UpdateElement(int index, int value, int prev_value) {
    NodeWithTreap* unit = root_;
    while (unit != nullptr) {
      unit->treap_->Delete(prev_value);
      unit->treap_->Insert(value);
      if (index <= (unit->left_border_ + unit->right_border_) / 2) {
        unit = unit->left_child_;
      } else {
        unit = unit->right_child_;
      }
    }
  }

  ~TreeSegments() { delete root_; }
};

std::mt19937 Node::rnd(
  std::chrono::steady_clock::now().time_since_epoch().count());

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int quantity_cars;
  int quantity;
  std::cin >> quantity_cars >> quantity;
  std::vector<int> cars(quantity_cars);
  for (int i = 0; i < quantity_cars; i++) {
    std::cin >> cars[i];
  }
  TreeSegments tree;
  tree.BuildTreeSegments(cars, quantity_cars);
  std::string instruction;
  int index_l;
  int index_r;
  int index_x;
  int index_y;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction >> index_l >> index_r;
    if (instruction == "SET") {
      tree.UpdateElement(index_l - 1, index_r, cars[index_l - 1]);
      cars[index_l - 1] = index_r;
    } else if (instruction == "GET") {
      std::cin >> index_x >> index_y;
      std::cout << tree.FindQuantity(index_l - 1, index_r - 1, index_x, index_y)
                << "\n";
    }
  }
}