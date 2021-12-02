#include "../util/util.h"
#include <iostream>

using namespace std;

int main() {
    list<string> lines = getInputList();
    int depth = 0;
    int distance = 0;
    int depth2 = 0;
    int aim = 0;
    for (string const &s: lines) {
        string dir = s.substr(0, s.find(" "));
        int mag = stoi(s.substr(s.find(" ") + 1, s.length()));
        if (dir == "forward") {
            distance += mag;
            depth2 += aim * mag;
        } else if (dir == "down") {
            depth += mag;
            aim += mag;
        } else if (dir == "up") {
            depth -= mag;
            aim -= mag;
        } else {
            cout << "unknown prefix: " << dir << "\n";
        }
    }

    cout << "Part 1: " << depth * distance << "\n";
    cout << "Part 2: " << depth2 * distance << "\n";
    return 0;
}