#include <bitset>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {



    struct Map {
        std::vector<std::pair<int,int>> roundRocks;
        std::vector<std::vector<int>> rockVert{{}};
        std::vector<std::vector<int>> rockHori{{}};
        size_t height{0}, width{0};

        friend std::istream& operator>>(std::istream& s, Map& map) {
            int row{0};
            for (std::string line{}; getline(s, line);) {
                for (int i = 0; i < line.length(); ++i) {
                    if (map.rockVert.size() == i) {
                        map.rockVert.emplace_back();
                    }
                    char c = line.at(i);
                    if (c == '#') {
                        map.rockVert[i].push_back(row);
                        map.rockHori[row].push_back(i);
                    }
                    else if (c == 'O') {
                        map.roundRocks.emplace_back(row, i);
                    }
                }
                map.width = line.length();
                map.rockHori.emplace_back();
                row++;

            }
            map.height = static_cast<size_t>(row);
            return s;
        }
    };

    class VMap {
    public:
        std::size_t operator()(const std::vector<std::pair<int, int>>& vec) const {
            std::size_t seed = 0;
            for (const auto& p : vec) {
                seed ^= std::hash<int>{}(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                seed ^= std::hash<int>{}(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

    Map map;

public:
    void init(std::istream& input){
        input >> map;
    }

    int calculate_solution_1(std::istream& input) {
        size_t nCols{};
        std::vector<int> lastRock;
        std::vector<int> points;
        int row{0};
        for (std::string line{}; getline(input, line);) {
            nCols = line.length();
            for (int i = 0; i < line.length(); ++i) {
                char c = line.at(i);
                if (i == lastRock.size()) {
                    lastRock.push_back(0);
                }
                if (c == '#')
                    lastRock[i] = row+1;
                else if (c == 'O') {
                    points.push_back(lastRock[i]);
                    lastRock[i]++;
                }
            }
            row++;

        }
        int acc{0};
        for (const auto& point : points) {
            acc += row - point;
        }
        return acc;
    }

    int findEmptyNorth(std::pair<int,int>& curPos) {
        int col = curPos.second;
        int curRow = curPos.first;
        auto rockCol = map.rockVert[col] | std::views::reverse;
        auto p = std::ranges::find_if(rockCol.begin(),rockCol.end(),[&](int i){return i < curRow;});
        int pos = 0;
        if (p != rockCol.end()) {
            pos = *p+1;
        }
        if (pos == curRow) {
            return pos;
        }
        for (int i{pos}; i < curRow; ++i) {
            if (std::ranges::find(map.roundRocks, std::pair{i, col}) == map.roundRocks.end()){
                return i;
            }
        }
        return curRow;
    }

    int findEmptySouth(std::pair<int,int>& curPos) {
        int col = curPos.second;
        int curRow = curPos.first;
        auto rockCol = map.rockVert[col];
        auto p = std::ranges::find_if(rockCol.begin(),rockCol.end(),[&](int i){return i > curRow;});
        int pos = map.height-1;
        if (p != rockCol.end()) {
            pos = *p-1;
        }
        if (pos == curRow) {
            return pos;
        }
        for (int i{pos}; i > curRow; --i) {
            if (std::ranges::find(map.roundRocks, std::pair{i, col}) == map.roundRocks.end()){
                return i;
            }
        }
        return curRow;
    }

    int findEmptyEast(std::pair<int,int>& curPos) {
        int col = curPos.second;
        int curRow = curPos.first;
        auto rockCol = map.rockHori[curRow];
        auto p = std::ranges::find_if(rockCol.begin(),rockCol.end(),[&](int i){return i > col;});
        int pos = map.width-1;
        if (p != rockCol.end()) {
            pos = *p-1;
        }
        if (pos == col) {
            return pos;
        }
        for (int i{pos}; i > col; --i) {
            if (std::ranges::find(map.roundRocks, std::pair{curRow, i}) == map.roundRocks.end()){
                return i;
            }
        }
        return col;
    }

    int findEmptyWest(std::pair<int,int>& curPos) {
        int col = curPos.second;
        int curRow = curPos.first;
        auto rockCol = map.rockHori[curRow] | std::views::reverse;
        auto p = std::ranges::find_if(rockCol.begin(),rockCol.end(),[&](int i){return i < col;});
        int pos = 0;
        if (p != rockCol.end()) {
            pos = *p+1;
        }
        if (pos == col) {
            return pos;
        }
        for (int i{pos}; i < col; ++i) {
            if (std::ranges::find(map.roundRocks, std::pair{curRow, i}) == map.roundRocks.end()){
                return i;
            }
        }
        return col;
    }

    void cycleMap() {
        for (auto& rock : map.roundRocks) {
            rock.first = findEmptyNorth(rock);
        }
        for (auto& rock : map.roundRocks) {
            rock.second = findEmptyWest(rock);
        }
        for (auto& rock : map.roundRocks) {
            rock.first = findEmptySouth(rock);
        }
        for (auto& rock : map.roundRocks) {
            rock.second = findEmptyEast(rock);
        }
        return;
    }

    int calculateMap() {
        return std::accumulate(map.roundRocks.begin(), map.roundRocks.end(), 0,
            [&](int acc, std::pair<int,int>& rock){return acc + map.height - rock.first;});
    }




    int calculate_solution_2(){
        std::unordered_map<std::vector<std::pair<int,int>>, int, VMap> seen{};

        int loops{1000000000};
        for (int i = 0; i < loops; ++i) {
            cycleMap();
            std::sort(map.roundRocks.begin(), map.roundRocks.end()); // critical!
            if (seen.contains(map.roundRocks)) {
                if (i-seen[map.roundRocks]==0) return calculateMap();
                loops = (loops - i - 1) %(i-seen[map.roundRocks]);
                break;
            }
            else {
                seen[map.roundRocks] = i;
            }

        }
        for (int i = 0; i < loops; ++i) {
            cycleMap();
        }
        return calculateMap();
    }
};

int main (int argc, char *argv[]) {
    Solution solution{};
    std::ifstream file{"input.txt"};
    solution.init(file);

    file.clear();
    file.seekg(0);

    auto start1 = std::chrono::_V2::high_resolution_clock::now();
    std::cout << "Solution 1: " << solution.calculate_solution_1(file) << '\n';
    auto end1= std::chrono::_V2::high_resolution_clock::now();


    auto start2 = std::chrono::_V2::high_resolution_clock::now();
    std::cout << "Solution 2: " << solution.calculate_solution_2() << '\n';
    auto end2 = std::chrono::_V2::high_resolution_clock::now();

    std::cout << "Solution 1 took: " << std::chrono::duration_cast<std::chrono::microseconds>(end1-start1) << '\n';
    std::cout << "Solution 2 took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end2-start2) << '\n';
    return 0;
}