#include <algorithm>
#include <iostream>
#include <string>

const int kMagic = 1000000001;

enum class Colors { Red, Black };

class Node {
  Node* parent_ = nullptr;
  Node* left_child_ = nullptr;
  Node* right_child_ = nullptr;
  Colors color_ = Colors::Black;
  int value_;
  int left_quantity_ = 0;
  bool can_be_destroyed_ = true;

  ~Node() {
    if (can_be_destroyed_) {
      if (left_child_->can_be_destroyed_) {
        delete left_child_;
      }
      if (right_child_->can_be_destroyed_) {
        delete right_child_;
      }
    }
  }

  Node* Grandparent() { return parent_->parent_; }

  Node* Brother() {
    if (parent_->left_child_ == this) {
      return parent_->right_child_;
    }
    return parent_->left_child_;
  }

  Node* Uncle() {
    if (parent_->parent_->left_child_ == parent_) {
      return parent_->parent_->right_child_;
    }
    return parent_->parent_->left_child_;
  }

  friend class RedBlackTree;
};

class RedBlackTree {
  Node* root_ = nullptr;
  Node* empty_black_leaf_ = new Node;

  void RootUp() {
    if (root_ == nullptr) {
      return;
    }
    while (root_->parent_ != nullptr) {
      root_ = root_->parent_;
    }
  }

  void LeftRotate(Node* node) {
    Node* temp = node->right_child_;
    temp->parent_ = node->parent_;
    node->right_child_ = temp->left_child_;
    if (temp->left_child_ != empty_black_leaf_) {
      temp->left_child_->parent_ = node;
    }
    temp->left_child_ = node;
    node->parent_ = temp;
    node = temp;
    if (node->parent_ != nullptr) {
      if (node->value_ < node->parent_->value_) {
        node->parent_->left_child_ = node;
      } else {
        node->parent_->right_child_ = node;
      }
    }
    node->left_quantity_ += node->left_child_->left_quantity_;
  }

  void RightRotate(Node* node) {
    Node* temp = node->left_child_;
    temp->parent_ = node->parent_;
    node->left_child_ = temp->right_child_;
    if (temp->right_child_ != empty_black_leaf_) {
      temp->right_child_->parent_ = node;
    }
    temp->right_child_ = node;
    node->parent_ = temp;
    node = temp;
    if (node->parent_ != nullptr) {
      if (node->value_ < node->parent_->value_) {
        node->parent_->left_child_ = node;
      } else {
        node->parent_->right_child_ = node;
      }
    }
    node->right_child_->left_quantity_ -= node->left_quantity_;
  }

  void RotateUp(Node* node) {
    if (node == node->parent_->left_child_) {
      RightRotate(node->parent_);
    } else {
      LeftRotate(node->parent_);
    }
  }

  static void UpdateLeftQuantity(Node* node, int value) {
    Node* unit = node;
    while (unit->parent_ != nullptr) {
      if (unit->parent_->left_child_ == unit) {
        unit->parent_->left_quantity_ += value;
      }
      unit = unit->parent_;
    }
  }

  void FixRedUncle(Node* node) {
    node->parent_->color_ = Colors::Black;
    node->Grandparent()->color_ = Colors::Red;
    node->Uncle()->color_ = Colors::Black;
    FixAfterInsert(node->Grandparent());
  }

  void FixBlackUncle(Node* node) {
    if ((node == node->parent_->left_child_ &&
         node->parent_ == node->Grandparent()->left_child_) ||
        (node == node->parent_->right_child_ &&
         node->parent_ == node->Grandparent()->right_child_)) {
      node->parent_->color_ = Colors::Black;
      node->Grandparent()->color_ = Colors::Red;
      RotateUp(node->parent_);
    } else {
      node->color_ = Colors::Black;
      node->Grandparent()->color_ = Colors::Red;
      RotateUp(node);
      RotateUp(node);
    }
  }

  void FixAfterInsert(Node* node) {
    if (node->parent_ == nullptr) {
      node->color_ = Colors::Black;
      return;
    }
    if (node->parent_->color_ == Colors::Red) {
      if (node->Uncle()->color_ == Colors::Red) {
        FixRedUncle(node);
      } else {
        FixBlackUncle(node);
      }
    }
  }

  void DeleteRedLeaf(Node* node) {
    if (node->parent_->left_child_ == node) {
      node->parent_->left_child_ = empty_black_leaf_;
    } else {
      node->parent_->right_child_ = empty_black_leaf_;
    }
    delete node;
  }

