#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>

class Point {
public:
  int x;
  int y;
  Point(int x, int y) : x(x), y(y) {}

  bool operator==(const Point &p) const { return x == p.x && y == p.y; }

  bool operator<(const Point &p) const {
    if (x == p.x) {
      return y < p.y;
    }
    return x < p.x;
  }
};

class Line {
public:
  Point p1;
  Point p2;

  Line(Point p1, Point p2) : p1(p1), p2(p2) {}

  // Only works for lines with grad that's in (0, -1, 1, inf)
  std::vector<Point> point_range() const {
    std::vector<Point> v;
    if (p1.x == p2.x) {
      int min_y = std::min(p1.y, p2.y);
      int max_y = std::max(p1.y, p2.y);
      for (int y = min_y; y <= max_y; y++) {
        Point p(p1.x, y);
        v.push_back(p);
      }
    } else {
      int grad, min_x, max_x, start_y;
      if (p1.x < p2.x) {
        grad = (p2.y - p1.y) / (p2.x - p1.x);
        start_y = p1.y;
        min_x = p1.x;
        max_x = p2.x;
      } else {
        grad = (p1.y - p2.y) / (p1.x - p2.x);
        start_y = p2.y;
        min_x = p2.x;
        max_x = p1.x;
      }

      for (int x = min_x, y = start_y; x <= max_x; x++, y += grad) {
        Point p(x, y);
        v.push_back(p);
      }
    }
    return v;
  }
};

std::vector<Line> read_input(std::string file_name) {
  std::vector<Line> v;
  std::ifstream ifs(file_name);
  std::string s;
  std::regex pat{R"((\d+),(\d+) -> (\d+),(\d+))"};
  while (std::getline(ifs, s)) {
    std::smatch m;
    if (!std::regex_match(s, m, pat)) {
      throw std::invalid_argument("Line does not match pattern");
    }
    Point p1(std::stoi(m[1]), std::stoi(m[2]));
    Point p2(std::stoi(m[3]), std::stoi(m[4]));
    Line l(p1, p2);
    v.push_back(l);
  }
  return v;
}

int count_overlapping_points(const std::vector<Line> &lines) {
  std::map<Point, int> point_counts;
  for (const auto &line : lines) {
    auto v = line.point_range();
    for (Point p : v) {
      if (point_counts.find(p) == point_counts.end()) {
        point_counts[p] = 0;
      }
      point_counts[p]++;
    }
  }
  int final_count = 0;
  for (const auto &[key, value] : point_counts) {
    if (value > 1) {
      final_count++;
    }
  }
  return final_count;
}

void task1(std::vector<Line> lines) {
  // Remove diagonal lines
  auto remove_it = std::remove_if(lines.begin(), lines.end(), [](Line line) {
    return line.p1.x != line.p2.x && line.p1.y != line.p2.y;
  });
  lines.erase(remove_it, lines.end());

  auto count = count_overlapping_points(lines);
  std::cout << count << std::endl;
}

void task2(const std::vector<Line> &lines) {
  auto count = count_overlapping_points(lines);
  std::cout << count << std::endl;
}

int main() {
  auto lines = read_input("input/5.txt");
  task1(lines);
  task2(lines);
}