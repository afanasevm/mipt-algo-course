#include <iostream>
#include <vector>

const int cMax = 1000000000;

void CountPrefixSum(int quantity, std::vector<int>& array,
                    std::vector<int>& result) {
  result[0] = 0;
  for (int i = 1; i < quantity + 1; i++) {
    result[i] = result[i - 1] + array[i - 1];
  }
}

void CountSumDistance(int quantity, std::vector<int>& coordinates,
                      std::vector<int>& prefix_sum,
                      std::vector<std::vector<int>>& distance) {
  distance[0][0] = 0;
  distance[0][quantity + 1] = cMax;
  for (int i = 1; i < quantity + 1; i++) {
    distance[0][i] = i * coordinates[i - 1] - prefix_sum[i];
  }

  distance[quantity + 1][quantity + 1] = 0;
  for (int i = 1; i < quantity + 1; i++) {
    distance[i][quantity + 1] = prefix_sum[quantity] - prefix_sum[i] -
                                (quantity - i) * coordinates[i - 1];
  }

  for (int i = 1; i < quantity + 1; i++) {
    for (int j = i + 1; j < quantity + 1; j++) {
      auto elem =
          std::lower_bound(coordinates.begin(), coordinates.end(),
                           (coordinates[i - 1] + coordinates[j - 1] + 1) / 2);
      int index_in_coord = elem - coordinates.begin() + 1;
      distance[i][j] = coordinates[j - 1] * (j - index_in_coord + 1) -
                       prefix_sum[j] + 2 * prefix_sum[index_in_coord - 1] -
                       prefix_sum[i - 1] -
                       coordinates[i - 1] * (index_in_coord - i);
    }
  }
}

int main() {
  int quantity_houses;
  int quantity_wells;
  std::cin >> quantity_houses >> quantity_wells;

  std::vector<int> houses(quantity_houses);
  for (int i = 0; i < quantity_houses; i++) {
    std::cin >> houses[i];
  }

  std::vector<int> prefix_sum(quantity_houses + 1);
  std::vector<std::vector<int>> distance(quantity_houses + 2,
                                         std::vector<int>(quantity_houses + 2));
  CountPrefixSum(quantity_houses, houses, prefix_sum);
  CountSumDistance(quantity_houses, houses, prefix_sum, distance);

  std::vector<std::vector<int>> dp(quantity_houses + 1,
                                   std::vector<int>(quantity_wells + 1, cMax));
  std::vector<std::vector<int>> prev(quantity_houses + 1,
                                     std::vector<int>(quantity_wells + 1));
  for (int j = 0; j < quantity_wells + 1; j++) {
    dp[0][j] = 0;
  }
  for (int i = 0; i < quantity_houses + 1; i++) {
    dp[i][0] = 0;
    dp[i][1] = distance[0][i];
    if (quantity_wells == 1) {
      dp[i][1] += distance[i][quantity_houses + 1];
    }
  }

  for (int j = 2; j < quantity_wells + 1; j++) {
    for (int i = j; i < quantity_houses - (quantity_wells - j) + 1; i++) {
      for (int k = j - 1; k < i; k++) {
        int temp_distance = dp[k][j - 1] + distance[k][i];
        if (j == quantity_wells) {
          temp_distance += distance[i][quantity_houses + 1];
        }
        if (temp_distance <= dp[i][j]) {
          dp[i][j] = temp_distance;
          prev[i][j] = k;
        }
      }
    }
  }

  int answer = cMax;
  int answer_index = -1;
  for (int i = quantity_wells; i < quantity_houses + 1; i++) {
    if (dp[i][quantity_wells] < answer) {
      answer = dp[i][quantity_wells];
      answer_index = i;
    }
  }

  std::vector<int> result(quantity_wells);
  for (int i = quantity_wells; i > 0; i--) {
    result[i - 1] = houses[answer_index - 1];
    answer_index = prev[answer_index][i];
  }

  std::cout << answer << "\n";
  for (int i = 0; i < quantity_wells; i++) {
    std::cout << result[i] << " ";
  }
}