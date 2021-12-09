#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

int basinSize(Point lowPoint, unordered_map<Point, int, PointHash> heights) {
  queue<Point> frontier;
  unordered_set<Point, PointHash> internal;
  frontier.push(lowPoint);
  while (frontier.size() > 0) {
    Point p = frontier.front();
    frontier.pop();
    if (internal.count(p) > 0) {
      continue;
    }
    for (Point adj : p.adj4()) {
      if (heights.count(adj) > 0 && heights[adj] > heights[p] && heights[adj] != 9) {
        frontier.push(adj);
      }
    }
    internal.insert(p);
  }
  return internal.size();
}

int main() {
  vector<string> lines = getInputVector();
  unordered_map<Point, int, PointHash> heights(100);
  vector<Point> lowPoints;
  for (int r = 0; r < lines.size(); r++) {
    for (int c = 0; c < lines[r].length(); c++) {
      heights[{r, c}] = lines[r][c] - 48;
    }
  }
  int risk = 0;
  for (pair<Point, int> loc : heights) {
    bool lowpoint = true;
    for (Point adj : loc.first.adj4()) {
      if (heights.count(adj) > 0 && heights[adj] <= loc.second) {
        lowpoint = false; break;
      }
    }
    if (lowpoint) {
      lowPoints.push_back(loc.first);
      risk += 1 + loc.second;
    }
  }

  vector<int> basinSizes;
  for (Point p : lowPoints) {
    basinSizes.push_back(basinSize(p, heights));
  }
  sort(basinSizes.begin(), basinSizes.end());
  cout << "Part 1: " << risk << "\n";
  cout << "Part 2: " << basinSizes[basinSizes.size() - 1] * basinSizes[basinSizes.size() - 2] * basinSizes[basinSizes.size() - 3] << "\n";
  return 0;
}