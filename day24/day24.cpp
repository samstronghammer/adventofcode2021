#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

long execute(long input, vector<string> commands) {
  int i = 0;
  string inputString = to_string(input);
  if (inputString.length() != 14) {
    return LONG_MAX;
  }
  for (char c : inputString) {
    if (c == '0') {
      return LONG_MAX;
    }
  }
  unordered_map<string, long> variables;
  for (string command : commands) {
    vector<string> toks = split(command, " ");
    if (toks.size() == 2) {
      variables[toks[1]] = inputString[i] - 48;
      i++;
    } else {
      long arg2 = toks[2][0] > 96 ? variables[toks[2]] : stoi(toks[2]);
      if (toks[0] == "add") {
        variables[toks[1]] = variables[toks[1]] + arg2;
      } else if (toks[0] == "mul") {
        variables[toks[1]] = variables[toks[1]] * arg2;
      } else if (toks[0] == "mod") {
        variables[toks[1]] = variables[toks[1]] % arg2;
      } else if (toks[0] == "eql") {
        variables[toks[1]] = variables[toks[1]] == arg2;
      } else if (toks[0] == "div") {
        variables[toks[1]] = variables[toks[1]] / arg2;
      }
    }
  }
  return variables["z"];
}

int main() {
  vector<string> lines = getInputVector();
  if (execute(59692994994998, lines) == 0) {
    cout << "Part 1: " << 59692994994998 << '\n';
  } else {
    exit(1);
  }
  if (execute(16181111641521, lines) == 0) {
    cout << "Part 1: " << 16181111641521 << '\n';
  } else {
    exit(1);
  }
  return 0;
}
