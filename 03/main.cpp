

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct value {
  bool activated;
  int value;
};

struct pair_hash {
  size_t operator() (const std::pair<int, int>& p) const {
      return ((size_t)p.first << 1) ^ p.second;
  }
};

int main(int argc, char *argv[]) {
  std::ifstream file{"input.txt"};
  std::string line;
  std::unordered_map<std::pair<int, int>, value *, pair_hash> values;
  std::vector<std::pair<int, int>> symbols;

  int lineNum{0};
  int currNum{0};
  int colNum{0};
  while (std::getline(file, line)) {

    value *curValue = (value *)malloc(sizeof(value));
    bool negNum{false};

    for (int col{0}; col < line.size(); ++col) {
      char c = line[col];
      if (isdigit((int)c)) {
        currNum = currNum * 10;
        currNum += c - '0';
        values[std::pair<int, int>{lineNum, col}] = curValue;
      } 
      else if (c != '.') {
        symbols.push_back(std::pair<int, int>{lineNum, col});
        if (currNum != 0) {
          curValue->value = currNum;
          curValue->activated = false;
          curValue = (value *)malloc(sizeof(value));
          currNum = 0;
        }
      } else {
        if (currNum != 0) {
          curValue->value = currNum;
          curValue->activated = false;
          curValue = (value *)malloc(sizeof(value));
          currNum = 0;
        }
      }
    }
    if (currNum != 0) {
          curValue->value = currNum;
          curValue->activated = false;
          curValue = (value *)malloc(sizeof(value));
          currNum = 0;
        }
    ++lineNum;
    colNum = line.size();
  }

  std::pair<int, int> neighbours[]{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
                                   {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  int acc{0};
  for (const auto &symbol : symbols) {
    for (const auto &adj : neighbours) {
      int row = symbol.first + adj.first;
      int col = symbol.second + adj.second;
      if (row < 0 || row > lineNum) {
        continue;
      }
      if (col < 0 || col > colNum) {
        continue;
      }

      std::pair<int, int> loc{row, col};
      if (values.contains(loc)) {
        value *val = values[loc];
        if (val->activated) {
          continue;
        }
        acc += val->value;
        val->activated = true;
      }
    }
  }

  std::cout << acc << '\n';
  return 0;
}
