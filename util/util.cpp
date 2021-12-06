#include "./util.h"
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <vector>

using namespace std;

static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}

vector<string> getInputVector() {
    vector<string> lines = {};
    fileToVector("in.txt", lines);
    return lines;
}

int stringToInt(string s) {
    return stoi(s);
}

vector<int> stoiVector(vector<string>& lines) {
    vector<int> ints = {};
    ints.resize(lines.size());
    transform(lines.begin(), lines.end(), ints.begin(), stringToInt);
    return ints;
}

void fileToVector(const char* filename, vector<string>& lines) {
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

vector<string> split(const string &text, string sep) {
  vector<string> tokens;
  size_t start = 0, end = 0;
  while ((end = text.find(sep, start)) != string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = end + sep.length();
  }
  tokens.push_back(text.substr(start));
  return tokens;
}