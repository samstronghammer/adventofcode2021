#include "../util/util.h"
#include <iostream>

using namespace std;

int main() {
  vector<string> lines = getInputVector();
  int depth = 0, distance = 0, depth2 = 0, aim = 0;
  for (string const &s: lines) {
    vector<string> toks = split(s, " ");
    string dir = toks[0];
    int mag = stoi(toks[1]);
    if (dir == "forward") {
      distance += mag;
      depth2 += aim * mag;
    } else if (dir == "down") {
      depth += mag;
      aim += mag;
    } else if (dir == "up") {
      depth -= mag;
      aim -= mag;
    } else {
      cout << "unknown prefix: " << dir << "\n";
    }
  }
  cout << "Part 1: " << depth * distance << "\n";
  cout << "Part 2: " << depth2 * distance << "\n";
  return 0;
}