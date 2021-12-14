#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <limits>

using namespace std;

const int IMAX = std::numeric_limits<int>::max();
const long long LMAX = std::numeric_limits<long long>::max();

void task1(string t, const map<string, char> &rules) {
  map<char, int> counter;
  for (auto [s, c] : rules) {
    counter[c] = 0;
  }

  for (char c : t) {
    counter[c]++;
  }

  const int steps = 10;
  for (int step = 0; step < steps; step++) {
    string s;
    for (int i = 0; i < t.length() - 1; i++) {
      auto insertion = rules.at(t.substr(i, 2));
      s += t[i];
      s += insertion;
      counter[insertion]++;
    }
    s += t[t.length() - 1];
    t = s;
  }

  int min_count = IMAX, max_count = 0;
  for (auto [c, count] : counter) {
    if (count < min_count) {
      min_count = count;
    }
    if (count > max_count) {
      max_count = count;
    }
  }
  cout << max_count - min_count << endl;
}

void task2(const string &t, const map<string, char> &rules) {
  char last_char = t.at(t.length() - 1);
  map<string, unsigned long long> pair_counts;

  for (auto [s, c] : rules) {
    pair_counts[s] = 0;
  }

  for (int i = 0; i < t.length() - 1; i++) {
    pair_counts.at(t.substr(i, 2)) += 1;
  }

  const int steps = 40;
  for (int step = 0; step < steps; step++) {
    map<string, long long> pair_count_changes;
    for (auto [pair, count] : pair_counts) {
      pair_count_changes[pair] = 0;
    }
    for (auto [pair, count] : pair_counts) {
      if (count > 0) {
        char lc = pair.at(0), c = rules.at(pair), rc = pair.at(1);
        string lpair({lc, c}), rpair({c, rc});
        pair_count_changes[pair] -= count;
        pair_count_changes.at(lpair) += count;
        pair_count_changes.at(rpair) += count;
      }
    }
    for (auto [pair, change] : pair_count_changes) {
      pair_counts[pair] += change;
    }
  }

  map<char, unsigned long long> char_counts;
  for (auto [pair, count] : pair_counts) {
    char c = pair.at(0);
    if (char_counts.find(c) == char_counts.end()) {
      char_counts[c] = 0;
    }
    char_counts.at(c) += count;
  }
  // Last char is never included as a first char of some pair
  char_counts[last_char]++;

  unsigned long long min_count = LMAX, max_count = 0;
  for (auto [c, count] : char_counts) {
    if (count < min_count) {
      min_count = count;
    }
    if (count > max_count) {
      max_count = count;
    }
  }
  cout << max_count - min_count << endl;
}

int main() {
  ifstream ifs("input/14.txt");
  string t, line;
  getline(ifs, t);
  ifs.ignore(1);
  map<string, char> rules;
  while (getline(ifs, line)) {
    string key = line.substr(0, 2);
    char value = line.at(6);
    rules.emplace(key, value);
  }

  task1(t, rules);
  task2(t, rules);
}
