#include "../util/util.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

inline int p2DistanceToFuel(int distance) {
  return distance * (distance + 1) / 2;
}

int main() {
  vector<string> lines = getInputVector();
  vector<string> crabStrings = split(lines[0], ",");
  vector<int> crabPositions = stoiVector(crabStrings);
  sort(crabPositions.begin(), crabPositions.end());
  int goal = crabPositions[crabPositions.size() / 2];
  int p1fuel = 0;
  for (int pos : crabPositions) {
    p1fuel += abs(pos - goal);
  }

  int p2fuel = INT_MAX;
  for (int i = crabPositions[0]; i < crabPositions[crabPositions.size() - 1]; i++) {
    int totalFuel = 0;
    for (int pos : crabPositions) {
      totalFuel += p2DistanceToFuel(abs(pos - i));
    }
    if (totalFuel < p2fuel) p2fuel = totalFuel;
  }

  cout << "Part 1: " << p1fuel << "\n";
  cout << "Part 2: " << p2fuel << "\n";

  return 0;
}