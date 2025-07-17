#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>
#include <sstream>
#include <unordered_set>

class Solution{

public:
    std::vector<std::array<long, 4>> galaxies;

    void init(std::ifstream& input){
        // std::string line;

        std::unordered_set<int> rowOccupied;
        std::unordered_set<int> colOccupied;
        int lineC{0};
        for (auto&& line : std::views::istream<std::string>(input)) {
            for (int colC{0}; const char c : line) {
                if (c == '#') {
                    galaxies.push_back({lineC, colC});
                    rowOccupied.insert(lineC);
                    colOccupied.insert(colC);
                }
                colC++;
            }
            lineC++;
        }

        auto rowFilter = std::ranges::views::filter([&](int i){return !rowOccupied.contains(i);});
        auto colFilter = std::ranges::views::filter([&](int i){return !colOccupied.contains(i);});




        for (int i : std::views::iota(0, lineC) | rowFilter) {
            for (int j = 0; j < galaxies.size(); ++j) {
                if (galaxies[j][0] > i) {
                    galaxies[j][2] += 1;
                }
            }
        }

        for (int i : std::views::iota(0, lineC) | colFilter) {
            for (int j = 0; j < galaxies.size(); ++j) {
                if (galaxies[j][1] > i) {
                    galaxies[j][3] += 1;
                }
            }
        }

    }

    long calculateTotalDistance(int extraDistance) {
        long acc{0};

        for (int i = 0; i < galaxies.size(); ++i) {
            for (int j = i+1; j < galaxies.size(); ++j) {
                long extradx = std::abs(galaxies[i][2]*extraDistance-galaxies[j][2]*extraDistance);
                long extrady = std::abs(galaxies[i][3]*extraDistance-galaxies[j][3]*extraDistance);
                long dx = std::abs(galaxies[i][0]-galaxies[j][0]);
                long dy = std::abs(galaxies[i][1]-galaxies[j][1]);
                acc += extradx + extrady + dx + dy;
            }
        }

        return acc;

    }

    long calculate_solution_1(){


        return calculateTotalDistance(1);
    }

    long calculate_solution_2(){

        return calculateTotalDistance(1000000-1);
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
