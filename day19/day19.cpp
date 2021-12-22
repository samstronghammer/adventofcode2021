#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static const PointN iVec({1, 0, 0});
static const PointN jVec({0, 1, 0});
static const PointN kVec({0, 0, 1});
static const vector<PointN> unitVecs = {iVec, jVec, kVec};
static const PointN posVec({1, 1, 1});
static const PointN negVec({-1, -1, -1});

vector<vector<vector<int>>> getOrientations() {
  vector<vector<vector<int>>> orientations;
  

}


bool merge(unordered_map<int, unordered_set<PointN, PointNHash>>& sensors, vector<int>& sensorsLeft) {
  for (int i = 0; i < sensorsLeft.size(); i++) {
    for (int j = i + 1; j < sensorsLeft.size(); j++) {
      int sensor1 = sensorsLeft[i], sensor2 = sensorsLeft[j];
      
    }
  }
}

int main() {
  vector<string> lines = getInputVector();
  unordered_map<int, unordered_set<PointN, PointNHash>> sensors;
  vector<int> sensorsLeft;
  unordered_set<PointN, PointNHash> currBeacons;
  int currSensor = -1;
  for (string line : lines) {
    if (line.length() == 0) {
      unordered_set<PointN, PointNHash> storedBeacons(currBeacons);
      sensors[currSensor] = storedBeacons;
      sensorsLeft.push_back(currSensor);
      currBeacons.clear();
    } else if (line[line.length() - 1] == '-') {
      currSensor = stoi(split(line, " ")[2]);
    } else {
      vector<string> toks = split(line, ",");
      currBeacons.insert(PointN(stoiVector(toks)));
    }
  }
  sensors[currSensor] = currBeacons;

  while (sensorsLeft.size() > 1) {
    bool merged = merge(sensors, sensorsLeft);
    if (merged) {
      cout << "merged\n";
      continue;
    } else {
      cout << "breaking\n";
      break;
    }
  }




  // cout << "Part 1: " << p1 << "\n";
  // cout << "Part 2: " << p2 << "\n";
  return 0;
}
