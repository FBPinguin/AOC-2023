#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <set>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>


class Solution {
public:


  enum dir {
    up,
    down,
    left,
    right
  };



  struct Direction {
    std::vector<dir> dirs;
  };

  Direction dirMap(char dir) {
    switch (dir) {
      case '.':
        return Direction{};
      case '|':
        return Direction{{up,down}};
      case '-':
        return Direction{{left,right}};
      case 'L':
        return Direction{{up,right}};
      case 'J':
        return Direction{{left,up}};
      case '7':
        return Direction{{down,left}};
      case 'F':
        return Direction{{down,right}};
      case 'S':
        return Direction{{up,down,left,right}};
    }
  }

  std::vector<std::vector<Direction>> map;
  std::vector<std::vector<char>> charMap;
  std::vector<std::pair<int,int>> corners;
  std::pair<int, int> startLoc;
  void init(std::ifstream& input){
    std::string line;
    int lineC{0};
    while (getline(input, line)) {
      int colC{0};
      std::vector<Direction> mapLine;
      std::vector<char> charmapLine;
      auto words = std::istringstream(line);

      for  (auto c : std::views::istream<char>(words)) {
        if (c == 'S') {
          startLoc = {lineC, colC};
        }
        mapLine.push_back(dirMap(c));
        charmapLine.push_back(c);

        colC++;
      }
      lineC++;
      map.push_back(mapLine);
      charMap.push_back(charmapLine);
    }

  }


  void takeStep(dir Direction, std::pair<int,int>& loc) {
    switch (Direction){
      case up:
        loc.first -= 1;
        break;
      case down:
        loc.first += 1;
        break;
      case left:
        loc.second -= 1;
        break;
      case right:
        loc.second += 1;
        break;
    }
  }

  struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1,T2>& p) const {
      return std::hash<T1>()(p.first) ^ (std::hash<T2>()(p.second) << 1);
    }
  };

  dir reverseDir(dir d) {
    switch (d) {
      case up: return down;
      case down: return up;
      case left: return right;
      case right: return left;
    }
    return up;
  }

  bool locOutOfBounds(std::pair<int,int>& loc) {
    return loc.first < 0 || loc.second < 0 || loc.first >= map.size() || loc.second >= map[loc.first].size();
  }

  void followDir(std::unordered_map<std::pair<int,int>, int, pair_hash>& values, std::unordered_set<std::pair<int,int>, pair_hash
>& history,int stepCount,dir lastStep,std::pair<int,int> loc, bool saveCorners = false) {
    if (history.contains(loc) || locOutOfBounds(loc)) {
      return;
    }
    if (!values.contains(loc) || values[loc] > stepCount) {
      values[loc] = stepCount;
    }
    if (saveCorners && charMap[loc.first][loc.second] != '-' &&  charMap[loc.first][loc.second] != '|') {
      corners.push_back(loc);
    }
    history.insert(loc);
    auto nextDir = *std::ranges::find_if(map[loc.first][loc.second].dirs, [&](dir Dir){return Dir != reverseDir(lastStep);});
    takeStep(nextDir, loc);
    stepCount++;
    followDir(values, history, stepCount, nextDir, loc, saveCorners);
  }

  void startFollowDir(std::unordered_map<std::pair<int,int>, int, pair_hash>& values, dir Direction, std::pair<int,int> loc,bool saveCorners = false) {
    std::unordered_set<std::pair<int,int>, pair_hash> history{loc};
    if (saveCorners) {
      corners.push_back(loc);
    }
    takeStep(Direction, loc);
    if (locOutOfBounds(loc)) {
      return;
    }
    if (!std::ranges::any_of(map[loc.first][loc.second].dirs, [&](dir Dir){return Dir == reverseDir(Direction);})) {
      return;
    }
    followDir(values, history, 1, Direction, loc, saveCorners);
  }
  std::unordered_map<std::pair<int,int>, int, pair_hash> values;
  int calculate_solution_1() {
    startFollowDir(values, up, startLoc);
    startFollowDir(values, down, startLoc);
    startFollowDir(values, left, startLoc,true);
    startFollowDir(values, right, startLoc);

    int acc{0};
    for (auto [key, value] : values) {
      if (value > acc) {
        acc = value;
      }
    }

    return acc;
  }

  int calculate_solution_2(){
    // std::vector<std::pair<int,int>> corners{{1,6},{3,1},{7,2},{4,4},{8,5}};

    int area{0};
    for (int i = 0; i < corners.size(); ++i) {
      int ax{corners[i].first}, ay{corners[i].second}, bx{corners[(i+1)%corners.size()].first}, by{corners[(i+1)%corners.size()].second};
      int dotProduct = ax*by-ay*bx;
      area += dotProduct;
    }

    int ans{abs(area)/2  -static_cast<int>(values.size())/2};


    return ans;
  }


};

int main (int argc, char *argv[]) {
  Solution solution{};
  std::ifstream file{"input.txt"};
  solution.init(file); 
  std::cout << "Solution 1: " << solution.calculate_solution_1() << '\n';
  std::cout << "Solution 2: " << solution.calculate_solution_2() << '\n';
  return 0;
}
