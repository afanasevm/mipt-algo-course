#include <iostream>
#include <vector>

const int kA = 543463;
const int kB = 234979;
const int kBigPrime = 999999937;
const int kSize = 16;
const float kLoad = 0.95;

class Pokemon {
  int type_;
  int quantity_;

public:
  Pokemon() {}

  Pokemon(int type, int quantity) : type_(type), quantity_(quantity) {}

  Pokemon(int type) : Pokemon(type, 1) {}

  friend class List;
  friend class HashTable;
};

class ListNode {
  ListNode* next_ = nullptr;
  Pokemon value_;

  ListNode(Pokemon pokemon) : value_(pokemon){};

  ~ListNode() { delete next_; }

  friend class List;
};

class List {
  ListNode* root_ = nullptr;

public:
  bool IsEmpty() { return (root_ == nullptr); }

  Pokemon DeleteFirst() {
    ListNode* node = root_;
    root_ = root_->next_;
    Pokemon result = node->value_;
    node->next_ = nullptr;
    delete node;
    return result;
  }

  bool Insert(Pokemon pokemon) {
    if (root_ == nullptr) {
      root_ = new ListNode(pokemon);
      return true;
    }
    ListNode* unit = root_;
    while (unit->next_ != nullptr && unit->value_.type_ != pokemon.type_) {
      unit = unit->next_;
    }
    if (unit->value_.type_ == pokemon.type_) {
      unit->value_.quantity_ += pokemon.quantity_;
      return false;
    }
    unit->next_ = new ListNode(pokemon);
    return true;
  }

  bool Delete(Pokemon pokemon) {
    if (root_ == nullptr) {
      return false;
    }
    if (root_->value_.type_ == pokemon.type_) {
      root_->value_.quantity_ -= pokemon.quantity_;
      if (root_->value_.quantity_ <= 0) {
        ListNode* node = root_;
        root_ = root_->next_;
        node->next_ = nullptr;
        delete node;
        return true;
      }
      return false;
    }
    ListNode* unit = root_;
    while (unit->next_ != nullptr &&
           unit->next_->value_.type_ != pokemon.type_) {
      unit = unit->next_;
    }
    if (unit->next_ != nullptr && unit->next_->value_.type_ == pokemon.type_) {
      unit->next_->value_.quantity_ -= pokemon.quantity_;
      if (unit->next_->value_.quantity_ <= 0) {
        ListNode* node_for_delete = unit->next_;
        unit->next_ = node_for_delete->next_;
        node_for_delete->next_ = nullptr;
        delete node_for_delete;
        return true;
      }
      return false;
    }
    return false;
  }

  bool Find(Pokemon pokemon) {
    if (root_ == nullptr) {
      return false;
    }
    ListNode* unit = root_;
    while (unit->next_ != nullptr && unit->value_.type_ != pokemon.type_) {
      unit = unit->next_;
    }
    return (unit->value_.type_ == pokemon.type_);
  }

  ~List() { delete root_; }
};

int Hash(int value, int size) {
  return (static_cast<long long>(kA) * value + kB) % kBigPrime % size;
}

class HashTable {
  int size_ = kSize;
  std::vector<List*> table_ = std::vector<List*>(size_, nullptr);
  int quantity_elements_ = 0;

  void ReHash() {
    size_ *= 2;
    quantity_elements_ = 0;
    std::vector<List*> temp_table = table_;
    table_ = std::vector<List*>(size_, nullptr);
    Pokemon pokemon;
    for (List* list : temp_table) {
      if (list == nullptr) {
        continue;
      }
      while (!list->IsEmpty()) {
        pokemon = list->DeleteFirst();
        Insert(pokemon);
      }
      delete list;
    }
  }

public:
  void Insert(Pokemon pokemon) {
    int value_of_hash = Hash(pokemon.type_, size_);
    if (table_[value_of_hash] == nullptr) {
      table_[value_of_hash] = new List;
    }
    if (table_[value_of_hash]->Insert(pokemon)) {
      quantity_elements_++;
    }
    if (static_cast<float>(quantity_elements_) / size_ > kLoad) {
      ReHash();
    }
  }

  void Delete(Pokemon pokemon) {
    int value_of_hash = Hash(pokemon.type_, size_);
    if (table_[value_of_hash] == nullptr) {
      return;
    }
    if (table_[value_of_hash]->Delete(pokemon)) {
      quantity_elements_--;
    }
  }

  bool Find(Pokemon pokemon) {
    int value_of_hash = Hash(pokemon.type_, size_);
    if (table_[value_of_hash] == nullptr) {
      return false;
    }
    return table_[value_of_hash]->Find(pokemon);
  }

  ~HashTable() {
    for (List* list : table_) {
      delete list;
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  HashTable table;
  int quantity_pokemons;
  int pokemon_type;
  std::cin >> quantity_pokemons;
  for (int i = 0; i < quantity_pokemons; i++) {
    std::cin >> pokemon_type;
    table.Insert(Pokemon(pokemon_type));
  }
  std::cin >> quantity_pokemons;
  int quantity_result = 0;
  std::vector<int> pokemons_result;
  for (int i = 0; i < quantity_pokemons; i++) {
    std::cin >> pokemon_type;
    if (table.Find(Pokemon(pokemon_type))) {
      quantity_result++;
      table.Delete(Pokemon(pokemon_type));
      pokemons_result.push_back(pokemon_type);
    }
  }
  std::cout << quantity_result << "\n";
  for (int i = 0; i < quantity_result; i++) {
    std::cout << pokemons_result[i] << " ";
  }
}