#include "../util/util.h"
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Score {
  int score;
  int numTurns;
};

Score getScore(vector<vector<int>>& board, vector<int>& draws) {
  vector<set<int>> setsToWin;
  set<int> totalSet;
  for (int r = 0; r < 5; r++) {
    set<int> newSet;
    for (int c = 0; c < 5; c++) {
      newSet.insert(board[r][c]);
      totalSet.insert(board[r][c]);
    }
    setsToWin.push_back(newSet);
  }
  for (int c = 0; c < 5; c++) {
    set<int> newSet;
    for (int r = 0; r < 5; r++) {
      newSet.insert(board[r][c]);
    }
    setsToWin.push_back(newSet);
  }
  for (int i = 0; i < draws.size(); i++) {
    int draw = draws[i];
    totalSet.erase(draw);
    bool done = false;
    for (set<int>& s: setsToWin) {
      s.erase(draw);
      if (s.size() == 0) done = true;
    }
    if (done) {
      int total = 0;
      for (int remaining: totalSet) total += remaining;
      return {total * draw, i + 1};
    }
  }
  cout << "Error! Board could not be scored.\n";
  exit(1);
}

int main() {
  vector<string> lines = getInputVector();
  vector<string> drawStrings = split(lines[0], ",");
  vector<int> draws = stoiVector(drawStrings);
  vector<vector<vector<int>>> boards;
  for (int i = 2; i < lines.size(); i += 6) {
    vector<vector<int>> board;
    for (int j = 0; j < 5; j++) {
      vector<int> line;
      for (int k = 0; k < lines[i].size(); k += 3) {
        line.push_back(stoi(lines[i + j].substr(k, 2)));
      }
      board.push_back(line);
    }
    boards.push_back(board);
  }
  Score fastScore = {0, (int) draws.size() + 1};
  Score slowScore = {0, 0};
  for (vector<vector<int>> board: boards) {
    Score newScore = getScore(board, draws);
    if (newScore.numTurns < fastScore.numTurns) {
      fastScore = newScore;
    }
    if (newScore.numTurns > slowScore.numTurns) {
      slowScore = newScore;
    }
  }
  cout << "Part 1: " << fastScore.score << "\n";
  cout << "Part 2: " << slowScore.score << "\n";
  return 0;
}
