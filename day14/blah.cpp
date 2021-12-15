#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bits/stdc++.h>

using namespace std;

static unordered_map<string, long long> memo(1000);

long long countChars(unordered_map<string, char>& rules, string startChars, int days, char charToCount) {
  if (days == 0) {
    return 0;
  }
  string key = startChars + to_string(days);
  // cout << key << "\n";
  if (memo.count(key) == 0) {
    if (rules.count(startChars) == 0) {
      memo[key] = countChars(rules, startChars, 0, charToCount);
    } else {
      char newChar = rules[startChars];
      string s1, s2;
      s1 += startChars[0], s1 += newChar, s2 += newChar, s2 += startChars[1];
      // cout << newChar << charToCount << (newChar == charToCount)
      memo[key] = countChars(rules, s1, days - 1, charToCount) + countChars(rules, s2, days - 1, charToCount) + (int)(newChar == charToCount);
    } 
  }
  cout << key << " " << memo[key] << "\n";
  return memo[key];
}

long long countCharsHelper(unordered_map<string, char>& rules, string startChars, int days, char charToCount) {

}

// void applyInsertion(unordered_map<string, char>& rules, list<char>& polymer) {
//   char prev;
//   for (list<char>::iterator it = polymer.begin(); it != polymer.end(); it++) {
//     if (it != polymer.begin()) {
//       char curr = *it;
//       string s;
//       s += prev; s += curr;
//       if (rules.count(s) > 0) {
//         char insert = rules[s];
//         polymer.insert(it, insert);
//       }
//     }
//     prev = *it;
//   }
// }

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

  // for (int i = 0; i < 10; i++) {
  //   applyInsertion(rules, polymer);
  // }

  // unordered_map<char, int> counts;
  // for (char c : polymer) {
  //   counts[c]++;
  // }
  // int mincount = INT_MAX, maxcount = INT_MIN;
  // for (pair<char, int> countPair : counts) {
  //   if (countPair.second > maxcount) maxcount = countPair.second;
  //   if (countPair.second < mincount) mincount = countPair.second;
  // }

  // cout << "Part 1: " << maxcount - mincount << "\n";

  unordered_map<char, long long> charCounts;
  for (char c : validChars) {
    char prev;
    for (list<char>::iterator it = polymer.begin(); it != polymer.end(); it++) {
      if (it != polymer.begin()) {
        char curr = *it;
        string s;
        s += prev; s += curr;
        charCounts[c] += countChars(rules, s, 10, c);
        // cout << c << charCounts[c] << "\n";
        // cout << countChars(rules, s, 40, c) << "\n";
      }
      prev = *it;
    }
  }

  long long minlong = LONG_LONG_MAX, maxlong = LONG_LONG_MIN;
  for (pair<char, long long> countPair : charCounts) {
    cout << countPair.first << countPair.second << "\n";
    // cout << maxlong << '\n';
    maxlong = max(countPair.second, maxlong);
    minlong = min(countPair.second, minlong);
  }

  cout << "Part 2: " << maxlong - minlong << "\n";

  return 0;
}
