#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int imin = numeric_limits<int>::min();
const int imax = numeric_limits<int>::max();

int get_index(const vector<vector<bool>> &bright_pixels, const bool outer_is_bright, int i, int j) {
  const auto rows = bright_pixels.size();
  const auto cols = bright_pixels.front().size();
  string bit_str = "";

  vector<pair<int, int>> coords({{i - 1, j - 1},
                                 {i - 1, j},
                                 {i - 1, j + 1},
                                 {i, j - 1},
                                 {i, j},
                                 {i, j + 1},
                                 {i + 1, j - 1},
                                 {i + 1, j},
                                 {i + 1, j + 1}});

  for (auto [k, l] : coords) {
    if (k < 0 || k >= rows || l < 0 || l >= cols) {
      bit_str += outer_is_bright ? "1" : "0";
    } else {
      bit_str += bright_pixels.at(k).at(l) ? "1" : "0";
    }
  }

  return stoi(bit_str, 0, 2);
}

int main() {
  ifstream ifs("input/20.txt");
  string line;

  getline(ifs, line);
  vector<bool> mask;
  for (auto c : line) {
    mask.push_back(c == '#');
  }

  ifs.ignore(1);

  vector<vector<bool>> inner_grid;
  while (getline(ifs, line)) {
    inner_grid.push_back(vector<bool>());
    for (auto c : line) {
      inner_grid.back().push_back(c == '#');
    }
  }

  bool outer_is_bright = false;

  const unsigned steps = 50;
  for (unsigned step = 0; step < steps; step++) {
    const auto cols_before_padding = inner_grid.front().size();
    inner_grid.insert(inner_grid.begin(), vector<bool>());
    inner_grid.push_back(vector<bool>());
    for (unsigned j = 0; j < cols_before_padding; j++) {
      inner_grid.front().push_back(outer_is_bright);
      inner_grid.back().push_back(outer_is_bright);
    }
    for (unsigned i = 0; i < inner_grid.size(); i++) {
      inner_grid.at(i).insert(inner_grid.at(i).begin(), outer_is_bright);
      inner_grid.at(i).push_back(outer_is_bright);
    }
    const auto original_inner_grid = inner_grid;
    for (unsigned i = 0; i < inner_grid.size(); i++) {
      for (unsigned j = 0; j < inner_grid.front().size(); j++) {
        const auto idx = get_index(original_inner_grid, outer_is_bright, i, j);
        if (mask[idx]) {
          inner_grid.at(i).at(j) = true;
        } else {
          inner_grid.at(i).at(j) = false;
        }
      }
    }
    if (outer_is_bright && !mask.back()) {
      outer_is_bright = false;
    } else if (!outer_is_bright && mask.front()) {
      outer_is_bright = true;
    }
  }

  unsigned bright_pixel_count = 0;
  for (const auto &row : inner_grid) {
    for (const auto &bright : row) {
      if (bright) {
        bright_pixel_count += 1;
      }
    }
  }

  cout << bright_pixel_count << endl;
}