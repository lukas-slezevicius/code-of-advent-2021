#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define BOARD_SIZE 5

typedef std::pair<int, bool> Cell;
typedef std::vector<Cell> Row;
typedef std::vector<Row> Board;

bool has_board_won(const Board &board) {
  for (auto &row : board) {
    bool has_won = true;
    for (auto &cell : row) {
      if (!cell.second) {
        has_won = false;
        break;
      }
    }
    if (has_won) {
      return true;
    }
  }
  for (int j = 0; j < BOARD_SIZE; j++) {
    bool has_won = true;
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (!board.at(i).at(j).second) {
        has_won = false;
        break;
      }
    }
    if (has_won) {
      return true;
    }
  }
  return false;
}

int unmarked_sum(const Board &board) {
  int sum = 0;
  for (auto &row : board) {
    for (auto &cell : row) {
      if (!cell.second) {
        sum += cell.first;
      }
    }
  }
  return sum;
}

void mark_cells(Board &board, int n) {
  for (auto &row : board) {
    for (auto &cell : row) {
      if (cell.first == n) {
        cell.second = true;
      }
    }
  }
}

void task1(std::vector<Board> boards, const std::vector<int> &numbers) {
  for (auto n : numbers) {
    for (auto &board : boards) {
      mark_cells(board, n);
      if (has_board_won(board)) {
        std::cout << n * unmarked_sum(board) << std::endl;
        return;
      }
    }
  }
}

void task2(std::vector<Board> boards, const std::vector<int> &numbers) {
  for (auto n : numbers) {
    for (int i = 0; i < boards.size(); i++) {
      auto &board = boards.at(i);
      mark_cells(board, n);
      if (has_board_won(board)) {
        if (boards.size() == 1) {
          std::cout << n * unmarked_sum(board) << std::endl;
          return;
        }
        boards.erase(boards.begin() + i);
        i--;
      }
    }
  }
}

int main() {
  std::ifstream ifs{"input/4.txt"};
  std::vector<int> numbers;
  std::string line, s;

  std::getline(ifs, line);
  std::istringstream ss(line);
  while (getline(ss, s, ',')) {
    numbers.push_back(std::stoi(s));
  }

  // Eat up the empty line
  std::getline(ifs, line);

  std::vector<Board> boards;
  while (ifs) {
    Board board;
    for (int i = 0; i < BOARD_SIZE; i++) {
      Row row;
      std::getline(ifs, line);
      std::istringstream ss(line);
      for (int j = 0; j < BOARD_SIZE; j++) {
        int n;
        ss >> n;
        Cell cell(n, false);
        row.push_back(cell);
      }
      board.push_back(row);
    }
    boards.push_back(board);

    // Eat up the empty line
    std::getline(ifs, line);
  }

  task1(boards, numbers);
  task2(boards, numbers);
}