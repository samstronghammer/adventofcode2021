#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <bits/stdc++.h>

using namespace std;

struct Cube {
  vector<pair<int, int>> dimensions;
  bool on;

  Cube intersect(Cube& other) {
    Cube c;
    for (int i = 0; i < dimensions.size(); i++) {
      int lowerbound = max(dimensions[i].first, other.dimensions[i].first);
      int upperbound = min(dimensions[i].second, other.dimensions[i].second);
      c.dimensions.push_back({lowerbound, upperbound});
    }
    return c;
  }

  vector<Cube> shatter(Cube& other) {
    vector<Cube> pieces;
    pair<int, int> everything = {INT_MIN, INT_MAX};
    for (int i = 0; i < 6; i++) {
      Cube c;
      vector<pair<int, int>> testDimensions;
      for (int j = 0; j < 3; j++) {
        if (j < i / 2) {
          testDimensions.push_back(other.dimensions[j]);
        } else if (j > i / 2){
          testDimensions.push_back(everything);
        } else {
          if (i % 2 == 0) {
            testDimensions.push_back({other.dimensions[j].second, INT_MAX});
          } else {
            testDimensions.push_back({INT_MIN, other.dimensions[j].first});
          }
        }
      }
      c.dimensions = testDimensions;
      Cube intersection = this->intersect(c);
      if (intersection.size() > 0) {
        pieces.push_back(intersection);
      }
    }
    return pieces;
  }

  long size() {
    long size = 1;
    for (pair<int, int> dimension : dimensions) {
      if (dimension.second < dimension.first) return 0;
      size *= dimension.second - dimension.first;
    }
    return size;
  }

  string toString() const {
    string s;
    for (pair<int, int> p : dimensions) {
      s += "(" + to_string(p.first) + "," + to_string(p.second) + ")";
    }
    return s;
  }

  bool operator == (const Cube& other) const {
    return toString() == other.toString() && on == other.on;
  }
};

struct CubeHash {
  std::size_t operator()(const Cube& k) const {
    return std::hash<std::string>()(k.toString());
  }
};

int main() {
  vector<string> lines = getInputVector();
  vector<Cube> cubes;
  for (string line : lines) {
    vector<string> toks = split(line, " ");
    Cube c;
    c.on = toks[0] == "on";
    vector<string> dimensionToks = split(toks[1], ",");
    for (string tok : dimensionToks) {
      vector<string> bounds = split(tok.substr(2), "..");
      c.dimensions.push_back({stoi(bounds[0]), stoi(bounds[1]) + 1}); // exclusive upper bound
    }
    cubes.push_back(c);
  }

  unordered_set<Cube, CubeHash> onCubes;
  for (Cube c : cubes) {
    unordered_set<Cube, CubeHash> toRemove, toAdd;
    for (Cube onCube : onCubes) {
      Cube intersection = c.intersect(onCube);
      if (intersection.size() > 0) {
        vector<Cube> pieces = onCube.shatter(c);
        toRemove.insert(onCube);
        for (Cube piece : pieces) {
          toAdd.insert(piece);
        }
      }
    }
    if (c.on) {
      toAdd.insert(c);
    }
    for (Cube add : toAdd) {
      onCubes.insert(add);
    }
    for (Cube remove : toRemove) {
      onCubes.erase(remove);
    }
  }

  int p1Size = 0;
  Cube p1Cube;
  p1Cube.dimensions = {{-50, 51}, {-50, 51}, {-50, 51}};
  for (Cube on : onCubes) {
    p1Size += on.intersect(p1Cube).size();
  }

  long totalSize = 0;
  for (Cube on : onCubes) {
    totalSize += on.size();
  }
  
  cout << "Part 1: " << p1Size << "\n";
  cout << "Part 2: " << totalSize << "\n";
  return 0;
}
