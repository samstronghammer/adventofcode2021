#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Result {
  long p1;
  long p2;

  Result operator + (const Result& other) const {
    return {p1 + other.p1, p2 + other.p2};
  }
};

void applyDie(int *pos, int *score, int *die, int *dieRolls) {
  *pos = (*pos - 1 + *die * 3 + 3) % 10 + 1;
  *score += *pos;
  *die += 3; *die %= 10;
  *dieRolls += 3;
}

static unordered_map<string, Result> memo(88000);

Result getResult(int score1, int score2, int pos1, int pos2, bool p1Turn) {
  if (score1 >= 21) {
    return {1, 0};
  }
  if (score2 >= 21) {
    return {0, 1};
  }
  string key = "s1: " + to_string(score1) + ", s2: " + to_string(score2) + ", p1: " + to_string(pos1) + ", p2: " + to_string(pos2) + ", turn: " + to_string(p1Turn);
  if (memo.count(key) == 0) {
    for (int dieVal = 1; dieVal < 4; dieVal++) {
      for (int dieVal2 = 1; dieVal2 < 4; dieVal2++) {
        for (int dieVal3 = 1; dieVal3 < 4; dieVal3++) {
          if (p1Turn) {
            int newPos = (pos1 - 1 + dieVal + dieVal2 + dieVal3) % 10 + 1;
            memo[key] = memo[key] + getResult(score1 + newPos, score2, newPos, pos2, !p1Turn);
          } else {
            int newPos = (pos2 - 1 + dieVal + dieVal2 + dieVal3) % 10 + 1;
            memo[key] = memo[key] + getResult(score1, score2 + newPos, pos1, newPos, !p1Turn);
          }
        }
      }
    }
  }
  return memo[key];
}

int main() {
  int p1pos = 1, p1score = 0;
  int p2pos = 5, p2score = 0;
  int die = 1, dieRolls = 0;
  while (true) {
    applyDie(&p1pos, &p1score, &die, &dieRolls);
    if (p1score > 1000) break;
    applyDie(&p2pos, &p2score, &die, &dieRolls);
    if (p2score > 1000) break;
  }

  cout << "Part 1: " << min(p1score, p2score) * dieRolls << "\n";

  Result r = getResult(0, 0, 1, 5, true);

  cout << "Part 2: " << max(r.p1, r.p2) << "\n";
  return 0;
}
