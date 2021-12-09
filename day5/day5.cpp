#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Line {
  Point start;
  Point end;
};

inline bool horzVert(Line line) {
  return line.start.x == line.end.x || line.start.y == line.end.y;
}

inline int sign(int value) {
  return (0 < value) - (value < 0);
}

int main() {
  vector<string> inputLines = getInputVector();
  vector<Line> lines;
  for (string& line : inputLines) {
    vector<string> toks = split(line, " -> ");
    vector<string> start = split(toks[0], ",");
    vector<string> end = split(toks[1], ",");
    lines.push_back({{stoi(start[0]), stoi(start[1])}, {stoi(end[0]), stoi(end[1])}});
  }

  unordered_map<string, int> pointCount(50);
  unordered_map<string, int> pointCount2(50);

  for (int i = 0; i < lines.size(); i++) {
    Line line = lines[i];
    int dx = sign(line.end.x - line.start.x);
    int dy = sign(line.end.y - line.start.y);
    Point p = {line.start.x - dx, line.start.y - dy};
    do {
      p = p + (Point) {dx, dy};
      string pString = p.toString();
      if (horzVert(line)) {
        pointCount[pString]++;
      }
      pointCount2[pString]++;
    } while (p != line.end);
  }

  int numCommonPoints = 0;
  for (pair<string, int> p : pointCount) {
    numCommonPoints += (p.second > 1);
  }
  int numCommonPoints2 = 0;
  for (pair<string, int> p : pointCount2) {
    numCommonPoints2 += (p.second > 1);
  }

  cout << "Part 1: " << numCommonPoints << "\n";
  cout << "Part 2: " << numCommonPoints2 << "\n";
  return 0;
}
