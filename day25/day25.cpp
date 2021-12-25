#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
  vector<string> lines = getInputVector();
  unordered_set<Point, PointHash> eastHerd;
  unordered_set<Point, PointHash> southHerd;
  for (int r = 0; r < lines.size(); r++) {
    for (int c = 0; c < lines[r].length(); c++) {
      char cucumber = lines[r][c];
      if (cucumber == '>') {
        eastHerd.insert({r, c});
      } else if (cucumber == 'v') {
        southHerd.insert({r, c});
      }
    }
  }

  int numSteps = 0;
  while (true) {
    bool moved = false;
    unordered_set<Point, PointHash> newEastHerd, newSouthHerd;
    for (Point p : eastHerd) {
      Point goalPoint = {p.x, ((p.y + 1) % lines[p.x].length())};
      if (eastHerd.count(goalPoint) == 0 && southHerd.count(goalPoint) == 0) {
        newEastHerd.insert(goalPoint); 
        moved = true;
      } else {
        newEastHerd.insert(p);
      }
    }
    for (Point p : southHerd) {
      Point goalPoint = {(p.x + 1) % lines.size(), p.y};
      if (newEastHerd.count(goalPoint) == 0 && southHerd.count(goalPoint) == 0) {
        newSouthHerd.insert(goalPoint); 
        moved = true;
      } else {
        newSouthHerd.insert(p);
      }
    }
    numSteps++;
    if (moved) {
      eastHerd = newEastHerd;
      southHerd = newSouthHerd;
    } else {
      break;
    }
  }

  cout << "Part 1: " << numSteps << "\n";
  return 0;
}
