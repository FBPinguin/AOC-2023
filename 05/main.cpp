

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
class Solution {

public:
  std::vector<long> seeds{};
  std::vector<std::pair<long, long>> seedRanges{};
  std::vector<std::vector<std::tuple<long, long, long>>> maps{};

  std::vector<std::tuple<long, long, long>> getMap(std::ifstream &input) {
    std::string line;
    std::vector<std::tuple<long, long, long>> map;
    while (getline(input, line)) {
      if (line.empty()) {
        return map;
      }
      std::istringstream ss{line};
      long rstart, sstart, rlength;
      ss >> rstart >> sstart >> rlength;
      map.push_back(std::tuple<long, long, long>{rstart, sstart, rlength});
    }
    return map;
  }

  void init(std::ifstream &input) {

    std::string line;
    std::getline(input, line);
    std::stringstream ss{line};
    std::string word;
    do {
      ss >> word;
    } while (!word.ends_with(':'));
    while (ss >> word) {
      seeds.push_back(std::stod(word));
    }

    while (std::getline(input, line)) {
      if (line.ends_with(':')) {
        maps.push_back(getMap(input));
      }
    }
    return;
  }

  long calculate_solution_1() {
    long lowest{100000000000000};

    auto getDest = [&](std::vector<std::tuple<long, long, long>> map,
                       long seed) -> long {
      for (auto [rstart, sstart, range] : map) {
        if (seed >= sstart && seed < sstart + range) {
          return seed + rstart - sstart;
        }
      }
      return seed;
    };

    for (long seed : seeds) {
      for (auto map : maps) {
        seed = getDest(map, seed);
        // std::cout << seed << '\n';
      }
      lowest = std::min(seed, lowest);
    }
    return lowest;
  }

  long calculate_solution_2() {
    long lowest{100000000000000};

    auto getDest = [&](std::vector<std::tuple<long, long, long>> map,
                       std::vector<std::pair<long, long>> ranges)
        -> std::vector<std::pair<long, long>> {
      std::vector<std::pair<long, long>> newRanges;
      for (auto [start, end] : ranges) {
        std::vector<std::pair<long, long>> remaining = {{start, end}};
        std::vector<std::pair<long, long>> nextRemaining;

        for (auto [rstart, sstart, range] : map) {
          nextRemaining.clear();
          for (auto [rstart_curr, end_curr] : remaining) {
            if (end_curr < sstart || rstart_curr >= sstart + range) {
              // No overlap
              nextRemaining.push_back({rstart_curr, end_curr});
            } else {
              // Split range into before, overlap, and after
              if (rstart_curr < sstart) {
                nextRemaining.push_back({rstart_curr, sstart - 1});
              }
              long overlap_start = std::max(rstart_curr, sstart);
              long overlap_end = std::min(end_curr, sstart + range - 1);
              newRanges.push_back({overlap_start + rstart - sstart,
                                   overlap_end + rstart - sstart});
              if (overlap_end < end_curr) {
                nextRemaining.push_back({overlap_end + 1, end_curr});
              }
            }
          }
          remaining.swap(nextRemaining);
        }
        // Add any remaining unmapped ranges
        newRanges.insert(newRanges.end(), remaining.begin(), remaining.end());
      }
      return newRanges;
    };
    auto lowestRange = [](std::vector<std::pair<long, long>> vec) {
      long currLowest{100000000000000};
      for (auto [begin, end] : vec) {
        if (begin < currLowest) {
          currLowest = begin;
        }
      }
      return currLowest;
    };

    for (int Idx{0}; Idx < seeds.size(); Idx += 2) {
      seedRanges.push_back(
          std::pair<long, long>{seeds[Idx], seeds[Idx + 1] + seeds[Idx] - 1});
    }

    for (auto seed : seedRanges) {
      std::vector<std::pair<long, long>> currSeedRange{seed};
      for (auto map : maps) {
        currSeedRange = getDest(map, currSeedRange);
        // std::cout << seed << '\n';
        std::cout << "New Ranges:\n";
        for (auto &[start, end] : currSeedRange) {
          std::cout << start << " " << end << '\n';
        }
      }
      std::cout << "SEED COMPLETE\n";
      lowest = std::min(lowestRange(currSeedRange), lowest);
    }
    return lowest;
  }
};

int main(int argc, char *argv[]) {
  Solution solution{};
  std::ifstream file{"input.txt"};
  solution.init(file);
  std::cout << solution.calculate_solution_1() << '\n';
  std::cout << solution.calculate_solution_2() << '\n';
  return 0;
}
