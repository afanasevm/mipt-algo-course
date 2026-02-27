#include <iostream>
#include <string>
#include <vector>

class MinMaxBinaryHeap {
public:
  int size = 0;
  std::vector<int> binary_heap_min;
  std::vector<int> binary_heap_max;

private:
  void SiftUpMin(int index);
  void SiftUpMax(int index);
  void SiftDownMin(int index);
  void SiftDownMax(int index);

public:
  void Insert(int number);
  void GetMin();
  void ExtractMin();
  void GetMax();
  void ExtractMax();
  void Size() const;
  void Clear();
};

void MinMaxBinaryHeap::SiftUpMin(int index) {
  while (index != 0) {
    if (binary_heap_min[index] < binary_heap_min[(index - 1) / 2]) {
      std::swap(binary_heap_min[index], binary_heap_min[(index - 1) / 2]);
      index = (index - 1) / 2;
    } else {
      break;
    }
  }
}

void MinMaxBinaryHeap::SiftUpMax(int index) {
  while (index != 0) {
    if (binary_heap_max[index] > binary_heap_max[(index - 1) / 2]) {
      std::swap(binary_heap_max[index], binary_heap_max[(index - 1) / 2]);
      index = (index - 1) / 2;
    } else {
      break;
    }
  }
}

void MinMaxBinaryHeap::SiftDownMin(int index) {
  while ((index * 2 + 1) < size) {
    int index_child = index * 2 + 1;
    if (((index_child + 1) < size) &&
        (binary_heap_min[index_child + 1] < binary_heap_min[index_child])) {
      index_child++;
    }
    if (binary_heap_min[index_child] < binary_heap_min[index]) {
      std::swap(binary_heap_min[index_child], binary_heap_min[index]);
      index = index_child;
    } else {
      break;
    }
  }
}

void MinMaxBinaryHeap::SiftDownMax(int index) {
  while ((index * 2 + 1) < size) {
    int index_child = index * 2 + 1;
    if (((index_child + 1) < size) &&
        (binary_heap_max[index_child + 1] > binary_heap_max[index_child])) {
      index_child++;
    }
    if (binary_heap_max[index_child] > binary_heap_max[index]) {
      std::swap(binary_heap_max[index_child], binary_heap_max[index]);
      index = index_child;
    } else {
      break;
    }
  }
}

void MinMaxBinaryHeap::Insert(int number) {
  binary_heap_min.push_back(number);
  SiftUpMin(size);
  binary_heap_max.push_back(number);
  SiftUpMax(size);
  size++;
  std::cout << "ok\n";
}

void MinMaxBinaryHeap::GetMin() {
  if (size > 0) {
    std::cout << binary_heap_min[0] << "\n";
  } else {
    std::cout << "error\n";
  }
}

void MinMaxBinaryHeap::ExtractMin() {
  if (size > 0) {
    int number = binary_heap_min[0];
    binary_heap_min[0] = binary_heap_min[size - 1];
    binary_heap_min.pop_back();
    SiftDownMin(0);
    for (int i = size - 1; i >= 0; i--) {
      if (binary_heap_max[i] == number) {
        binary_heap_max[i] = binary_heap_max[size - 1];
        binary_heap_max.pop_back();
        SiftDownMax(i);
        SiftUpMax(i);
        break;
      }
    }
    std::cout << number << "\n";
    size--;
  } else {
    std::cout << "error\n";
  }
}

void MinMaxBinaryHeap::GetMax() {
  if (size > 0) {
    std::cout << binary_heap_max[0] << "\n";
  } else {
    std::cout << "error\n";
  }
}

void MinMaxBinaryHeap::ExtractMax() {
  if (size > 0) {
    int number = binary_heap_max[0];
    binary_heap_max[0] = binary_heap_max[size - 1];
    binary_heap_max.pop_back();
    SiftDownMax(0);
    for (int i = size - 1; i >= 0; i--) {
      if (binary_heap_min[i] == number) {
        binary_heap_min[i] = binary_heap_min[size - 1];
        binary_heap_min.pop_back();
        SiftDownMin(i);
        SiftUpMin(i);
        break;
      }
    }
    std::cout << number << "\n";
    size--;
  } else {
    std::cout << "error\n";
  }
}

void MinMaxBinaryHeap::Size() const { std::cout << size << "\n"; }

void MinMaxBinaryHeap::Clear() {
  binary_heap_min.clear();
  binary_heap_max.clear();
  size = 0;
  std::cout << "ok\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  MinMaxBinaryHeap min_max_binary_heap;
  int quantity;
  std::cin >> quantity;
  std::string instruction;
  int number;
  for (int i = 0; i < quantity; i++) {
    std::cin >> instruction;
    if (instruction == "insert") {
      std::cin >> number;
      min_max_binary_heap.Insert(number);
    } else if (instruction == "extract_min") {
      min_max_binary_heap.ExtractMin();
    } else if (instruction == "get_min") {
      min_max_binary_heap.GetMin();
    } else if (instruction == "extract_max") {
      min_max_binary_heap.ExtractMax();
    } else if (instruction == "get_max") {
      min_max_binary_heap.GetMax();
    } else if (instruction == "size") {
      min_max_binary_heap.Size();
    } else if (instruction == "clear") {
      min_max_binary_heap.Clear();
    }
  }
}