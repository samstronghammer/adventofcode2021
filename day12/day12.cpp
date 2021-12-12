#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int countPathsStartingWith(string tail, unordered_set<string>& beginning, bool dupUsed, unordered_map<string, unordered_set<string>>& connections) {
  if (tail == "end") {
    return 1;
  }
  int numPaths = 0;
  for (string s : connections[tail]) {
    if (s != "start" && (s[0] < 96 || beginning.count(s) == 0 || !dupUsed)) {
      unordered_set<string> newBeginning(beginning);
      newBeginning.insert(s);
      numPaths += countPathsStartingWith(s, newBeginning, dupUsed || (s[0] > 96 && beginning.count(s) > 0), connections);
    }
  }
  return numPaths;
}

int main() {
  vector<string> lines = getInputVector();
  unordered_map<string, unordered_set<string>> connections;
  for (string& line : lines) {
    vector<string> toks = split(line, "-");
    connections[toks[0]].insert(toks[1]);
    connections[toks[1]].insert(toks[0]);
  }
  unordered_set<string> start;
  start.insert("start");
  int p1 = countPathsStartingWith("start", start, true, connections);
  int p2 = countPathsStartingWith("start", start, false, connections);
  cout << "Part 1: " << p1 << "\n";
  cout << "Part 2: " << p2 << "\n";
  return 0;
}
