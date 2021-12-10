#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const map<char, char> opposites{
    {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
const map<char, int> missing_char_scores{
    {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
const map<char, int> completion_char_scores{
    {')', 1}, {']', 2}, {'}', 3}, {'>', 4}};

int main() {
  ifstream ifs("input/10.txt");
  string line;

  int syntax_score = 0;
  vector<unsigned long long> completion_str_scores;
  while (getline(ifs, line)) {
    bool corrupted = false;
    stack<char> s;
    for (char c : line) {
      if (c == '(' || c == '[' || c == '{' || c == '<') {
        s.push(opposites.at(c));
      } else if (s.top() == c) {
        s.pop();
      } else {
        syntax_score += missing_char_scores.at(c);
        corrupted = true;
        break;
      }
    }
    if (!corrupted) {
      unsigned long long completion_score = 0;
      while (!s.empty()) {
        char c = s.top();
        s.pop();
        completion_score *= 5;
        completion_score += completion_char_scores.at(c);
      }
      completion_str_scores.push_back(completion_score);
    }
  }

  sort(completion_str_scores.begin(), completion_str_scores.end());

  cout << syntax_score << endl;

  auto idx = completion_str_scores.size()/2;
  cout << completion_str_scores[idx] << endl;
}