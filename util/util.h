#include <string>
#include <list>

using namespace std;

static inline void rtrim(std::string &s);

list<string> getInputList();

list<int> stringListToIntList(list<string> lines);

void fileToList(const char* filename, list<string>& lines);

