#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

bool is_upper_string(const string &word) {
  for (auto &c : word) {
    if (!isupper(static_cast<unsigned char>(c))) {
      return false;
    }
  }
  return true;
}

int count_paths1(const string &source, const string &dest,
                 const map<string, set<string>> &graph, set<string> visited) {
  if (source == dest) {
    return 1;
  } else if (!is_upper_string(source)) {
    if (visited.find(source) != visited.end()) {
      return 0;
    }
    visited.insert(source);
  }

  int paths = 0;
  for (const auto &child : graph.at(source)) {
    paths += count_paths1(child, dest, graph, visited);
  }
  return paths;
}

int count_paths2(const string &source, const string &dest,
                 const map<string, set<string>> &graph, set<string> visited,
                 optional<pair<string, int>> dup_small_cave) {
  if (source == dest) {
    if (dup_small_cave.has_value() && dup_small_cave.value().second < 2) {
      return 0;
    }
    return 1;
  } else if (!is_upper_string(source)) {
    if (dup_small_cave.has_value() && dup_small_cave.value().first == source) {
      if (dup_small_cave.value().second == 2) {
        return 0;
      }
      dup_small_cave.value().second++;
    } else {
      if (visited.find(source) != visited.end()) {
        return 0;
      }
      visited.insert(source);
    }
  }

  int paths = 0;
  for (const auto &child : graph.at(source)) {
    paths += count_paths2(child, dest, graph, visited, dup_small_cave);
  }
  if (source != "start" && !is_upper_string(source) && !dup_small_cave.has_value()) {
    dup_small_cave.emplace(make_pair(source, 1));
    for (const auto &child : graph.at(source)) {
      paths += count_paths2(child, dest, graph, visited, dup_small_cave);
    }
  }
  return paths;
}

int main() {
  ifstream ifs("input/12.txt");
  string line;
  map<string, set<string>> graph;

  while (getline(ifs, line)) {
    istringstream ss(line);
    string source;
    getline(ss, source, '-');
    string dest;
    getline(ss, dest, '-');
    graph[source].insert(dest);
    graph[dest].insert(source);
  }

  set<string> visited;
  cout << count_paths1("start", "end", graph, visited) << endl;
  optional<pair<string, int>> dup_small_cave;
  cout << count_paths2("start", "end", graph, visited, dup_small_cave) << endl;
}