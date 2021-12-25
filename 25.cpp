#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

enum class cell { east, south, empty };

int main() {
  ifstream ifs("input/25.txt");
  string line;
  vector<vector<cell>> grid;
  while (getline(ifs, line)) {
    grid.push_back(vector<cell>());
    for (const auto &c : line) {
      switch (c) {
      case '>':
        grid.back().push_back(cell::east);
        break;
      case 'v':
        grid.back().push_back(cell::south);
        break;
      case '.':
        grid.back().push_back(cell::empty);
        break;
      default:
        throw invalid_argument("Unrecognized character");
      }
    }
    if (grid.front().size() != grid.back().size()) {
      throw invalid_argument("Row sizes not consistent");
    }
  }

  const size_t rows = grid.size(), cols = grid.front().size();

  uint step = 0;
  while (true) {
    step++;
    bool changed = false;
    auto old_grid = grid;
    // move the east ones
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        if (old_grid.at(i).at(j) == cell::east) {
          if (old_grid.at(i).at((j + 1) % cols) == cell::empty) {
            changed = true;
            grid.at(i).at(j) = cell::empty;
            grid.at(i).at((j + 1) % cols) = cell::east;
          }
        }
      }
    }
    old_grid = grid;
    // move the south ones
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        if (old_grid.at(i).at(j) == cell::south) {
          if (old_grid.at((i + 1) % rows).at(j) == cell::empty) {
            changed = true;
            grid.at(i).at(j) = cell::empty;
            grid.at((i + 1) % rows).at(j) = cell::south;
          }
        }
      }
    }
    if (!changed) {
      break;
    }
  }

  cout << step << endl;
}