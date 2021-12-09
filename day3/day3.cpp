#include "../util/util.h"
#include <iostream>

using namespace std;

int supportRating(list<string> lines, bool oxygen, int bitIndex = 0) {
  if (lines.size() == 1) {
    return stoi(lines.front(), 0, 2);
  }
  int numOnes = 0;
  for (string const &s: lines) {
    if (s[bitIndex] == '1') {
      numOnes++;
    }
  }
  bool keepOnes = true;
  if ((numOnes * 2 >= lines.size() && !oxygen) || (numOnes * 2 < lines.size() && oxygen)) {
    keepOnes = false;
  }
  struct RemoveOp {
    int bitIndex;
    bool keepOnes;
    RemoveOp(int bitIndex, bool keepOnes) { this->bitIndex = bitIndex; this->keepOnes = keepOnes; }
    bool operator() (const string value) {
      return (value[bitIndex] == '0' && keepOnes) || (value[bitIndex] == '1' && !keepOnes);
    }
  };

  lines.remove_if(RemoveOp(bitIndex, keepOnes));
  return supportRating(lines, oxygen, bitIndex + 1);
}

int main() {
  vector<string> lineVector = getInputVector();
  list<string> lines(lineVector.begin(), lineVector.end());
  int bitLength = lines.front().length();
  int numOnes[bitLength] = {0};
  for (string const &s: lines) {
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '0') {
        continue;
      } else if (s[i] == '1') {
        numOnes[i]++;
      } else {
        cout << "unknown character " << s[i] << "\n";
      }
    }
  }

  char gammaString[bitLength];
  char epsilonString[bitLength];
  for (int i = 0; i < bitLength; i++) {
    if (numOnes[i] > lines.size() / 2) {
      gammaString[i] = '1';
      epsilonString[i] = '0';
    } else {
      gammaString[i] = '0';
      epsilonString[i] = '1';
    }
  }

  list<string> linesCopy(lines);
  int oxygenRating = supportRating(linesCopy, true);
  list<string> linesCopy2(lines);
  int c02Rating = supportRating(linesCopy2, false);

  cout << "Part 1: " << stoi(gammaString, 0, 2) * stoi(epsilonString, 0, 2) << "\n";
  cout << "Part 2: " << oxygenRating * c02Rating << "\n";
  return 0;
}