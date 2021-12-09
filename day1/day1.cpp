#include "../util/util.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<string> lines = getInputVector();
  vector<int> nums = stoiVector(lines);
  
  int p1 = 0, p2 = 0;
  for (int i = 1; i < lines.size(); i++) {
    if (nums[i - 1] < nums[i]) p1++;
    if (i >= 3 && nums[i - 3] < nums[i]) p2++;
  }

  cout << "Part 1: " << p1 << "\n";
  cout << "Part 2: " << p2 << "\n";
  return 0;
}
