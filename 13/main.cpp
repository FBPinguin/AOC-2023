#include <chrono>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

class Solution{

public:

  enum squareType {
    ASH=0,
    ROCK,
  };

  typedef std::vector<squareType> MapRow;
  typedef std::vector<MapRow> Map;

  std::vector<Map> allMaps{};

  void init(std::ifstream& input){
    Map currMap{};
    for (std::string line{}; getline(input, line);) {
      if (line.empty()) {
        allMaps.push_back(currMap);
        currMap.clear();
        continue;
      }
      MapRow currRow{};
      for (char c : line) {
        if (c == '#') {
          currRow.push_back(ROCK);
        }
        else if (c == '.') {
          currRow.push_back(ASH);
        }
        else {
          std::cout << c << " was not recognized in INIT.";
          exit(1);
        }
      }
      currMap.push_back(currRow);
    }
    allMaps.push_back(currMap);
  }

  // long getNumHoriz(const Map& map, const int index) {
  //   long acc{0};
  //   for (int i = 0; i < map[index].size(); ++i) {
  //     acc = acc | (static_cast<int>(map[index][i])<< i);
  //   }
  //   return acc;
  // }
  //
  // long getNumVert(const Map& map, const int index) {
  //   long acc{0};
  //   for (int i = 0; i < map.size(); ++i) {
  //     acc = acc | (static_cast<int>(map[i][index])<< i);
  //   }
  //   return acc;
  // }

  int differencesVert(const Map& map, int i1, int i2) {
    int acc{0};
    for (int i = 0; i < map.size(); ++i) {
      acc += map[i][i1] == map[i][i2] ? 0 : 1;
    }
    return acc;
  }
  int differencesHori(const Map& map, int i1, int i2) {
    int acc{0};
    for (int i = 0; i < map[0].size(); ++i) {
      acc += map[i1][i] == map[i2][i] ? 0 : 1;
    }
    return acc;
  }

  int checkMirrorVert(const Map& map, const int index) {
    size_t mapLength{map[0].size()};
    int diff{0};
    for (int i = 0; i <= index; ++i) {
      if (index+1+i >= mapLength) {
        return diff;
      }
      diff += differencesVert(map, index-i, index+1+i);
      // if (getNumVert(map, index-i) != getNumVert(map, index+1+i)) {
      //   return false;
      // }
    }
    return diff;
  }

  int checkMirrorHori(const Map& map, const int index) {
    size_t mapLength{map.size()};
    int diff{0};
    for (int i = 0; i <= index; ++i) {
      if (index+i+1 >= mapLength) {
        return diff;
      }
      diff += differencesHori(map, index-i, index+1+i);
      // if (getNumHoriz(map, index-i) != getNumHoriz(map, index+1+i)) {
      //   return false;
      // }
    }
    return diff;
  }

  int getScoreMap(const Map& map, int numOffDiff) {
    for (int i = 0; i < map.size()-1; ++i) {
      if (checkMirrorHori(map, i) == numOffDiff) {
        // std::cout << "HORI FOUND AT: " << i << '\n';
        return (i+1)*100;
      }
    }
    for (int i = 0; i < map[0].size()-1; ++i) {
      if (checkMirrorVert(map, i) == numOffDiff) {
        // std::cout << "VERt FOUND AT: " << i << '\n';
        return (i+1);
      }
    }
    return 0;
  }

  int calculate_solution_1(){
    int acc{0};

    for (const auto& map : allMaps) {
      acc += getScoreMap(map, 0);
    }

    return acc;
  }

  int calculate_solution_2(){
    int acc{0};

    for (const auto& map : allMaps) {
      acc += getScoreMap(map, 1);
    }

    return acc;
  }


};

int main (int argc, char *argv[]) {
  Solution solution{};
  std::ifstream file{"input.txt"};
  solution.init(file);
  auto start1 = std::chrono::_V2::high_resolution_clock::now();
  std::cout << "Solution 1: " << solution.calculate_solution_1() << '\n';
  auto end1= std::chrono::_V2::high_resolution_clock::now();

  auto start2 = std::chrono::_V2::high_resolution_clock::now();
  std::cout << "Solution 2: " << solution.calculate_solution_2() << '\n';
  auto end2 = std::chrono::_V2::high_resolution_clock::now();

  std::cout << "Solution 1 took: " << std::chrono::duration_cast<std::chrono::microseconds>(end1-start1) << '\n';
  std::cout << "Solution 2 took: " << std::chrono::duration_cast<std::chrono::microseconds>(end2-start2) << '\n';
  return 0;
}
