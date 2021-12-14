#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <bits/stdc++.h>

using namespace std;

void performFold(unordered_set<Point, PointHash>& holes, Point fold) {
  unordered_set<Point, PointHash> toAdd, toRemove;
  for (Point p : holes) {
    if (p.x > fold.x && p.y > fold.y) {
      Point delta = p - fold;
      delta.x = fold.x == INT_MIN ? 0 : delta.x;
      delta.y = fold.y == INT_MIN ? 0 : delta.y;
      Point newPoint = p - delta - delta;
      toRemove.insert(p);
      toAdd.insert(newPoint);
    }
  }
  for (Point p : toAdd) {
    holes.insert(p);
  }
  for (Point p : toRemove) {
    holes.erase(p);
  }
}

int main() {
  vector<string> lines = getInputVector();
  unordered_set<Point, PointHash> holes;
  vector<Point> folds;
  for (string& line : lines) {
    if (line.length() > 0) {
      if (line[0] == 'f') {
        string eqn = split(line, "fold along ")[1];
        vector<string> toks = split(eqn, "=");
        int xval = toks[0] == "x" ? stoi(toks[1]) : INT_MIN;
        int yval = toks[0] == "y" ? stoi(toks[1]) : INT_MIN;
        folds.push_back({xval, yval});
      } else {
        vector<string> toks = split(line, ",");
        holes.insert({stoi(toks[0]), stoi(toks[1])});
      }
    }
  }
  performFold(holes, folds[0]);
  cout << "Part 1: " << holes.size() << "\n";
  for (int i = 1; i < folds.size(); i++) {
    performFold(holes, folds[i]);
  }
  cout << "Part 2:" << "\n";
  int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;
  for (Point p : holes) {
    if (p.x < minx) minx = p.x;
    if (p.y < miny) miny = p.y;
    if (p.x > maxx) maxx = p.x;
    if (p.y > maxy) maxy = p.y;
  }
  for (int y = miny; y <= maxy; y++) {
    for (int x = minx; x <= maxx; x++) {
      holes.count({x, y}) > 0 ? cout << '#' : cout << ' ';
    }
    cout << "\n";
  }


  return 0;
}
