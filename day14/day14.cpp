#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bits/stdc++.h>

using namespace std;

static unordered_map<string, long> memo(1000);

long countChars(unordered_map<string, char>& rules, string startChars, int days, char charToCount) {
  if (days == 0) {
    return 0;
  }
  string key = startChars + charToCount + to_string(days);
  if (memo.count(key) == 0) {
    if (rules.count(startChars) == 0) {
      memo[key] = countChars(rules, startChars, 0, charToCount);
    } else {
      char newChar = rules[startChars];
      string s1, s2;
      s1 += startChars[0], s1 += newChar, s2 += newChar, s2 += startChars[1];
      memo[key] = countChars(rules, s1, days - 1, charToCount) + countChars(rules, s2, days - 1, charToCount) + (newChar == charToCount);
    } 
  }
  return memo[key];
}

long charDifference(unordered_map<string, char>& rules, list<char>& polymer, unordered_set<char>& validChars, int iterations) {
  unordered_map<char, long> charCounts;
  for (char c : polymer) {
    charCounts[c] += 1;
  }
  for (char c : validChars) {
    char prev;
    for (list<char>::iterator it = polymer.begin(); it != polymer.end(); it++) {
      if (it != polymer.begin()) {
        string s;
        s += prev; s += *it;
        charCounts[c] += countChars(rules, s, iterations, c);
      }
      prev = *it;
    }
  }
  long minlong = LONG_MAX, maxlong = LONG_MIN;
  for (pair<char, long> countPair : charCounts) {
    maxlong = max(countPair.second, maxlong);
    minlong = min(countPair.second, minlong);
  }
  return maxlong - minlong;
}

int main() {
  vector<string> lines = getInputVector();
  unordered_map<string, char> rules;
  list<char> polymer;
  unordered_set<char> validChars;
  for (string& line : lines) {
    vector<string> toks = split(line, " -> ");
    if (toks.size() == 2) {
      rules[toks[0]] = toks[1][0];
      validChars.insert(toks[1][0]);
    } else {
      for (char c : toks[0]) {
        polymer.push_back(c);
      }
    }
  }

  cout << "Part 1: " << charDifference(rules, polymer, validChars, 10) << "\n";
  cout << "Part 2: " << charDifference(rules, polymer, validChars, 40) << "\n";

  return 0;
}
