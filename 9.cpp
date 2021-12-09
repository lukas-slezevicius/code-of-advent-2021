#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> surrounding_points(int i, int j, int row_count,
                                          int column_count) {
  vector<pair<int, int>> v;
  if (i - 1 >= 0) {
    v.push_back(make_pair(i - 1, j));
  }
  if (j + 1 < column_count) {
    v.push_back(make_pair(i, j + 1));
  }
  if (i + 1 < row_count) {
    v.push_back(make_pair(i + 1, j));
  }
  if (j - 1 >= 0) {
    v.push_back(make_pair(i, j - 1));
  }
  return v;
}

int main() {
  vector<vector<uint>> height_map;
  string line;
  ifstream ifs("input/9.txt");
  while (getline(ifs, line)) {
    height_map.push_back(vector<uint>());
    for (auto c : line) {
      auto d = static_cast<uint>(c - '0');
      height_map.back().push_back(d);
    }
  }

  int row_count = height_map.size();
  int column_count = height_map.at(0).size();
  int risk_sum = 0;
  vector<pair<int, int>> low_points;
  for (int i = 0; i < row_count; i++) {
    for (int j = 0; j < column_count; j++) {
      int current_height = height_map.at(i).at(j);
      bool is_low_point = true;
      for (auto [k, l] : surrounding_points(i, j, row_count, column_count)) {
        if (height_map.at(k).at(l) <= current_height) {
          is_low_point = false;
          break;
        }
      }
      if (is_low_point) {
        risk_sum += 1 + current_height;
        low_points.push_back(make_pair(i, j));
      }
    }
  }

  cout << risk_sum << endl;

  vector<int> largest_basin_sizes(3, 0);
  for (auto low_point : low_points) {
    set<pair<int, int>> visited_points;
    queue<pair<int, int>> q;
    q.push(low_point);
    visited_points.insert(low_point);
    int basin_size = 1;
    while (!q.empty()) {
      auto [i, j] = q.front();
      q.pop();
      for (auto point : surrounding_points(i, j, row_count, column_count)) {
        auto [k, l] = point;
        if (height_map.at(k).at(l) != 9) {
          if (visited_points.find(point) == visited_points.end()) {
            basin_size++;
            q.push(point);
            visited_points.insert(point);
          }
        }
      }
    }
    if (largest_basin_sizes[0] < basin_size) {
      largest_basin_sizes[2] = largest_basin_sizes[1];
      largest_basin_sizes[1] = largest_basin_sizes[0];
      largest_basin_sizes[0] = basin_size;
    } else if (largest_basin_sizes[1] < basin_size) {
      largest_basin_sizes[2] = largest_basin_sizes[1];
      largest_basin_sizes[1] = basin_size;
    } else if (largest_basin_sizes[2] < basin_size) {
      largest_basin_sizes[2] = basin_size;
    }
  }

  int basin_size_prod = 1;
  for (auto basin_size : largest_basin_sizes) {
    basin_size_prod *= basin_size;
  }

  cout << basin_size_prod << endl;
}