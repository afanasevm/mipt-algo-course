#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class BigInteger {
private:
  static const int cRank = 1000000000;
  std::vector<int> ranks_;
  bool is_positive_ = true;

  static const int cNine = 9;
  static const int cEight = 8;

  void DeleteZero();

  static BigInteger Abs(const BigInteger& big_integer);

  static BigInteger Sum(const BigInteger& first, const BigInteger& second);

  static BigInteger Difference(const BigInteger& first,
                               const BigInteger& second);

public:
  BigInteger() : BigInteger(0) {}

  BigInteger(const int cNumber) {
    is_positive_ = (cNumber >= 0);
    int num = cNumber;
    if (!is_positive_) {
      num = -num;
    }
    if (num < cRank) {
      ranks_.push_back(num);
    } else {
      ranks_.push_back(num % cRank);
      ranks_.push_back(num / cRank);
    }
  }

  BigInteger(const std::string cNumber) {
    is_positive_ = (cNumber[0] != '-');
    for (long long i = cNumber.size() - 1;
         i >= static_cast<long long>(!is_positive_); i -= cNine) {
      if (i > cEight) {
        ranks_.push_back(std::stoi(cNumber.substr(i - cEight, cNine)));
      } else {
        ranks_.push_back(std::stoi(
            cNumber.substr(static_cast<long long>(!is_positive_),
                           i + static_cast<long long>(is_positive_))));
      }
    }
    this->DeleteZero();
  }

  BigInteger(const BigInteger& big_integer)
      : ranks_(big_integer.ranks_), is_positive_(big_integer.is_positive_) {}

  void Swap(BigInteger& big_integer) {
    std::swap(ranks_, big_integer.ranks_);
    std::swap(is_positive_, big_integer.is_positive_);
  }

  BigInteger& operator=(BigInteger big_integer);

  BigInteger& operator+=(const BigInteger& big_integer);

  BigInteger& operator-=(const BigInteger& big_integer);

  BigInteger& operator*=(const BigInteger& big_integer);

  BigInteger& operator/=(const BigInteger& big_integer);

  BigInteger& operator%=(const BigInteger& big_integer);

  BigInteger operator-() const;

  BigInteger& operator++();

  BigInteger operator++(int);

  BigInteger& operator--();

  BigInteger operator--(int);

  std::string ToString() const;

  friend bool operator==(const BigInteger& first, const BigInteger& second);

  friend bool operator<(const BigInteger& first, const BigInteger& second);

  explicit operator bool() const;

  friend BigInteger operator*(const BigInteger& left, const BigInteger& right);

  friend BigInteger operator/(const BigInteger& left, const BigInteger& right);
};

