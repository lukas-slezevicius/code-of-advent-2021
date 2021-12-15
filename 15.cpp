#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

vector<pair<int, int>> get_neighbors(int i, int j, int rows, int cols) {
  vector<pair<int, int>> v;
  if (i > 0) {
    v.push_back(make_pair(i - 1, j));
  }
  if (j < cols - 1) {
    v.push_back(make_pair(i, j + 1));
  }
  if (i < rows - 1) {
    v.push_back(make_pair(i + 1, j));
  }
  if (j > 0) {
    v.push_back(make_pair(i, j - 1));
  }
  return v;
}

struct Elem {
  pair<int, int> val;
  double dist;
  bool operator<(const Elem &e) const {
    return dist > e.dist;
  }
};

optional<int> shortest_distance(const vector<vector<int>> &grid) {
  const int rows = grid.size(), cols = grid.front().size();

  priority_queue<Elem> q;
  vector<vector<double>> dist;
  vector<vector<optional<pair<int, int>>>> prev;
  set<pair<int, int>> visited;
  for (int i = 0; i < rows; i++) {
    dist.push_back(vector<double>());
    prev.push_back(vector<optional<pair<int, int>>>());
    for (int j = 0; j < cols; j++) {
      dist.back().push_back(numeric_limits<double>::infinity());
      prev.back().push_back(optional<pair<int, int>>());
      q.push(Elem({make_pair(i, j), dist[i][j]}));
    }
  }
  dist[0][0] = 0.0;
  q.push(Elem({make_pair(0, 0), dist[0][0]}));

  while (!q.empty()) {
    auto [i, j] = q.top().val;
    q.pop();
    if (visited.find(make_pair(i, j)) != visited.end()) {
      continue;
    }
    visited.insert(make_pair(i, j));

    if (i == rows - 1 && j == cols - 1) {
      return make_optional(dist[rows - 1][cols - 1]);
    }

    for (auto [k, l] : get_neighbors(i, j, rows, cols)) {
      auto alt = dist[i][j] + grid[k][l];
      if (alt < dist[k][l]) {
        dist[k][l] = alt;
        prev[k][l].emplace(make_pair(i, j));
        q.push(Elem({make_pair(k, l), dist[k][l]}));
      }
    }
  }

  return {};
}

int main() {
  ifstream ifs("input/15.txt");
  string line;
  vector<vector<int>> grid1;

  while (getline(ifs, line)) {
    grid1.push_back(vector<int>());
    istringstream ss(line);
    char c;
    while (ss >> c) {
      grid1.back().push_back(c - '0');
    }
  }

  auto task1 = shortest_distance(grid1);
  if (task1.has_value()) {
    cout << task1.value() << endl;
  } else {
    cout << "No solution found for task 1\n";
  }

  // Build larger grid and compute it
  vector<vector<int>> grid2;
  // Expand the grid horizontaly
  for (int i = 0; i < grid1.size(); i++) {
    grid2.push_back(vector<int>());
    for (int x = 0; x < 5; x++) {
      for (int j = 0; j < grid1.front().size(); j++) {
        int n = grid1[i][j] + x;
        if (n > 9) {
          n -= 9;
        }
        grid2.back().push_back(n);
      }
    }
  }
  // Expand the grid vertically
  for (int x = 1; x < 5; x++) {
    for (int i = 0; i < grid1.size(); i++) {
      grid2.push_back(vector<int>());
      for (int j = 0; j < grid2.front().size(); j++) {
        int n = grid2[i][j] + x;
        if (n > 9) {
          n -= 9;
        }
        grid2.back().push_back(n);
      }
    }
  }

  auto task2 = shortest_distance(grid2);
  if (task2.has_value()) {
    cout << task2.value() << endl;
  } else {
    cout << "No solution found for task 2\n";
  }
}