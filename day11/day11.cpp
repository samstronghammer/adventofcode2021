#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

int main() {
  vector<string> lines = getInputVector();
  unordered_map<Point, int, PointHash> octopuses;
  for (int r = 0; r < lines.size(); r++) {
    for (int c = 0; c < lines[r].length(); c++) {
      char octopus = lines[r][c];
      octopuses[{r, c}] = octopus - 48;
    }
  }
  int flashes = 0, i = 0, sync = 0;
  while (true) {
    queue<Point> needToFlash;
    for (pair<Point, int> octopus : octopuses) {
      octopuses[octopus.first]++;
      if (octopuses[octopus.first] > 9) {
        needToFlash.push(octopus.first);
      }
    }
    unordered_set<Point, PointHash> flashed;
    while (needToFlash.size() > 0) {
      Point flashPoint = needToFlash.front();
      needToFlash.pop();
      if (flashed.count(flashPoint) > 0) {
        continue;
      }
      flashed.insert(flashPoint);
      for (Point p : flashPoint.adj8()) {
        if (octopuses.count(p) > 0) {
          octopuses[p]++;
          if (octopuses[p] > 9 && flashed.count(p) == 0) {
            needToFlash.push(p);
          }
        }
      }
    }
    for (Point p : flashed) {
      octopuses[p] = 0;
    }
    flashes += i < 100 ? flashed.size() : 0;
    i++;
    if (flashed.size() == octopuses.size()) {
      sync = i;
      break;
    }
  }

  cout << "Part 1: " << flashes << "\n";
  cout << "Part 2: " << sync << "\n";
  return 0;
}