  void DeleteBlackBrother(Node* node) {
    if (node == node->parent_->left_child_) {
      if (node->parent_->right_child_->right_child_->color_ == Colors::Red) {
        node->parent_->right_child_->color_ = node->parent_->color_;
        node->parent_->color_ = Colors::Black;
        node->parent_->right_child_->right_child_->color_ = Colors::Black;
        LeftRotate(node->parent_);
        if (node->Grandparent() == nullptr) {
          node->parent_->color_ = Colors::Black;
        }
      } else if (node->parent_->right_child_->left_child_->color_ ==
                 Colors::Red) {
        node->parent_->right_child_->color_ = Colors::Red;
        node->parent_->right_child_->left_child_->color_ = Colors::Black;
        RightRotate(node->parent_->right_child_);
        DeleteBlackBrother(node);
      } else {
        node->parent_->right_child_->color_ = Colors::Red;
        Colors temp = node->parent_->color_;
        node->parent_->color_ = Colors::Black;
        if (temp == Colors::Black) {
          DeleteBlackLeaf(node->parent_, false);
        }
      }
    } else if (node->parent_->left_child_->left_child_->color_ == Colors::Red) {
      node->parent_->left_child_->color_ = node->parent_->color_;
      node->parent_->color_ = Colors::Black;
      node->parent_->left_child_->left_child_->color_ = Colors::Black;
      RightRotate(node->parent_);
      if (node->Grandparent() == nullptr) {
        node->parent_->color_ = Colors::Black;
      }
    } else if (node->parent_->left_child_->right_child_->color_ ==
               Colors::Red) {
      node->parent_->left_child_->color_ = Colors::Red;
      node->parent_->left_child_->right_child_->color_ = Colors::Black;
      LeftRotate(node->parent_->left_child_);
      DeleteBlackBrother(node);
    } else {
      node->parent_->left_child_->color_ = Colors::Red;
      Colors temp = node->parent_->color_;
      node->parent_->color_ = Colors::Black;
      if (temp == Colors::Black) {
        DeleteBlackLeaf(node->parent_, false);
      }
    }
  }

  void DeleteRedBrother(Node* node) {
    if (node == node->parent_->left_child_) {
      node->parent_->color_ = Colors::Red;
      node->parent_->right_child_->color_ = Colors::Black;
      LeftRotate(node->parent_);
      DeleteBlackBrother(node);
    } else {
      node->parent_->color_ = Colors::Red;
      node->parent_->left_child_->color_ = Colors::Black;
      RightRotate(node->parent_);
      DeleteBlackBrother(node);
    }
  }

  void DeleteBlackLeaf(Node* node, bool delete_this_node) {
    if (node->parent_ == nullptr) {
      node->color_ = Colors::Black;
    } else {
      if (node->Brother()->color_ == Colors::Black) {
        DeleteBlackBrother(node);
      } else {
        DeleteRedBrother(node);
      }
    }
    if (delete_this_node) {
      if (node->parent_ == nullptr) {
        root_ = nullptr;
      } else if (node == node->parent_->left_child_) {
        node->parent_->left_child_ = empty_black_leaf_;
      } else {
        node->parent_->right_child_ = empty_black_leaf_;
      }
      delete node;
    }
  }

  void DeleteNotLeaf(Node* node) {
    if (node->left_child_ != empty_black_leaf_) {
      node->left_child_->color_ = Colors::Black;
      node->left_child_->parent_ = node->parent_;
      if (node->parent_ != nullptr) {
        if (node->left_child_->value_ < node->parent_->value_) {
          node->parent_->left_child_ = node->left_child_;
        } else {
          node->parent_->right_child_ = node->left_child_;
        }
      } else {
        root_ = node->left_child_;
      }
      node->left_child_ = empty_black_leaf_;
    } else {
      node->right_child_->color_ = Colors::Black;
      node->right_child_->parent_ = node->parent_;
      if (node->parent_ != nullptr) {
        if (node->right_child_->value_ < node->parent_->value_) {
          node->parent_->left_child_ = node->right_child_;
        } else {
          node->parent_->right_child_ = node->right_child_;
        }
      } else {
        root_ = node->right_child_;
      }
      node->right_child_ = empty_black_leaf_;
    }
    delete node;
  }

