#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void fold_up(vector<vector<bool>> &grid, int fold_y) {
  int rows = grid.size(), cols = grid.front().size();
  int bottom_height = rows - fold_y - 1;
  for (int y = 0; y < bottom_height; y++) {
    for (int x = 0; x < cols; x++) {
      auto t = grid.at(fold_y - bottom_height + y).at(x);
      auto b = grid.at(rows - y - 1).at(x);
      grid.at(fold_y - bottom_height + y).at(x) = t || b;
    }
  }
  grid.erase(grid.end() - bottom_height - 1, grid.end());
}

void fold_left(vector<vector<bool>> &grid, int fold_x) {
  int rows = grid.size(), cols = grid.front().size();
  int right_width = cols - fold_x - 1;
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < right_width; x++) {
      auto l = grid.at(y).at(fold_x - right_width + x);
      auto r = grid.at(y).at(cols - x - 1);
      grid.at(y).at(fold_x - right_width + x) = l || r;
    }
    grid.at(y).erase(grid.at(y).end() - right_width - 1, grid.at(y).end());
  }
}

int main() {
  ifstream ifs("input/13.txt");
  string line;

  vector<pair<int, int>> dots;
  int max_x = 0, max_y = 0;
  while (getline(ifs, line) && line != "") {
    pair<int, int> dot;
    istringstream ss(line);
    ss >> dot.first;
    ss.ignore(1);
    ss >> dot.second;
    dots.push_back(dot);
    if (dot.first > max_x) {
      max_x = dot.first;
    }
    if (dot.second > max_y) {
      max_y = dot.second;
    }
  }

  vector<pair<char, int>> folds;
  while (getline(ifs, line)) {
    pair<char, int> fold;
    istringstream ss(line);
    ss.ignore(11);
    ss >> fold.first;
    ss.ignore(1);
    ss >> fold.second;
    folds.push_back(fold);
  }

  vector<vector<bool>> grid;
  for (int y = 0; y < max_y + 1; y++) {
    grid.push_back(vector<bool>(max_x + 1, false));
  }
  for (auto [x, y] : dots) {
    grid[y][x] = true;
  }

  bool first_fold = true;
  for (auto [dir, n] : folds) {
    if (dir == 'y') {
      fold_up(grid, n);
    } else {
      fold_left(grid, n);
    }

    if (first_fold) {
      int total = 0;
      for (const auto &row : grid) {
        for (const auto &b : row) {
          if (b) {
            total++;
          }
        }
      }
      cout << total << endl;
      first_fold = false;
    }
  }

  for (const auto &row : grid) {
    for (const auto &b : row) {
      if (b) {
        cout << "#";
      } else {
        cout << ".";
      }
    }
    cout << endl;
  }
}