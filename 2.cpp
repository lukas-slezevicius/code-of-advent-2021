#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void task1() {
  std::ifstream ifs{"input/2.txt"};
  std::string instruction;
  int x, depth = 0, horizontal_pos = 0;
  while (ifs >> instruction >> x) {
    if (instruction == "forward") {
      horizontal_pos += x;
    } else if (instruction == "down") {
      depth += x;
    } else if (instruction == "up") {
      depth -= x;
    } else {
      throw std::invalid_argument(instruction);
    }
  }
  std::cout << depth * horizontal_pos << std::endl;
}

void task2() {
  std::ifstream ifs{"input/2.txt"};
  std::string instruction;
  int x, depth = 0, horizontal_pos = 0, aim = 0;
  while (ifs >> instruction >> x) {
    if (instruction == "forward") {
      horizontal_pos += x;
      depth += aim * x;
    } else if (instruction == "down") {
      aim += x;
    } else if (instruction == "up") {
      aim -= x;
    } else {
      throw std::invalid_argument(instruction);
    }
  }
  std::cout << depth * horizontal_pos << std::endl;
}

int main() {
  task1();
  task2();
}