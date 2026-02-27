#include <iostream>
#include <vector>

const int cMod = 1e9 + 7;

bool CheckMaskWithTable(size_t length, std::vector<char>& line, int mask) {
  for (size_t i = 0; i < length; i++) {
    if ((line[i] == '+') && (((mask >> i) & 1) != 1)) {
      return false;
    }
    if ((line[i] == '-') && (((mask >> i) & 1) != 0)) {
      return false;
    }
  }
  return true;
}

std::pair<int, int> FindMasks(size_t length, int mask) {
  std::pair<int, int> result;
  result.first = ((1 << length) - 1) ^ mask;

  int copy = mask;
  for (size_t i = 0; i < length - 1; i++) {
    if ((copy & 1) == ((copy >> 1) & 1)) {
      result.second = -1;
      return result;
    }
    copy >>= 1;
  }
  result.second = mask;
  return result;
}

int main() {
  size_t length;
  size_t height;
  std::cin >> length >> height;

  std::vector<std::vector<char>> table(height, std::vector<char>(length));
  for (size_t i = 0; i < length; i++) {
    for (size_t j = 0; j < height; j++) {
      std::cin >> table[j][i];
    }
  }

  std::vector<int> dp_prev(1 << length, 0);
  std::vector<int> dp_next(1 << length, 0);

  for (int mask = 0; mask < (1 << length); mask++) {
    if (CheckMaskWithTable(length, table[0], mask)) {
      dp_prev[mask] = 1;
    }
  }

  for (size_t i = 1; i < height; i++) {
    for (int mask = 0; mask < (1 << length); mask++) {
      if (CheckMaskWithTable(length, table[i], mask)) {
        std::pair<int, int> masks(FindMasks(length, mask));
        if (CheckMaskWithTable(length, table[i - 1], masks.first)) {
          dp_next[mask] = (dp_next[mask] + dp_prev[masks.first]) % cMod;
        }
        if ((masks.second != -1) &&
            CheckMaskWithTable(length, table[i - 1], masks.second)) {
          dp_next[mask] = (dp_next[mask] + dp_prev[masks.second]) % cMod;
        }
      }
    }
    std::swap(dp_prev, dp_next);
    for (int mask = 0; mask < (1 << length); mask++) {
      dp_next[mask] = 0;
    }
  }

  int answer = 0;
  for (int mask = 0; mask < (1 << length); mask++) {
    answer = (answer + dp_prev[mask]) % cMod;
  }
  std::cout << answer;
}