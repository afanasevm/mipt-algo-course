#include <deque>
#include <iostream>
#include <vector>

void MaximumOnLine(
  int coord_x, int coord_y, int size_z,
  std::vector<std::vector<std::vector<std::vector<int>>>>& signs,
  int visibility_z) {
  std::deque<std::vector<int>> deque;
  std::vector<int> sign;
  for (int i = 0; i < visibility_z; i++) {
    while (!deque.empty() &&
           (deque.back()[0] < signs[coord_x][coord_y][i][0])) {
      deque.pop_back();
    }
    deque.push_back(signs[coord_x][coord_y][i]);
  }
  for (int i = 0; i < size_z; i++) {
    sign = signs[coord_x][coord_y][i];
    signs[coord_x][coord_y][i] = deque.front();
    if (sign == deque.front()) {
      deque.pop_front();
    }
    if ((i + visibility_z) < size_z) {
      while (!deque.empty() &&
             (deque.back()[0] < signs[coord_x][coord_y][i + visibility_z][0])) {
        deque.pop_back();
      }
      deque.push_back(signs[coord_x][coord_y][i + visibility_z]);
    }
  }
}

void FindMaximumOnLines(
  int size_x, int size_y, int size_z,
  std::vector<std::vector<std::vector<std::vector<int>>>>& signs,
  int visibility_z) {
  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_y; j++) {
      MaximumOnLine(i, j, size_z, signs, visibility_z);
    }
  }
}

void MaximumOnColumns(
  int coord_x, int size_y, int coord_z,
  std::vector<std::vector<std::vector<std::vector<int>>>>& signs,
  int visibility_y) {
  std::deque<std::vector<int>> deque;
  std::vector<int> sign;
  for (int i = 0; i < visibility_y; i++) {
    while (!deque.empty() &&
           (deque.back()[0] < signs[coord_x][i][coord_z][0])) {
      deque.pop_back();
    }
    deque.push_back(signs[coord_x][i][coord_z]);
  }
  for (int i = 0; i < size_y; i++) {
    sign = signs[coord_x][i][coord_z];
    signs[coord_x][i][coord_z] = deque.front();
    if (sign == deque.front()) {
      deque.pop_front();
    }
    if ((i + visibility_y) < size_y) {
      while (!deque.empty() &&
             (deque.back()[0] < signs[coord_x][i + visibility_y][coord_z][0])) {
        deque.pop_back();
      }
      deque.push_back(signs[coord_x][i + visibility_y][coord_z]);
    }
  }
}

void FindMaximumOnColumns(
  int size_x, int size_y, int size_z,
  std::vector<std::vector<std::vector<std::vector<int>>>>& signs,
  int visibility_y) {
  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_z; j++) {
      MaximumOnColumns(i, size_y, j, signs, visibility_y);
    }
  }
}

void MaximumOnVerticals(
  int size_x, int coord_y, int coord_z,
  std::vector<std::vector<std::vector<std::vector<int>>>>& signs,
  int visibility_x) {
  std::deque<std::vector<int>> deque;
  std::vector<int> sign;
  for (int i = 0; i < visibility_x; i++) {
    while (!deque.empty() &&
           (deque.back()[0] < signs[i][coord_y][coord_z][0])) {
      deque.pop_back();
    }
    deque.push_back(signs[i][coord_y][coord_z]);
  }
  for (int i = 0; i < size_x; i++) {
    sign = signs[i][coord_y][coord_z];
    signs[i][coord_y][coord_z] = deque.front();
    if (sign == deque.front()) {
      deque.pop_front();
    }
    if ((i + visibility_x) < size_x) {
      while (!deque.empty() &&
             (deque.back()[0] < signs[i + visibility_x][coord_y][coord_z][0])) {
        deque.pop_back();
      }
      deque.push_back(signs[i + visibility_x][coord_y][coord_z]);
    }
  }
}

void FindMaximumOnVerticals(
  int size_x, int size_y, int size_z,
  std::vector<std::vector<std::vector<std::vector<int>>>>& signs,
  int visibility_x) {
  for (int i = 0; i < size_y; i++) {
    for (int j = 0; j < size_z; j++) {
      MaximumOnVerticals(size_x, i, j, signs, visibility_x);
    }
  }
}

void PreCalculation(
  int size_x, int size_y, int size_z,
  std::vector<std::vector<std::vector<std::vector<int>>>>& signs) {
  int xx;
  int yy;
  int zz;
  for (int i = size_x - 1; i >= 0; i--) {
    for (int j = size_y - 1; j >= 0; j--) {
      for (int k = size_z - 1; k >= 0; k--) {
        xx = signs[i][j][k][1];
        yy = signs[i][j][k][2];
        zz = signs[i][j][k][3];
        signs[i][j][k][1] = signs[xx][yy][zz][1];
        signs[i][j][k][2] = signs[xx][yy][zz][2];
        signs[i][j][k][3] = signs[xx][yy][zz][3];
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int size_x;
  int size_y;
  int size_z;
  std::cin >> size_x >> size_y >> size_z;
  int visibility_x;
  int visibility_y;
  int visibility_z;
  std::cin >> visibility_x >> visibility_y >> visibility_z;
  std::vector<std::vector<std::vector<std::vector<int>>>> signs(
    size_x,
    std::vector<std::vector<std::vector<int>>>(
      size_y, std::vector<std::vector<int>>(size_z, std::vector<int>(4))));
  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_y; j++) {
      for (int k = 0; k < size_z; k++) {
        std::cin >> signs[i][j][k][0];
        signs[i][j][k][1] = i;
        signs[i][j][k][2] = j;
        signs[i][j][k][3] = k;
      }
    }
  }
  FindMaximumOnLines(size_x, size_y, size_z, signs, visibility_z);
  FindMaximumOnColumns(size_x, size_y, size_z, signs, visibility_y);
  FindMaximumOnVerticals(size_x, size_y, size_z, signs, visibility_x);
  PreCalculation(size_x, size_y, size_z, signs);
  int number_of_requests;
  std::cin >> number_of_requests;
  int coordinate_x;
  int coordinate_y;
  int coordinate_z;
  for (int i = 0; i < number_of_requests; i++) {
    std::cin >> coordinate_x >> coordinate_y >> coordinate_z;
    for (int j = 1; j <= 3; j++) {
      std::cout << signs[coordinate_x][coordinate_y][coordinate_z][j] << " ";
    }
    std::cout << "\n";
  }
}