  void FixAfterDelete(Node* node) {
    if (node->left_child_ == empty_black_leaf_ &&
        node->right_child_ == empty_black_leaf_) {
      if (node->color_ == Colors::Red) {
        DeleteRedLeaf(node);
      } else {
        DeleteBlackLeaf(node, true);
      }
    } else {
      DeleteNotLeaf(node);
    }
  }

 public:
  RedBlackTree() { empty_black_leaf_->can_be_destroyed_ = false; }

  bool Exists(int value) {
    if (root_ == nullptr) {
      return false;
    }
    Node* unit = root_;
    while (unit != empty_black_leaf_) {
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

  void Insert(int value) {
    if (Exists(value)) {
      return;
    }
    Node* node = new Node;
    node->value_ = value;
    node->left_child_ = empty_black_leaf_;
    node->right_child_ = empty_black_leaf_;
    node->left_quantity_ = 1;
    if (root_ == nullptr) {
      root_ = node;
      return;
    }
    node->color_ = Colors::Red;
    Node* unit = root_;
    Node* prev;
    while (unit != empty_black_leaf_) {
      prev = unit;
      if (unit->value_ < value) {
        unit = unit->right_child_;
      } else {
        unit = unit->left_child_;
      }
    }
    node->parent_ = prev;
    if (prev->value_ < value) {
      prev->right_child_ = node;
    } else {
      prev->left_child_ = node;
    }
    UpdateLeftQuantity(node, 1);
    FixAfterInsert(node);
    RootUp();
  }

  void Delete(int value) {
    if (!Exists(value)) {
      return;
    }
    Node* unit = root_;
    while (unit->value_ != value) {
      if (unit->value_ < value) {
        unit = unit->right_child_;
      } else {
        unit = unit->left_child_;
      }
    }
    if (unit->left_child_ != empty_black_leaf_ &&
        unit->right_child_ != empty_black_leaf_) {
      Node* temp = unit->left_child_;
      while (temp->right_child_ != empty_black_leaf_) {
        temp = temp->right_child_;
      }
      unit->value_ = temp->value_;
      unit = temp;
    }
    UpdateLeftQuantity(unit, -1);
    FixAfterDelete(unit);
    RootUp();
  }

  int Next(int value) {
    int result = kMagic;
    if (root_ == nullptr) {
      return result;
    }
    Node* unit = root_;
    while (unit != empty_black_leaf_) {
      if (unit->value_ <= value) {
        unit = unit->right_child_;
      } else {
        result = std::min(result, unit->value_);
        unit = unit->left_child_;
      }
    }
    return result;
  }

  int Prev(int value) {
    int result = -kMagic;
    if (root_ == nullptr) {
      return result;
    }
    Node* unit = root_;
    while (unit != empty_black_leaf_) {
      if (unit->value_ < value) {
        result = std::max(result, unit->value_);
        unit = unit->right_child_;
      } else {
        unit = unit->left_child_;
      }
    }
    return result;
  }

  int Kth(int value) {
    int result = kMagic;
    if (root_ == nullptr) {
      return result;
    }
    Node* unit = root_;
    while (unit != empty_black_leaf_) {
      if (unit->left_quantity_ == value) {
        result = unit->value_;
        break;
      }
      if (unit->left_quantity_ < value) {
        value -= unit->left_quantity_;
        unit = unit->right_child_;
      } else {
        unit = unit->left_child_;
      }
    }
    return result;
  }

  ~RedBlackTree() {
    delete root_;
    delete empty_black_leaf_;
  }
};

void ProcessRequest(RedBlackTree& tree, std::string& instruction, int number) {
  int result;
  if (instruction == "insert") {
    tree.Insert(number);
  } else if (instruction == "delete") {
    tree.Delete(number);
  } else if (instruction == "exists") {
    if (tree.Exists(number)) {
      std::cout << "true\n";
    } else {
      std::cout << "false\n";
    }
  } else if (instruction == "next") {
    result = tree.Next(number);
    if (result != kMagic) {
      std::cout << result << "\n";
    } else {
      std::cout << "none\n";
    }
  } else if (instruction == "prev") {
    result = tree.Prev(number);
    if (result != -kMagic) {
      std::cout << result << "\n";
    } else {
      std::cout << "none\n";
    }
  } else if (instruction == "kth") {
    result = tree.Kth(number + 1);
    if (result != kMagic) {
      std::cout << result << "\n";
    } else {
      std::cout << "none\n";
    }
  }
}

int main() {
  RedBlackTree tree;
  std::string instruction;
  int number;
  while (std::cin >> instruction >> number) {
    ProcessRequest(tree, instruction, number);
  }
}