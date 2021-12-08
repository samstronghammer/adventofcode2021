#include "../util/util.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

bool missingLetterFrom(string& option, string& known) {
  for (char c : known) {
    if (option.find(c) == string::npos) return true;
  }
  return false;
}

unordered_map<string, int> getMapping(vector<string>& inputs) {
  unordered_map<string, int> mapping(10);
  unordered_map<int, string> backwardMapping(10);
  vector<string> len5Options;
  vector<string> len6Options;
  for (string& in : inputs) {
    switch (in.length()) {
      case 2: mapping[in] = 1; backwardMapping[1] = in; break;
      case 3: mapping[in] = 7; break;
      case 4: mapping[in] = 4; backwardMapping[4] = in; break;
      case 5: len5Options.push_back(in); break;
      case 6: len6Options.push_back(in); break;
      case 7: mapping[in] = 8; break;
    }
  }
  for (string& s : len6Options) {
    if (missingLetterFrom(s, backwardMapping[1])) {
      mapping[s] = 6;
      backwardMapping[6] = s;
    } else if (missingLetterFrom(s, backwardMapping[4])) {
      mapping[s] = 0;
    } else {
      mapping[s] = 9;
    }
  }
  for (string& s : len5Options) {
    if (!missingLetterFrom(s, backwardMapping[1])) {
      mapping[s] = 3;
    } else if (missingLetterFrom(backwardMapping[6], s)) {
      mapping[s] = 2;
    } else {
      mapping[s] = 5;
    }
  }
  return mapping;
}

int main() {
    vector<string> lines = getInputVector();
    int p1Sum = 0, p2Sum = 0;
    for (string& line : lines) {
      vector<string> sides = split(line, " | ");
      vector<string> inputs = split(sides[0], " ");
      vector<string> outputs = split(sides[1], " ");
      for (string& in : inputs) {
        sort(in.begin(), in.end());
      }
      for (string& out : outputs) {
        sort(out.begin(), out.end());
      }
      unordered_map<string, int> mapping = getMapping(inputs);
      int outNum = 0;
      for (string& out : outputs) {
        if (out.length() == 2 || out.length() == 3 || out.length() == 4 || out.length() == 7) {
          p1Sum++;
        }
        outNum *= 10;
        outNum += mapping[out];
      }
      p2Sum += outNum;
    }

    cout << "Part 1: " << p1Sum << "\n";
    cout << "Part 2: " << p2Sum << "\n";
    return 0;
}
