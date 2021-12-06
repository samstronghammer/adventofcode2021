#include "../util/util.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

static unordered_map<int, long> memo(1000);

long numOneFish(int initialFish, int days) {
  if (days <= initialFish) {
    return 1;
  }
  int key = days * 10 + initialFish;
  if (memo.count(key) == 0) {
    memo[key] = numOneFish(6, days - initialFish - 1) + numOneFish(8, days - initialFish - 1);
  }
  return memo[key];
}

long numFish(vector<int>& fishes, int days) {
  long totalFish = 0;
  for (int fish : fishes) {
    totalFish += numOneFish(fish, days);
  }
  return totalFish;
}

int main() {
  string line = getInputVector()[0];
  vector<string> toks = split(line, ",");
  vector<int> fishes = stoiVector(toks);

  cout << "Part 1: " << numFish(fishes, 80) << "\n";
  cout << "Part 2: " << numFish(fishes, 256) << "\n";
  return 0;
}