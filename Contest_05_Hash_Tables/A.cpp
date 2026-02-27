#include <chrono>
#include <iostream>
#include <random>
#include <vector>

const int kSize = 16;
const float kLoad = 0.95;

class ListNode {
  ListNode* next_ = nullptr;
  int value_;

  ListNode(int value) : value_(value){};

  ~ListNode() { delete next_; }

  friend class List;
};

class List {
  ListNode* root_ = nullptr;

public:
  bool IsEmpty() { return (root_ == nullptr); }

  int DeleteFirst() {
    ListNode* node = root_;
    root_ = root_->next_;
    int result = node->value_;
    node->next_ = nullptr;
    delete node;
    return result;
  }

  bool Insert(int value) {
    if (root_ == nullptr) {
      root_ = new ListNode(value);
      return true;
    }
    ListNode* unit = root_;
    while (unit->next_ != nullptr && unit->value_ != value) {
      unit = unit->next_;
    }
    if (unit->value_ == value) {
      return false;
    }
    unit->next_ = new ListNode(value);
    return true;
  }

  bool Delete(int value) {
    if (root_ == nullptr) {
      return false;
    }
    if (root_->value_ == value) {
      ListNode* node = root_;
      root_ = root_->next_;
      node->next_ = nullptr;
      delete node;
      return true;
    }
    ListNode* unit = root_;
    while (unit->next_ != nullptr && unit->next_->value_ != value) {
      unit = unit->next_;
    }
    if (unit->next_ != nullptr && unit->next_->value_ == value) {
      ListNode* node_for_delete = unit->next_;
      unit->next_ = node_for_delete->next_;
      node_for_delete->next_ = nullptr;
      delete node_for_delete;
      return true;
    }
    return false;
  }

  bool Find(int value) {
    if (root_ == nullptr) {
      return false;
    }
    ListNode* unit = root_;
    while (unit->next_ != nullptr && unit->value_ != value) {
      unit = unit->next_;
    }
    return (unit->value_ == value);
  }

  ~List() { delete root_; }
};

class HashFunction {
  int aa_;
  int bb_;
  int pp_;

public:
  HashFunction(int value) {
    std::mt19937 rnd(
      std::chrono::steady_clock::now().time_since_epoch().count());
    aa_ = rnd();
    bb_ = rnd();
    pp_ = value;
    while (aa_ % pp_ == 0) {
      aa_ = rnd();
    }
  }

  int Hash(int value) const {
    return std::abs((static_cast<long long>(aa_) * value + bb_) % pp_);
  }
};

class HashTable {
  int size_ = kSize;
  std::vector<List*> table_ = std::vector<List*>(size_, nullptr);
  HashFunction hash_ = HashFunction(size_);
  int quantity_elements_ = 0;

  void ReHash() {
    size_ *= 2;
    hash_ = HashFunction(size_);
    quantity_elements_ = 0;
    std::vector<List*> temp_table = table_;
    table_ = std::vector<List*>(size_, nullptr);
    int number;
    for (List* list : temp_table) {
      if (list == nullptr) {
        continue;
      }
      while (!list->IsEmpty()) {
        number = list->DeleteFirst();
        Insert(number);
      }
      delete list;
    }
  }

public:
  void Insert(int value) {
    int value_of_hash = hash_.Hash(value);
    if (table_[value_of_hash] == nullptr) {
      table_[value_of_hash] = new List;
    }
    if (table_[value_of_hash]->Insert(value)) {
      quantity_elements_++;
    }
    if (static_cast<float>(quantity_elements_) / size_ > kLoad) {
      ReHash();
    }
  }

  void Delete(int value) {
    int value_of_hash = hash_.Hash(value);
    if (table_[value_of_hash] == nullptr) {
      return;
    }
    if (table_[value_of_hash]->Delete(value)) {
      quantity_elements_--;
    }
  }

  bool Find(int value) {
    int value_of_hash = hash_.Hash(value);
    if (table_[value_of_hash] == nullptr) {
      return false;
    }
    return table_[value_of_hash]->Find(value);
  }

  ~HashTable() {
    for (List* list : table_) {
      delete list;
    }
  }
};

int main() {
  HashTable hash_table;
  int quantity;
  std::cin >> quantity;
  char instruction;
  int number;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction >> number;
    if (instruction == '+') {
      hash_table.Insert(number);
    } else if (instruction == '-') {
      hash_table.Delete(number);
    } else if (instruction == '?') {
      if (hash_table.Find(number)) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
  }
}