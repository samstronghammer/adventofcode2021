#include <string>
#include <list>
#include <vector>
#include <iostream>

struct Point {
  int x;
  int y;

  bool operator == (const Point& other) const {
    return x == other.x && y == other.y;
  }

  bool operator != (const Point& other) const {
    return x != other.x || y != other.y;
  }

  Point operator + (const Point& other) const {
    return {x + other.x, y + other.y};
  }

  Point operator - (const Point& other) const {
    return {x - other.x, y - other.y};
  }

  std::string toString() const {
    return std::to_string(x) + "," + std::to_string(y);
  }

  std::vector<Point> adj4() const {
    std::vector<Point> adj = {{x, y - 1}, {x - 1, y}, {x + 1, y}, {x, y + 1}};
    return adj;
  }

  std::vector<Point> adj8() const {
    std::vector<Point> adj = {{x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1}, {x - 1, y}, {x + 1, y}, {x - 1, y + 1}, {x, y + 1}, {x + 1, y + 1}};
    return adj;
  }
};

struct PointHash {
  std::size_t operator()(const Point& k) const {
    return std::hash<std::string>()(k.toString());
  }
};

struct PointN {

  std::vector<int> vec;

  PointN(std::vector<int> v) {
    this->vec = v;
  }

  bool operator == (const PointN& other) const {
    if (vec.size() != other.vec.size()) return false;
    for (int i = 0; i < vec.size(); i++) {
      if (vec[i] != other.vec[i]) return false;
    }
    return true;
  }

  bool operator != (const PointN& other) const {
    return !(*this == other);
  }

  PointN operator + (const PointN& other) const {
    if (vec.size() != other.vec.size()) {
      std::cout << "PointN size mismatch in +"; 
      exit(1);
    }
    std::vector<int> newV;
    for (int i = 0; i < vec.size(); i++) {
      newV.push_back(vec[i] + other.vec[i]);
    }
    return PointN(newV);
  }

  PointN operator - (const PointN& other) const {
    if (vec.size() != other.vec.size()) {
      std::cout << "PointN size mismatch in -"; 
      exit(1);
    }
    std::vector<int> newV;
    for (int i = 0; i < vec.size(); i++) {
      newV.push_back(vec[i] - other.vec[i]);
    }
    return PointN(newV);
  }

  std::string toString() const {
    if (vec.size() == 0) return "";
    std::string s = std::to_string(vec[0]);
    for (int i = 1; i < vec.size(); i++) {
      s += "," + std::to_string(vec[i]);
    }
    return s;
  }

  PointN dot(const PointN& other) const {
    if (vec.size() != other.vec.size()) {
      std::cout << "PointN size mismatch in dot"; 
      exit(1);
    }
    std::vector<int> newV;
    for (int i = 0; i < vec.size(); i++) {
      newV.push_back(vec[i] * other.vec[i]);
    }
    return PointN(newV);
  }

  PointN cross(const PointN& other) const {
    if (vec.size() != 3 || other.vec.size() != 3) {
      std::cout << "PointN size mismatch in cross-- must be size 3"; 
      exit(1);
    }
    std::vector<int> newV;
    newV.push_back(vec[1] * other.vec[2] - vec[2] * other.vec[1]);
    newV.push_back(vec[2] * other.vec[0] - vec[0] * other.vec[2]);
    newV.push_back(vec[0] * other.vec[1] - vec[1] * other.vec[0]);
    return PointN(newV);
  }
};

struct PointNHash {
  std::size_t operator()(const PointN& k) const {
    return std::hash<std::string>()(k.toString());
  }
};

static inline void rtrim(std::string &s);

std::vector<std::string> getInputVector();

std::vector<int> stoiVector(std::vector<std::string>& lines);

void fileToVector(const char* filename, std::vector<std::string>& lines);

std::vector<std::string> split(const std::string &text, std::string sep);

