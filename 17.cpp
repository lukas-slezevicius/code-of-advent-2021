#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
  ifstream ifs("input/17.txt");
  ifs.ignore(15);
  int tx1;
  ifs >> tx1;
  ifs.ignore(2);
  int tx2;
  ifs >> tx2;
  ifs.ignore(4);
  int ty1;
  ifs >> ty1;
  ifs.ignore(2);
  int ty2;
  ifs >> ty2;

  int max_dy = abs(ty1) - 1;

  cout << max_dy*(max_dy+1)/2 << endl;

  int possible_velocity_count = 0;
  for (int dx = 1; dx <= tx2; dx++) {
    for (int dy = max_dy; dy >= ty1; dy--) {
      int x = 0, y = 0;
      int cur_dx = dx, cur_dy = dy;
      while (x <= tx2 && y >= ty1) {
        x += cur_dx;
        y += cur_dy;
        if (x >= tx1 && x <= tx2 && y >= ty1 && y <= ty2) {
          possible_velocity_count++;
          break;
        }
        if (cur_dx > 0) {
          cur_dx--;
        }
        cur_dy--;
      }
    }
  }
  cout << possible_velocity_count << endl;
}