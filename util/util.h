#include <string>
#include <list>
#include <vector>

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

static inline void rtrim(std::string &s);

std::vector<std::string> getInputVector();

std::vector<int> stoiVector(std::vector<std::string>& lines);

void fileToVector(const char* filename, std::vector<std::string>& lines);

std::vector<std::string> split(const std::string &text, std::string sep);

