#include "../util/util.h"
#include <iostream>
#include <vector>
#include <bitset>
#include <bits/stdc++.h>

using namespace std;

struct Packet {
  int version;
  int typeId;
  long value;
  string raw;
  vector<Packet> children;
};

int versionSum(Packet p) {
  int count = p.version;
  for (Packet child : p.children) {
    count += versionSum(child);
  }
  return count;
}

Packet rawToPacket(string raw) {
  int version = stoi(raw.substr(0, 3), nullptr, 2);
  int typeId = stoi(raw.substr(3, 3), nullptr, 2);
  vector<Packet> children;
  Packet p = {version, typeId, 0, raw, children};
  if (typeId == 4) {
    // literal
    string literalBits; int index = 6;
    while (true) {
      literalBits.append(raw.substr(index + 1, 4));
      if (raw[index] == '0') {
        break;
      }
      index += 5;
    }
    p.value = stol(literalBits, nullptr, 2);
    p.raw = raw.substr(0, 6 + (literalBits.length() * 5 / 4));
  } else {
    // expression
    if (raw[6] == '0') {
      int totalBits = stoi(raw.substr(7, 15), nullptr, 2);
      int index = 22;
      while (index < 22 + totalBits) {
        Packet child = rawToPacket(raw.substr(index));
        p.children.push_back(child);
        index += child.raw.length();
      }
      p.raw = raw.substr(0, 22 + totalBits);
    } else {
      int numPackets = stoi(raw.substr(7, 11), nullptr, 2);
      int index = 18;
      for (int i = 0; i < numPackets; i++) {
        Packet child = rawToPacket(raw.substr(index));
        p.children.push_back(child);
        index += child.raw.length();
      }
      p.raw = raw.substr(0, index);
    }
    // run operation
    switch (p.typeId) {
      case 0:
        for (Packet child : p.children) {
          p.value += child.value;
        }
        break;
      case 1:
        p.value = 1;
        for (Packet child : p.children) {
          p.value *= child.value;
        }
        break;
      case 2:
        p.value = LONG_MAX;
        for (Packet child : p.children) {
          p.value = min(p.value, child.value);
        }
        break;
      case 3:
        p.value = LONG_MIN;
        for (Packet child : p.children) {
          p.value = max(p.value, child.value);
        }
        break;
      case 5:
        p.value = p.children[0].value > p.children[1].value;
        break;
      case 6:
        p.value = p.children[0].value < p.children[1].value;
        break;
      case 7:
        p.value = p.children[0].value == p.children[1].value;
        break;
    }
  }
  return p;
}

int main() {
  string line = getInputVector()[0];
  string bits;
  for (char c : line) {
    int numVal = c <= '9' ? c - 48 : c - 55;
    bits.append(bitset<4>(numVal).to_string());
  }
  Packet p = rawToPacket(bits);
  cout << "Part 1: " << versionSum(p) << "\n";
  cout << "Part 2: " << p.value << "\n";
  return 0;
}
