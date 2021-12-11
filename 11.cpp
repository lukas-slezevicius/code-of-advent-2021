#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> surrounding_cells(int i, int j, int rows, int cols) {
  vector<pair<int, int>> v;
  if (i - 1 >= 0) {
    v.push_back(make_pair(i - 1, j));
  }
  if (i - 1 >= 0 && j + 1 < cols) {
    v.push_back(make_pair(i - 1, j + 1));
  }
  if (j + 1 < cols) {
    v.push_back(make_pair(i, j + 1));
  }
  if (i + 1 < rows && j + 1 < cols) {
    v.push_back(make_pair(i + 1, j + 1));
  }
  if (i + 1 < rows) {
    v.push_back(make_pair(i + 1, j));
  }
  if (i + 1 < rows && j - 1 >= 0) {
    v.push_back(make_pair(i + 1, j - 1));
  }
  if (j - 1 >= 0) {
    v.push_back(make_pair(i, j - 1));
  }
  if (i - 1 >= 0 && j - 1 >= 0) {
    v.push_back(make_pair(i - 1, j - 1));
  }
  return v;
}

int main() {
  ifstream ifs("input/11.txt");
  vector<vector<int>> grid;
  string line;
  while (getline(ifs, line)) {
    stringstream ss(line);
    grid.push_back(vector<int>());
    char c;
    while (ss >> c) {
      auto n = static_cast<int>(c - '0');
      grid.back().push_back(n);
    }
  }

  //int steps = 100, flashed_count = 0;
  int rows = grid.size(), cols = grid.front().size();

  //for (int step = 0; step < steps; step++) {
  for (int step = 0;; step++) {
    for (auto &row : grid) {
      for (auto &n : row) {
        n++;
      }
    }
    set<pair<int, int>> flashed_set;
    while (true) {
      bool has_changed = false;
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          auto n = grid.at(i).at(j);
          if (n > 9 && flashed_set.find(make_pair(i, j)) == flashed_set.end()) {
            for (auto [k, l] : surrounding_cells(i, j, rows, cols)) {
              grid.at(k).at(l)++;
            }
            flashed_set.insert(make_pair(i, j));
            has_changed = true;
          }
        }
      }

      if (!has_changed) {
        //flashed_count += flashed_set.size();
        if (flashed_set.size() == rows*cols) {
          cout << step + 1 << endl;
          return 0;
        }
        for (auto [i, j] : flashed_set) {
          grid.at(i).at(j) = 0;
        }
        break;
      }
    }
  }

  //cout << flashed_count << endl;
}
