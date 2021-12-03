#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void task1() {
  std::ifstream ifs{"input/3.txt"};
  std::string line;
  uint total_lines = 0;
  ifs >> line;
  std::vector<uint> bit_counts(line.length(), 0);

  do {
    total_lines++;
    for (int i = 0; i < line.length(); i++) {
      if (line[i] == '1') {
        bit_counts[i]++;
      }
    }
  } while (ifs >> line);

  uint gamma_rate = 0;
  for (int i = 0; i < bit_counts.size(); i++) {
    if (bit_counts[bit_counts.size() - 1 - i] > total_lines / 2) {
      gamma_rate += 1 << i;
    }
  }
  uint epsilon_rate = ~gamma_rate & ((1 << bit_counts.size()) - 1);

  std::cout << gamma_rate * epsilon_rate << std::endl;
}

void task2() {
  std::ifstream ifs{"input/3.txt"};
  std::vector<uint> oxygen_nums;
  std::vector<uint> co2_nums;
  std::string line;
  ifs >> line;
  auto line_length = line.length();
  std::vector<uint> oxygen_bit_counts(line_length, 0);
  std::vector<uint> co2_bit_counts(line_length, 0);

  do {
    uint num = std::stoi(line, NULL, 2);
    oxygen_nums.push_back(num);
    co2_nums.push_back(num);
  } while (ifs >> line);

  for (int i = 0; i < line_length; i++) {

    // Oxygen generator rating
    if (oxygen_nums.size() > 1) {
      for (auto num : oxygen_nums) {
        int shift = line_length - 1 - i;
        uint bit = (num & (1 << shift)) >> shift;
        oxygen_bit_counts[i] += bit;
        if (bit == 1) {
        } else {
        }
      }

      uint most_common;
      if (oxygen_bit_counts[i] >= (oxygen_nums.size()+1)/2) {
        most_common = 1;
      } else {
        most_common = 0;
      }


      for (int j = 0; j < oxygen_nums.size(); j++) {
        uint num = oxygen_nums[j];
        int shift = line_length - 1 - i;
        uint bit = (num & (1 << shift)) >> shift;
        if (bit != most_common) {
          oxygen_nums.erase(oxygen_nums.begin() + j);
          j--;
        }
      }
    }

    // CO2 scrubber rating
    if (co2_nums.size() > 1) {
      for (auto num : co2_nums) {
        int shift = line_length - 1 - i;
        uint bit = (num & (1 << shift)) >> shift;
        co2_bit_counts[i] += bit;
      }

      uint least_common;
      if (co2_bit_counts[i] >= (co2_nums.size()+1)/2) {
        least_common = 0;
      } else {
        least_common = 1;
      }


      for (int j = 0; j < co2_nums.size(); j++) {
        uint num = co2_nums[j];
        int shift = line_length - 1 - i;
        uint bit = (num & (1 << shift)) >> shift;
        if (bit != least_common) {
          co2_nums.erase(co2_nums.begin() + j);
          j--;
        }
      }
    }
  }

  auto oxygen = oxygen_nums[0];
  auto co2 = co2_nums[0];

  std::cout << oxygen*co2 << std::endl;
}

int main() {
  task1();
  task2();
}