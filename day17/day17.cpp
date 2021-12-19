#include "../util/util.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// target area: x=211..232, y=-124..-69
const int minx = 211, miny = -124, maxx = 232, maxy = -69;

int calcBestY(Point v) {
  Point pos = {0, 0};
  int bestY = INT_MIN;
  while (pos.y >= miny) {
    pos = pos + v;
    bestY = max(bestY, pos.y);
    v.y--;
    v.x = max(v.x - 1, 0);
    if (pos.x >= minx && pos.x <= maxx && pos.y >= miny && pos.y <= maxy) {
      return bestY;
    }
  }
  return INT_MIN;
}

int main() {
  int count = 0, bestY = INT_MIN;
  for (int x = 0; x <= maxx; x++) {
    for (int y = abs(miny); y >= miny; y--) {
      int calc = calcBestY({x, y});
      bestY = max(bestY, calc);
      count += calc != INT_MIN;
    }
  }

  cout << "Part 1: " << bestY << "\n";
  cout << "Part 2: " << count << "\n";
  return 0;
}



