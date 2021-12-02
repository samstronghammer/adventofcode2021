#include "./util.h"
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm> 

using namespace std;

static inline void rtrim(std::string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

list<string> getInputList() {
    list<string> lines = {};
    fileToList("in.txt", lines);
    return lines;
}

int stringToInt(string s) {
    return stoi(s);
}

list<int> stringListToIntList(list<string> lines) {
    list<int> ints = {};
    ints.resize(lines.size());
    transform(lines.begin(), lines.end(), ints.begin(), stringToInt);
    return ints;
}

void fileToList(const char* filename, list<string>& lines) {
    lines.clear();
    ifstream file(filename);
    if (!file) {
        cout << "File '" << filename << "' does not exist.\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        rtrim(line);
        lines.push_back(line);
    }
}