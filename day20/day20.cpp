#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void consider(unordered_set<Point, PointHash>& importantPoints, unordered_set<Point, PointHash>& out) {
  out.clear();
  for (Point pixel : importantPoints) {
    out.insert(pixel);
    for (Point adjPixel : pixel.adj8()) {
      out.insert(adjPixel);
    }
  }
}

int main() {
  vector<string> lines = getInputVector();
  string enhance = lines[0];
  unordered_set<Point, PointHash> positivePixels;
  for (int r = 2; r < lines.size(); r++) {
    for (int c = 0; c < lines[r].length(); c++) {
      if (lines[r][c] == '#') {
        positivePixels.insert({r - 2, c});
      }
    }
  }

  for (int stepPair = 0; stepPair < 25; stepPair++) {
    unordered_set<Point, PointHash> to_consider, negativePixels;
    consider(positivePixels, to_consider);

    for (Point pixel : to_consider) {
      string surrounding = "";
      for (int dr = -1; dr < 2; dr++) {
        for (int dc = -1; dc < 2; dc++) {
          surrounding += positivePixels.count(pixel + (Point) {dr, dc}) == 0 ? "0" : "1";
        }
      }
      int index = stoi(surrounding, nullptr, 2);
      if (enhance[index] == '.') {
        negativePixels.insert(pixel);
      }
    }

    positivePixels.clear();

    consider(negativePixels, to_consider);

    for (Point pixel : to_consider) {
      string surrounding = "";
      for (int dr = -1; dr < 2; dr++) {
        for (int dc = -1; dc < 2; dc++) {
          surrounding += negativePixels.count(pixel + (Point) {dr, dc}) == 0 ? "1" : "0";
        }
      }
      int index = stoi(surrounding, nullptr, 2);
      if (enhance[index] == '#') {
        positivePixels.insert(pixel);
      }
    }

    if (stepPair == 1) cout << "Part 1: " << positivePixels.size() << "\n";
  }

  cout << "Part 2: " << positivePixels.size() << "\n";
  return 0;
}
