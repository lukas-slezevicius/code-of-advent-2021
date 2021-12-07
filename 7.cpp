#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <vector>
#include <cmath>

void task1(const std::vector<int> &input) {
  std::map<int, int> pos_counts;
  int min_pos = std::numeric_limits<int>::max(), max_pos = 0;
  int total_pos_left = 0, total_pos_right = 0, fuel_used = 0;
  for (auto n : input) {
    if (n > 0) {
      total_pos_right++;
      fuel_used += n;
    }
    if (n < min_pos) {
      min_pos = n;
    }
    if (n > max_pos) {
      max_pos = n;
    }
    if (pos_counts.find(n) == pos_counts.end()) {
      pos_counts[n] = 0;
    }
    pos_counts[n]++;
  }

  int min_fuel_used = fuel_used;
  for (int pos = min_pos + 1; pos <= max_pos; pos++) {
    if (pos_counts.find(pos - 1) != pos_counts.end()) {
      total_pos_left += pos_counts.at(pos - 1);
    }
    int count_at_pos = 0;
    if (pos_counts.find(pos) != pos_counts.end()) {
      count_at_pos += pos_counts.at(pos);
      total_pos_right -= pos_counts.at(pos);
    }
    fuel_used += total_pos_left - total_pos_right - count_at_pos;
    if (fuel_used < min_fuel_used) {
      min_fuel_used = fuel_used;
    }
  }

  std::cout << min_fuel_used << std::endl;
}

void task2(const std::vector<int> &input) {
  int min_pos = std::numeric_limits<int>::max(), max_pos = 0;
  for (auto n : input) {
    if (n < min_pos) {
      min_pos = n;
    }
    if (n > max_pos) {
      max_pos = n;
    }
  }

  int min_fuel_used = std::numeric_limits<int>::max();
  for (int pos = min_pos; pos <= max_pos; pos++) {
    int fuel_used = 0;
    for (auto n : input) {
      int diff = std::abs(pos - n);
      fuel_used += ((diff + 1)*diff)/2;
    }
    if (fuel_used < min_fuel_used) {
      min_fuel_used = fuel_used;
    }
  }

  std::cout << min_fuel_used << std::endl;
}

int main() {
  std::ifstream ifs("input/7.txt");
  std::string s;
  std::vector<int> input;
  while (std::getline(ifs, s, ',')) {
    int n = std::stoi(s);
    input.push_back(n);
  }

  task1(input);
  task2(input);
}