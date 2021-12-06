#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using ullong = unsigned long long;

ullong count_fishes(const std::vector<int> &initial_state, int total_days) {
  std::vector<ullong> prev_state(9, 0), curr_state(9, 0);
  for (const auto &cycle_age : initial_state) {
    if (cycle_age < 0 || cycle_age > 8) {
      throw std::invalid_argument("Cycle age out of cycle");
    }
    curr_state[cycle_age]++;
  }

  for (int day = 0; day < total_days; day++) {
    for (int i = 0; i < curr_state.size(); i++) {
      prev_state[i] = curr_state[i];
      curr_state[i] = 0;
    }
    curr_state[6] += prev_state[0];
    curr_state[8] += prev_state[0];
    for (int i = 1; i < curr_state.size(); i++) {
      curr_state[i - 1] += prev_state[i];
    }
  }

  ullong sum = 0;
  for (const auto &n : curr_state) {
    sum += n;
  }

  return sum;
}

int main(int argv, char **argc) {
  if (argv != 3) {
    std::cerr << "Expected 2 arguments" << std::endl;
    return 1;
  }
  std::string arg1(argc[1]), arg2(argc[2]), s;
  std::ifstream ifs(arg1);
  std::vector<int> initial_state;
  while (std::getline(ifs, s, ',')) {
    initial_state.push_back(std::stoi(s));
  }
  int total_days = std::stoi(arg2);

  auto c = count_fishes(initial_state, total_days);

  std::cout << c << std::endl;

  return 0;
}
