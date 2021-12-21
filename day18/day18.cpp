#include "../util/util.h"
#include <iostream>
#include <vector>

using namespace std;

struct Snail {
  Snail *left = nullptr;
  Snail *right = nullptr;
  Snail *parent = nullptr;
  int value;
  string raw;

  Snail(int value) {
    init(nullptr, nullptr, value);
  }

  Snail(Snail *left, Snail *right) {
    init(left, right, -1);
  }

  void init(Snail *left, Snail *right, int value) {
    if (this->left != nullptr) this->left->free();
    if (this->right != nullptr) this->right->free();
    this->value = value;
    this->left = left;
    this->right = right;
    this->raw = value == -1 ? "[" + left->raw + "," + right->raw + "]" : std::to_string(value);
    if (this->left != nullptr) this->left->parent = this;
    if (this->right != nullptr) this->right->parent = this;
  }

  string to_string(string indent = "") {
    string childrenString = "";
    if (left != nullptr) {
      childrenString.append("\n" + left->to_string(indent + "  "));
    }
    if (right != nullptr) {
      childrenString.append("\n" + right->to_string(indent + "  "));
    }
    return indent + "v: " + std::to_string(value) + childrenString;
  }

  void reduce() {
    while (true) {
      if (this->explode(0)) continue;
      if (this->split()) continue;
      break;
    }
  }

  bool explode(int depth) {
    if (depth == 4 && this->value == -1) {
      Snail *l = this->findLeftNeighbor();
      Snail *r = this->findRightNeighbor();
      if (l != nullptr) {
        l->value += this->left->value;
        l->updateRaw();
      }
      if (r != nullptr) {
        r->value += this->right->value;
        r->updateRaw();
      };
      init(nullptr, nullptr, 0);
      updateRaw();
      return true;
    } else {
      if (this->left != nullptr && this->left->explode(depth + 1)) return true;
      return this->right != nullptr && this->right->explode(depth + 1);
    }
  }

  bool split() {
    if (value > 9) {
      init(new Snail(value / 2), new Snail((value + 1) / 2), -1);
      updateRaw();
      return true;
    } else {
      if (this->left != nullptr && this->left->split()) return true;
      return this->right != nullptr && this->right->split();
    }
  }

  int magnitude() {
    if (value != -1) {
      return value;
    }
    return left->magnitude() * 3 + right->magnitude() * 2;
  }

  Snail *findLeftNeighbor() {
    Snail *curr = this;
    while (curr != nullptr) {
      if (curr->parent != nullptr && curr->parent->right == curr) {
        curr = curr->parent->left;
        break;
      }
      curr = curr->parent;
    }
    if (curr == nullptr) return curr;
    while (curr->right != nullptr) curr = curr->right;
    return curr;
  }
  
  Snail *findRightNeighbor() {
    Snail *curr = this;
    while (curr != nullptr) {
      if (curr->parent != nullptr && curr->parent->left == curr) {
        curr = curr->parent->right;
        break;
      }
      curr = curr->parent;
    }
    if (curr == nullptr) return curr;
    while (curr->left != nullptr) curr = curr->left;
    return curr;
  }

  void updateRaw() {
    this->raw = value == -1 ? "[" + left->raw + "," + right->raw + "]" : std::to_string(value);
    if (this->parent != nullptr) this->parent->updateRaw();
  }

  void free() {
    if (this->left != nullptr) this->left->free();
    if (this->right != nullptr) this->right->free();
    delete this;
  }
};

Snail *rawToSnail(string raw) {
  if (raw[0] >= '0' && raw[0] <= '9') {
    return new Snail(stoi(raw.substr(0, 1)));
  }
  if (raw[0] != '[') {
    cout << "Unexpected character: " << raw[0] << '\n';
    exit(1);
  }
  Snail *left = rawToSnail(raw.substr(1));
  Snail *right = rawToSnail(raw.substr(2 + left->raw.length()));
  Snail *s = new Snail(left, right);
  return s;
}

int main() {
  vector<string> lines = getInputVector();
  Snail *sol = rawToSnail(lines[0]);
  for (int i = 1; i < lines.size(); i++) {
    Snail *nextSnail = new Snail(sol, rawToSnail(lines[i]));
    sol = nextSnail;
    sol->reduce();
  }
  cout << "Part 1: " << sol->magnitude() << "\n";
  sol->free();

  int bestMagnitude = 0;
  for (int i = 0; i < lines.size(); i++) {
    for (int j = 0; j < lines.size(); j++) {
      if (i != j) {
        Snail *sum = new Snail(rawToSnail(lines[i]), rawToSnail(lines[j]));
        sum->reduce();
        bestMagnitude = max(bestMagnitude, sum->magnitude());
        sum->free();
      }
    }
  }

  cout << "Part 2: " << bestMagnitude << "\n";
  return 0;
}
