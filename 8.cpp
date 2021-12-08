#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

void task1(const std::vector<std::vector<std::string>> &output_digits) {
  int count = 0;
  for (const auto &row : output_digits) {
    for (const auto &signals : row) {
      auto l = signals.length();
      if (l == 2 || l == 4 || l == 3 || l == 7) {
        count++;
      }
    }
  }

  std::cout << count << std::endl;
}

bool assignment_done(const std::vector<std::set<char>> &pos_assig) {
  for (const auto &assig : pos_assig) {
    if (assig.size() > 1) {
      return false;
    }
  }
  return true;
}

std::vector<char>
find_segment_assignments(const std::vector<std::string> &signal_seq) {
  const std::set<char> all_chars = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  std::vector<std::set<char>> pos_assig(7, all_chars); // Possible assignments
  while (!assignment_done(pos_assig)) {
    for (const auto &signals : signal_seq) {
      std::set<int> removes;
      std::set<int> simplifications;
      if (signals.length() == 2) {
        // 1
        removes.insert({0, 1, 3, 4, 6});
        simplifications.insert({2, 5});
      } else if (signals.length() == 3) {
        // 7
        removes.insert({1, 3, 4, 6});
        simplifications.insert({0, 2, 5});
      } else if (signals.length() == 4) {
        // 4
        removes.insert({0, 4, 6});
        simplifications.insert({1, 2, 3, 5});
      } else if (signals.length() == 5 || signals.length() == 6) {
        auto pos_assig_copy = pos_assig;
        std::set<char> signal_set(signals.begin(), signals.end());
        for (auto &assig : pos_assig_copy) {
          std::set<char> instersect;
          std::set_intersection(assig.begin(), assig.end(), signal_set.begin(),
                                signal_set.end(),
                                std::inserter(instersect, instersect.begin()));
          assig = instersect;
        }
        if (pos_assig_copy.at(1).size() == 0 &&
            pos_assig_copy.at(5).size() == 0) {
          // 2
          removes.insert({1, 5});
          simplifications.insert({0, 2, 3, 4, 6});
        } else if (pos_assig_copy.at(1).size() == 0 &&
                   pos_assig_copy.at(4).size() == 0) {
          // 3
          removes.insert({1, 4});
          simplifications.insert({0, 2, 3, 5, 6});
        } else if (pos_assig_copy.at(2).size() == 0 &&
                   pos_assig_copy.at(4).size() == 0) {
          // 5
          removes.insert({2, 4});
          simplifications.insert({0, 1, 3, 5, 6});
        } else if (pos_assig_copy.at(3).size() == 0) {
          // 0
          removes.insert({3});
          simplifications.insert({0, 1, 2, 4, 5, 6});
        } else if (pos_assig_copy.at(2).size() == 0) {
          // 6
          removes.insert({2});
          simplifications.insert({0, 1, 3, 4, 5, 6});
        } else if (pos_assig_copy.at(4).size() == 0) {
          // 9
          removes.insert({4});
          simplifications.insert({0, 1, 2, 3, 5, 6});
        }
      } else if (signals.length() == 7) {
        // 8
        // has no information that would be useful
      } else {
        throw std::runtime_error("Unexpected segment count");
      }
      for (int idx : removes) {
        for (char signal : signals) {
          pos_assig.at(idx).erase(signal);
        }
      }
      for (int idx : simplifications) {
        std::set<char> intersect;
        std::set<char> signal_set(signals.begin(), signals.end());
        std::set_intersection(pos_assig.at(idx).begin(),
                              pos_assig.at(idx).end(), signal_set.begin(),
                              signal_set.end(),
                              std::inserter(intersect, intersect.begin()));
        pos_assig.at(idx) = intersect;
      }
    }
  }

  std::vector<char> output;
  for (const auto &s : pos_assig) {
    output.push_back(*s.begin());
  }
  return output;
}

void task2(const std::vector<std::vector<std::string>> &signal_patterns,
           const std::vector<std::vector<std::string>> &output_digits) {
  int sum = 0;
  for (int i = 0; i < signal_patterns.size(); i++) {
    const auto &signal_seq = signal_patterns.at(i);
    const auto &output_seq = output_digits.at(i);
    const auto segment_assignments = find_segment_assignments(signal_seq);
    for (const auto &c : segment_assignments) {
      std::cout << c << std::endl;
    }
  }
}

int main() {
  std::ifstream ifs("input/test.txt");
  std::vector<std::vector<std::string>> signal_patterns, output_digits;
  std::string line;
  while (getline(ifs, line)) {
    signal_patterns.push_back(std::vector<std::string>());
    output_digits.push_back(std::vector<std::string>());
    std::istringstream line_iss(line);
    std::string s;
    getline(line_iss, s, '|');
    std::istringstream signal_pattern_iss(s);
    while (signal_pattern_iss >> s) {
      signal_patterns.back().push_back(s);
    }
    while (line_iss >> s) {
      output_digits.back().push_back(s);
    }
  }

  task1(output_digits);
  task2(signal_patterns, output_digits);
}