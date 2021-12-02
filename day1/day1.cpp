#include "../util/util.h"
#include <iostream>

using namespace std;

int main() {
    list<string> lines = getInputList();
    int nums[lines.size()];
    int i = 0;
    for (string const &s: lines) {
        nums[i++] = stoi(s);
    }
    
    int p1 = 0;
    int p2 = 0;
    for (i = 1; i < lines.size(); i++) {
        if (nums[i - 1] < nums[i]) p1++;
        if (i >= 3 && nums[i - 3] < nums[i]) p2++;
    }

    cout << "Part 1: " << p1 << "\n";
    cout << "Part 2: " << p2 << "\n";
    return 0;
}
