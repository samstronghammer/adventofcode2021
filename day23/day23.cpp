#include "../util/util.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

unordered_map<char, int> moveCost = {{'A', 1}, {'B', 10}, {'C', 100}, {'D', 1000}};

struct Amphipod {
  char id;
  int stepsLeft;

  Amphipod(char id, int stepsLeft = 2) {
    this->stepsLeft = stepsLeft;
    this->id = id;
  }

  string toString() {
    return to_string(stepsLeft) + ":" + id;
  }
};

vector<Point> locationsVector = {
  {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0},
                  {2, 1},         {4, 1},         {6, 1},         {8, 1},
                  {2, 2},         {4, 2},         {6, 2},         {8, 2},
                  {2, 3},         {4, 3},         {6, 3},         {8, 3},
                  {2, 4},         {4, 4},         {6, 4},         {8, 4}
};

unordered_set<Point, PointHash> locations = {
  {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0},
                  {2, 1},         {4, 1},         {6, 1},         {8, 1},
                  {2, 2},         {4, 2},         {6, 2},         {8, 2},
                  {2, 3},         {4, 3},         {6, 3},         {8, 3},
                  {2, 4},         {4, 4},         {6, 4},         {8, 4}
};


inline int getCorrectX(Amphipod pod) {
  return (pod.id - 65) * 2 + 2;
}

bool isDone(unordered_map<Point, Amphipod, PointHash> amphipods) {
  for (pair<Point, Amphipod> podPair : amphipods) {
    if (getCorrectX(podPair.second) != podPair.first.x) return false;
  }
  return true;
}

int distance(Point start, Point end, Amphipod pod) {
  return (start.y + end.y + abs(end.x - start.x)) * moveCost.at(pod.id);
}

unordered_set<Point, PointHash> options(Point start, unordered_map<Point, Amphipod, PointHash>& amphipods) {
  queue<Point> frontier;
  unordered_set<Point, PointHash> internal;
  frontier.push(start);
  while (frontier.size() > 0) {
    Point p = frontier.front();
    frontier.pop();
    if (internal.count(p) > 0) {
      continue;
    }
    for (Point adj : p.adj4()) {
      if (locations.count(adj) > 0 && (amphipods.count(adj) == 0)) {
        frontier.push(adj);
      }
    }
    internal.insert(p);
  }
  return internal;
}

string amphipodsToString(unordered_map<Point, Amphipod, PointHash>& amphipods) {
  string s;
  for (Point location : locationsVector) {
    if (amphipods.count(location) == 0) {
      s += '.';
    } else {
      s += amphipods.at(location).toString();
    }
  }
  return s;
}

unordered_map<string, int> memo;

int totalCost(unordered_map<Point, Amphipod, PointHash> amphipods, int depth = 0) {
  if (depth > 8 && isDone(amphipods)) {
    return 0;
  }
  string amphipodString = amphipodsToString(amphipods);
  if (memo.count(amphipodString) == 0) {
    int bestCost = INT_MAX;
    for (pair<Point, Amphipod> podPair : amphipods) {
      if (podPair.second.stepsLeft != 0) {
        for (Point option : options(podPair.first, amphipods)) {
          int correctX = getCorrectX(podPair.second);
          if (podPair.second.stepsLeft == 1 && correctX != option.x) {
            continue; // skip option if pod ends up in wrong destination after 2 steps
          }
          if (option.x % 2 == 0 && option.x != 0 && option.x != 10 && correctX != option.x) {
            continue; // skip option if pod ends up in incorrect burrow
          }
          if (correctX == option.x && option.y < 4) {
            if (amphipods.count({option.x, option.y + 1}) == 0 || 
                amphipods.at({option.x, option.y + 1}).id != podPair.second.id ||
                amphipods.count({option.x, 4}) == 0 || 
                amphipods.at({option.x, 4}).id != podPair.second.id) {
              continue; // skip option if pod ends up on top of the wrong element
            }
          }
          unordered_map<Point, Amphipod, PointHash> newMap(amphipods);
          newMap.erase(podPair.first);
          newMap.emplace(option, Amphipod(podPair.second.id, podPair.second.stepsLeft - 1));
          if (distance(podPair.first, option, podPair.second) < bestCost) {
            int calculatedCost = totalCost(newMap, depth + 1);
            if (calculatedCost != INT_MAX) {
              bestCost = min(bestCost, distance(podPair.first, option, podPair.second) + calculatedCost);
            }
          }
        }
      }
    }
    memo.emplace(amphipodString, bestCost);
  }
  return memo.at(amphipodString);
}

int main() {
  vector<string> lines = getInputVector();
  unordered_map<Point, Amphipod, PointHash> amphipods;
  for (Point p : locations) {
    char c = lines[p.y + 1][p.x + 1];
    if (moveCost.count(c) > 0) {
      amphipods.emplace(p, Amphipod(c));
    }
  }

  cout << "Part 1: " << 18282 << '\n'; // Since the input changed for p2, the p1 solution is hardcoded here.
  cout << "Part 2: " << totalCost(amphipods) << '\n'; // runs for a couple minutes.
}
