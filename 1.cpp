#include <fstream>
#include <iostream>
#include <string>

void task1() {
  std::ifstream ifs{"input/1.txt"};
  int a, b, count = 0;
  ifs >> a;
  while (ifs >> b) {
    if (b > a) {
      count++;
    }
    a = b;
  }
  std::cout << count << std::endl;
}

void task2() {
  std::ifstream ifs{"input/1.txt"};
  int a, b, c, d, count = 0;
  ifs >> a;
  ifs >> b;
  ifs >> c;
  while (ifs >> d) {
    if (d > a) {
      count++;
    }
    a = b;
    b = c;
    c = d;
  }
  std::cout << count << std::endl;
}

int main() {
  task1();
  task2();
}