bool operator==(const BigInteger& first, const BigInteger& second) {
  if ((first.is_positive_ != second.is_positive_) ||
      (first.ranks_.size() != second.ranks_.size())) {
    return false;
  }
  for (size_t i = 0; i < first.ranks_.size(); i++) {
    if (first.ranks_[i] != second.ranks_[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const BigInteger& first, const BigInteger& second) {
  return !(first == second);
}

bool operator<(const BigInteger& first, const BigInteger& second) {
  if (first.is_positive_ != second.is_positive_) {
    return static_cast<int>(first.is_positive_) <
           static_cast<int>(second.is_positive_);
  }
  if (first.ranks_.size() < second.ranks_.size()) {
    return first.is_positive_;
  }
  if (first.ranks_.size() > second.ranks_.size()) {
    return !first.is_positive_;
  }
  for (long long i = first.ranks_.size() - 1; i >= 0; i--) {
    if (first.ranks_[i] < second.ranks_[i]) {
      return first.is_positive_;
    }
    if (first.ranks_[i] > second.ranks_[i]) {
      return !first.is_positive_;
    }
  }
  return false;
}

bool operator>(const BigInteger& first, const BigInteger& second) {
  return (second < first);
}

bool operator<=(const BigInteger& first, const BigInteger& second) {
  return !(first > second);
}

bool operator>=(const BigInteger& first, const BigInteger& second) {
  return !(first < second);
}

BigInteger BigInteger::Abs(const BigInteger& big_integer) {
  BigInteger copy = big_integer;
  copy.is_positive_ = true;
  return copy;
}

BigInteger BigInteger::Sum(const BigInteger& first, const BigInteger& second) {
  BigInteger result;
  long long value;
  int transfer = 0;
  for (size_t i = 0;
       (i < std::max(first.ranks_.size(), second.ranks_.size())) ||
       (transfer != 0);
       i++) {
    if (i == result.ranks_.size()) {
      result.ranks_.push_back(0);
    }
    value = transfer;
    transfer = 0;
    if (i < first.ranks_.size()) {
      value += first.ranks_[i];
    }
    if (i < second.ranks_.size()) {
      value += second.ranks_[i];
    }
    if (value >= cRank) {
      transfer = 1;
      value -= cRank;
    }
    result.ranks_[i] = value;
  }
  return result;
}

BigInteger BigInteger::Difference(const BigInteger& first,
                                  const BigInteger& second) {
  BigInteger result = first;
  long long value;
  int transfer = 0;
  for (size_t i = 0; (i < second.ranks_.size()) || (transfer != 0); i++) {
    value = 1LL * result.ranks_[i] - transfer;
    transfer = 0;
    if (i < second.ranks_.size()) {
      value -= second.ranks_[i];
    }
    if (value < 0) {
      transfer = 1;
      value += cRank;
    }
    result.ranks_[i] = value;
  }
  return result;
}

BigInteger operator+(const BigInteger& left, const BigInteger& right) {
  BigInteger result = left;
  result += right;
  return result;
}

BigInteger operator-(const BigInteger& left, const BigInteger& right) {
  BigInteger result = left;
  result -= right;
  return result;
}

BigInteger operator*(const BigInteger& left, const BigInteger& right) {
  BigInteger result;
  result.is_positive_ = (left.is_positive_ == right.is_positive_);
  result.ranks_ = std::vector(left.ranks_.size() + right.ranks_.size(), 0);
  long long transfer;
  long long value;
  for (size_t i = 0; i < left.ranks_.size(); i++) {
    transfer = 0;
    for (size_t j = 0; (j < right.ranks_.size()) || (transfer != 0); j++) {
      value = transfer;
      if (j < right.ranks_.size()) {
        value += 1LL * left.ranks_[i] * right.ranks_[j] + result.ranks_[i + j];
      }
      transfer = value / BigInteger::cRank;
      result.ranks_[i + j] = value % BigInteger::cRank;
    }
  }
  result.DeleteZero();
  return result;
}

BigInteger operator/(const BigInteger& left, const BigInteger& right) {
  BigInteger result;
  result.is_positive_ = (left.is_positive_ == right.is_positive_);
  long long index = -1;
  bool flag = false;
  BigInteger divisible;
  divisible.ranks_.pop_back();
  for (long long i = left.ranks_.size() - 1; i >= 0; i--) {
    divisible.ranks_.insert(divisible.ranks_.begin(), left.ranks_[i]);
    divisible.DeleteZero();
    int total = 0;
    int left_border = 0;
    int right_border = BigInteger::cRank - 1;
    if (divisible > 0) {
      while (left_border <= right_border) {
        size_t middle = (left_border + right_border) / 2;
        BigInteger value = right * middle;
        value.is_positive_ = true;
        if (value <= divisible) {
          total = middle;
          left_border = middle + 1;
        } else {
          right_border = middle - 1;
        }
      }
    }
    if (index == -1 && total != 0) {
      result.ranks_ = std::vector(i + 1, 0);
      index = i;
      flag = true;
    }
    if (flag) {
      BigInteger value = right * total;
      value.is_positive_ = true;
      divisible -= value;
      result.ranks_[index--] = total;
    }
  }
  result.DeleteZero();
  return result;
}

BigInteger operator%(const BigInteger& left, const BigInteger& right) {
  BigInteger result;
  if (left < right) {
    result = left;
  } else if (left == right || right == 1) {
    result = 0;
  } else {
    result = left - (left / right) * right;
  }
  return result;
}

std::ostream& operator<<(std::ostream& cout, const BigInteger& big_integer) {
  cout << big_integer.ToString();
  return cout;
}

std::istream& operator>>(std::istream& cin, BigInteger& big_integer) {
  std::string string;
  cin >> string;
  big_integer = BigInteger(string);
  return cin;
}

void BigInteger::DeleteZero() {
  while (ranks_.size() > 1 && ranks_.back() == 0) {
    ranks_.pop_back();
  }
  if (ranks_.size() == 1 && ranks_[0] == 0) {
    is_positive_ = true;
  }
  if (ranks_.size() == 1 and ranks_[0] == 0) {
    is_positive_ = true;
  }
}

BigInteger& BigInteger::operator=(BigInteger big_integer) {
  Swap(big_integer);
  return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& big_integer) {
  bool sign = this->is_positive_;
  if (big_integer == 0) {
    return *this;
  }
  if (is_positive_ != big_integer.is_positive_) {
    if (Abs(*this) >= Abs(big_integer)) {
      *this = Difference(*this, big_integer);
    } else {
      sign = !sign;
      *this = Difference(big_integer, *this);
    }
  } else {
    *this = Sum(*this, big_integer);
  }
  this->is_positive_ = sign;
  this->DeleteZero();
  return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& big_integer) {
  bool sign = this->is_positive_;
  if (big_integer == 0) {
    return *this;
  }
  if (is_positive_ != big_integer.is_positive_) {
    *this = Sum(*this, big_integer);
  } else {
    if (Abs(*this) >= Abs(big_integer)) {
      *this = Difference(*this, big_integer);
    } else {
      sign = !sign;
      *this = Difference(big_integer, *this);
    }
  }
  this->is_positive_ = sign;
  this->DeleteZero();
  return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& big_integer) {
  *this = *this * big_integer;
  return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& big_integer) {
  *this = *this / big_integer;
  return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& big_integer) {
  *this = *this % big_integer;
  return *this;
}

BigInteger BigInteger::operator-() const {
  BigInteger big_integer = *this;
  if (big_integer != 0) {
    big_integer.is_positive_ = !is_positive_;
  }
  return big_integer;
}

BigInteger& BigInteger::operator++() { return *this += 1; }

BigInteger BigInteger::operator++(int) {
  *this += 1;
  return *this - 1;
}

BigInteger& BigInteger::operator--() { return *this -= 1; }

BigInteger BigInteger::operator--(int) {
  *this -= 1;
  return *this + 1;
}

std::string BigInteger::ToString() const {
  std::string string;
  std::string digit;
  if (!is_positive_) {
    string += '-';
  }
  for (long long i = ranks_.size() - 1; i >= 0; i--) {
    digit = std::to_string(ranks_[i]);
    if (i != static_cast<long long>(ranks_.size()) - 1) {
      string += std::string(cNine - digit.length(), '0');
    }
    string += digit;
  }
  return string;
}

BigInteger::operator bool() const { return (*this != 0); }

BigInteger operator""_bi(const char* string) { return BigInteger(string); }

struct Matrix {
  int size;
  std::vector<std::vector<long long>> data;

  Matrix(int size)
      : size(size),
        data(std::vector<std::vector<long long>>(
            size, std::vector<long long>(size, 0))) {}
};

Matrix MultiplyMatrix(int mod, Matrix& first, Matrix& second) {
  Matrix result(first.size);
  for (int i = 0; i < result.size; i++) {
    for (int j = 0; j < result.size; j++) {
      for (int k = 0; k < result.size; k++) {
        result.data[i][j] =
            (result.data[i][j] + first.data[i][k] * second.data[k][j]) % mod;
      }
    }
  }
  return result;
}

Matrix PowerMatrix(int mod, Matrix& matrix, BigInteger power) {
  if (power == 0) {
    Matrix result(matrix.size);
    for (int i = 0; i < matrix.size; i++) {
      result.data[i][i] = 1;
    }
    return result;
  }
  if (power % 2 == 1) {
    Matrix temp(PowerMatrix(mod, matrix, power - 1));
    return MultiplyMatrix(mod, matrix, temp);
  }
  Matrix temp(PowerMatrix(mod, matrix, power / 2));
  return MultiplyMatrix(mod, temp, temp);
}

bool CheckMask(int length_mask, int mask1, int mask2) {
  int sum;
  for (int i = 0; i < length_mask - 1; i++) {
    sum = static_cast<int>(mask1 >> i & 1);
    sum += static_cast<int>(mask1 >> (i + 1) & 1);
    sum += static_cast<int>(mask2 >> i & 1);
    sum += static_cast<int>(mask2 >> (i + 1) & 1);
    if (sum == 0 || sum == 4) {
      return false;
    }
  }
  return true;
}

int main() {
  BigInteger length;
  int height;
  int mod;
  std::cin >> length >> height >> mod;

  Matrix result(1 << height);
  for (int i = 0; i < 1 << height; i++) {
    for (int j = 0; j < 1 << height; j++) {
      result.data[i][j] = static_cast<long long>(CheckMask(height, i, j));
    }
  }

  result = PowerMatrix(mod, result, length - 1);
  int answer = 0;
  for (int i = 0; i < 1 << height; i++) {
    for (int j = 0; j < 1 << height; j++) {
      answer += result.data[i][j];
    }
  }

  std::cout << answer % mod;
}