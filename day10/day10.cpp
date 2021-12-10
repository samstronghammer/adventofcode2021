#include "../util/util.h"
#include <iostream>
#include <vector>
#include <stack>
#include <bits/stdc++.h>

using namespace std;

int charToErrorScore(char c) {
  switch (c) {
    case ')': return 3;
    case ']': return 57;
    case '}': return 1197;
    case '>': return 25137;
  }
  cout << "Invalid char\n";
  exit(1);
}

int charToAcScore(char c) {
  switch (c) {
    case '(': return 1;
    case '[': return 2;
    case '{': return 3;
    case '<': return 4;
  }
  cout << "Invalid char\n";
  exit(1);
}

int main() {
  vector<string> lines = getInputVector();
  int errorScore = 0;
  vector<long> acScores;
  for (string& line : lines) {
    stack<char> chars;
    bool corrupted = false;
    for (char c : line) {
      if (c == '(' || c == '<' || c == '{' || c == '[') {
        chars.push(c);
      } else {
        if (0 < c - chars.top() && c - chars.top() < 3) {
          chars.pop();
        } else {
          errorScore += charToErrorScore(c);
          corrupted = true;
          break;
        }
      }
    }
    if (chars.size() > 0 && !corrupted) {
      long acScore = 0;
      while (chars.size() > 0) {
        acScore *= 5;
        acScore += charToAcScore(chars.top());
        chars.pop();
      }
      acScores.push_back(acScore);
    }
  }

  sort(acScores.begin(), acScores.end());

  cout << "Part 1: " << errorScore << "\n";
  cout << "Part 2: " << acScores[acScores.size() / 2] << "\n";
  return 0;
}
