#include <string>
#include <list>
#include <vector>

using namespace std;

static inline void rtrim(string &s);

vector<string> getInputVector();

vector<int> stoiVector(vector<string>& lines);

void fileToVector(const char* filename, vector<string>& lines);

vector<string> split(const string &text, string sep);

