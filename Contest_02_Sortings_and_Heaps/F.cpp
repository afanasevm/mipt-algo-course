#include <iostream>
#include <string>
#include <vector>

class BinaryHeapMin {
 public:
  int size = 0;
  std::vector<std::pair<long long, int>> binary_heap_min;

 private:
  void SiftUp(int index);
  void SiftDown(int index);

 public:
  void Insert(long long number, int call_number);
  void GetMin();
  void ExtractMin();
  void DecreaseKey(int call_number, long long key);
};

void BinaryHeapMin::SiftUp(int index) {
  while (index != 0) {
    if (binary_heap_min[index].first < binary_heap_min[(index - 1) / 2].first) {
      std::swap(binary_heap_min[index], binary_heap_min[(index - 1) / 2]);
      index = (index - 1) / 2;
    } else {
      break;
    }
  }
}

void BinaryHeapMin::SiftDown(int index) {
  while ((index * 2 + 1) < size) {
    int index_child = index * 2 + 1;
    if (((index_child + 1) < size) && (binary_heap_min[index_child + 1].first <
                                       binary_heap_min[index_child].first)) {
      index_child++;
    }
    if (binary_heap_min[index_child].first < binary_heap_min[index].first) {
      std::swap(binary_heap_min[index_child], binary_heap_min[index]);
      index = index_child;
    } else {
      break;
    }
  }
}

void BinaryHeapMin::Insert(long long number, int call_number) {
  binary_heap_min.push_back(std::make_pair(number, call_number));
  SiftUp(size++);
}

void BinaryHeapMin::GetMin() { std::cout << binary_heap_min[0].first << "\n"; }

void BinaryHeapMin::ExtractMin() {
  binary_heap_min[0] = binary_heap_min[--size];
  binary_heap_min.pop_back();
  SiftDown(0);
}

void BinaryHeapMin::DecreaseKey(int call_number, long long key) {
  for (int i = 0; i < size; i++) {
    if (binary_heap_min[i].second == call_number) {
      binary_heap_min[i].first -= key;
      SiftUp(i);
      break;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  BinaryHeapMin binary_heap_min;
  int quantity;
  std::cin >> quantity;
  std::string instruction;
  long long number;
  int key;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction;
    if (instruction == "insert") {
      std::cin >> number;
      binary_heap_min.Insert(number, i);
    } else if (instruction == "getMin") {
      binary_heap_min.GetMin();
    } else if (instruction == "extractMin") {
      binary_heap_min.ExtractMin();
    } else if (instruction == "decreaseKey") {
      std::cin >> key >> number;
      binary_heap_min.DecreaseKey(key - 1, number);
    }
  }
}