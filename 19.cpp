#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include <set>
#include <queue>
#include <stdexcept>

using namespace std;

using coords_t = tuple<int, int, int>;

int main() {
  ifstream ifs("input/test.txt");
  map<unsigned, vector<coords_t>> scanners;
  set<coords_t> beacons;
  // Fill out the data

  if (scanners.find(0) == scanners.end()) {
    throw invalid_argument("No scanner 0");
  }

  queue<unsigned> to_explore;
  to_explore.push(0);
  set<unsigned> explored;
  while (!to_explore.empty()) {
    auto scanner = to_explore.front();
    to_explore.pop();
    explored.insert(scanner);
    const auto &scanned_beacons = scanners.at(scanner);
    for (const auto &[other_scanner, other_scanned_beacons] : scanners) {
      // scanner is already in explored, so it will also be ignored
      if (explored.find(other_scanner) != explored.end()) {

      }
    }
  }
}