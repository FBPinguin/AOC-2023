#include <chrono>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>
#include <sstream>
#include <unordered_map>

class Solution{

public:

    enum condition {
        UNKNOWN,
        FIXED,
        BROKEN
    };


    typedef std::vector<condition> group;
    typedef std::vector<int> conditionMap;

    struct springMap{
        group groupMap;
        conditionMap condition;
    };





    int getGroupMap(group& groupMap, std::string& line) {
        for (int i{0}; i < line.size(); ++i) {
            char c = line[i];
            switch (c) {
                case '?':
                    groupMap.push_back(UNKNOWN);
                    break;
                case '.':
                    groupMap.push_back(FIXED);
                    break;
                case '#':
                    groupMap.push_back(BROKEN);
                    break;
                case ' ':
                    return i+1;
            }
        }
    }

    std::vector<springMap> springs;

    void init(std::ifstream& input){
        for (std::string line; getline(input, line);) {
            group groupMap{};
            conditionMap groupCondition{};
            size_t splitIndex = getGroupMap(groupMap, line);

            std::istringstream ss{line.substr(splitIndex)};
            char c;
            for (int word; ss >> word;) {
                groupCondition.push_back(word);
                ss >> c;
            }
            springs.push_back({groupMap, groupCondition});
        }
    }

    bool isValidSpring(springMap& spring) {
        int brokenAcc{0}, condMapIndx{0};
        for (condition c: spring.groupMap) {
            if (c == BROKEN) {
                ++brokenAcc;
            } else {
                if (brokenAcc == 0) {
                    continue;
                }
                if (condMapIndx >= spring.condition.size() || brokenAcc != spring.condition[condMapIndx]) {
                    return false;
                }
                condMapIndx++;
                brokenAcc = 0;
            }
        }

        if (brokenAcc > 0) {
            if (condMapIndx >= spring.condition.size() || brokenAcc != spring.condition[condMapIndx]) {
                return false;
            }
            condMapIndx++;
        }

        return condMapIndx == spring.condition.size();
    }

    bool isValidSpringUntill(springMap& spring, size_t index) {
        int brokenAcc{0}, condMapIndx{0};
        for (int i{0}; i < index;++i)  {
            condition c = spring.groupMap[i];
            if (c == BROKEN) {
                ++brokenAcc;
            } else {
                if (brokenAcc == 0) {
                    continue;
                }
                if (condMapIndx >= spring.condition.size() || brokenAcc != spring.condition[condMapIndx]) {
                    return false;
                }
                condMapIndx++;
                brokenAcc = 0;
            }
        }
        return true;
    }

    struct mapKey {
        int currentIndex;
        int numPlacedSprings;
        int condIndex;

        bool operator==(const mapKey& other) const {
            return condIndex == other.condIndex &&
                   currentIndex == other.currentIndex &&
                   numPlacedSprings == other.numPlacedSprings;
        }
    };

    struct mapKeyHash {
        std::size_t operator()(const mapKey& key) const {
            return (std::hash<int>{}(key.condIndex) ^ (std::hash<int>{}(key.currentIndex) << 1) ^ (std::hash<int>{}(key.numPlacedSprings) << 2));
        }
    };



    std::unordered_map<mapKey, long, mapKeyHash> cache;


    long numOfValidSpring(group& springList, conditionMap& conditions,int conditionIndex,int springListIndex, int currBrokenSpring, int totalBrokenSpring) {
        if (springList.size() == springListIndex) {
            if (conditions.size() == conditionIndex && currBrokenSpring == 0)
                {return 1;}
            if (conditions.size() == conditionIndex + 1 && conditions[conditionIndex] == currBrokenSpring)
                {return 1;}
            return 0;
        }

        mapKey key{(int)springListIndex,(int)totalBrokenSpring, conditionIndex};

        if (cache.contains(key)) {
            return cache[key];
        }

        condition c = springList[springListIndex];
        long acc{0};
        switch (c) {
            case UNKNOWN:
                // FIXED BRANCH
                if (conditionIndex < conditions.size() && conditions[conditionIndex] == currBrokenSpring) {
                    acc += numOfValidSpring(springList, conditions,  conditionIndex+1,springListIndex+1, 0, totalBrokenSpring);
                }
                else if (currBrokenSpring == 0) {
                    acc += numOfValidSpring(springList, conditions,  conditionIndex,springListIndex+1, 0, totalBrokenSpring);
                }
                // BROKEN BRANCH
                acc += numOfValidSpring(springList, conditions, conditionIndex, springListIndex+1, currBrokenSpring+1, totalBrokenSpring+1);
                break;
            case FIXED:
                if (conditionIndex < conditions.size() && conditions[conditionIndex] == currBrokenSpring) {
                    acc += numOfValidSpring(springList, conditions,  conditionIndex+1,springListIndex+1, 0, totalBrokenSpring);
                }
                else if (currBrokenSpring == 0) {
                    acc += numOfValidSpring(springList, conditions,  conditionIndex,springListIndex+1, 0, totalBrokenSpring);
                }
                break;
            case BROKEN:
                acc += numOfValidSpring(springList, conditions, conditionIndex, springListIndex+1, currBrokenSpring+1, totalBrokenSpring+1);
                break;
        }
        cache[key] = acc;
        return acc;


    }

    long calculate_solution_1(){
        long acc{0};
        for (auto spring : springs) {
            // cache =  {};
            cache.clear();
            acc += numOfValidSpring(spring.groupMap, spring.condition, 0, 0, 0, 0);
            // std::cout << acc << '\n';
        }

        return acc;
    }

    long calculate_solution_2(){
        long long acc{0};
        for (auto spring : springs) {
            auto newSpring = spring;
            for (int i = 0; i < 4; ++i) {
                newSpring.groupMap.push_back(UNKNOWN);
                newSpring.condition.insert(newSpring.condition.end(), spring.condition.begin(), spring.condition.end());
                newSpring.groupMap.insert(newSpring.groupMap.end(), spring.groupMap.begin(), spring.groupMap.end());
            }

            cache.clear();

            acc += numOfValidSpring(newSpring.groupMap, newSpring.condition, 0, 0, 0, 0);
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

    std::cout << "Solution 1 took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end1-start1) << '\n';
    std::cout << "Solution 2 took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end2-start2) << '\n';
    return 0;
}
