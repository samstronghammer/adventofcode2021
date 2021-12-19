#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

int main() {
  vector<string> lines = getInputVector();
  unordered_map<Point, int, PointHash> locs, dist;
  unordered_set<Point, PointHash> internal, external;
  auto closer = [&dist](const Point& p1, const Point& p2) {
    return dist.at(p1) > dist.at(p2);
  };
  priority_queue<Point, vector<Point>, decltype(closer)> q(closer);
  for (int r = 0; r < lines.size(); r++) {
    for (int c = 0; c < lines[r].length(); c++) {
      for (int rcopy = 0; rcopy < 5; rcopy++) {
        for (int ccopy = 0; ccopy < 5; ccopy++) {
          Point p = {r + rcopy * (int) lines.size(), c + ccopy * (int) lines[r].length()};
          locs[p] = ((lines[r][c] - 48 + rcopy + ccopy - 1) % 9) + 1;
          dist[p] = INT_MAX;
          external.insert(p);
        }
      }
    }
  }
  dist[{0, 0}] = 0;
  q.emplace((Point) {0, 0});

  while (q.size() > 0) {
    Point u = q.top();
    q.pop();
    if (internal.count(u) > 0) {
      continue;
    }
    internal.insert(u);
    external.erase(u);
    for (Point p : u.adj4()) {
      if (external.count(p) > 0) {
        int alt = dist[u] + locs[p];
        if (alt < dist[p]) {
          dist[p] = alt;
          q.emplace(p);
        }
      }
    }
  }
  
  Point end1 = {(int) lines.size() - 1, (int) lines[lines.size() - 1].length() - 1};
  Point end2 = end1 + (Point) {4 * (int) lines.size(), 4 * (int) lines[0].length()};
  cout << "Part 1: " << dist[end1] << "\n";
  cout << "Part 2: " << dist[end2] << "\n";
  return 0;
}
