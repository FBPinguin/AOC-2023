

#include <algorithm>
#include <array>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

class Solution{
  enum cardLabel {
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    T,
    J,
    Q,
    K,
    A
  };
  /**
   *THIS IS USED FOR PART 2
   */
  // enum cardLabel {
  //   J,
  //   two,
  //   three,
  //   four,
  //   five,
  //   six,
  //   seven,
  //   eight,
  //   nine,
  //   T,
  //   Q,
  //   K,
  //   A
  // };

  enum handType {
    HighCard=0,
    OnePair,
    TwoPair,
    ThreeOAK,
    FullHouse,
    FourOAK,
    FiveOAK,
  };

  cardLabel returnLabel(char s) {
    switch (s) {
      case '2': return two;
      case '3': return three;
      case '4': return four;
      case '5': return five;
      case '6': return six;
      case '7': return seven;
      case '8': return eight;
      case '9': return nine;
      case 'T': return T;
      case 'J': return J;
      case 'Q': return Q;
      case 'K': return K;
      case 'A': return A;
      default:
        std::cerr << std::format("{} is not a label", s);
        exit(1);
    }
  }

  handType handValue(std::array<cardLabel,5>& hand) {
    auto contains = [](std::pmr::unordered_map<cardLabel, int>& count, int i) {
      for (auto& [key, value] : count) {
        if (value == i) {
          return true;
        }
      }
      return false;
    };

    std::pmr::unordered_map<cardLabel, int> count;
    for (cardLabel& label : hand) {
      count[label] += 1;
    }
    int max{0};
    for (auto& [key, val] : count) {
      if (val > max) {
        max = val;
      }
    }

    if (max==5) {
      return FiveOAK;
    }
    if (max==4) {
      return FourOAK;
    }
    if (max == 3 && contains(count, 2)) {
      return FullHouse;
    }
    if (max == 3) {
      return ThreeOAK;
    }
    int numTwos{0};
    for (auto& [key, val] : count) {
      if (val == 2) {
        numTwos++;
      }
    }
    if (numTwos == 2) {
      return TwoPair;
    }
    if (numTwos == 1) {
      return OnePair;
    }
    return HighCard;

  }


  struct Play {
    std::array<cardLabel, 5> hand{};
    int bid{};
    handType value;
  };

  std::vector<Play> Plays{};

public:
  void init(std::ifstream& input){
    std::string line;
    while (getline(input, line)) {
      std::array<cardLabel, 5> hand{};
      int loc{0};
      for (; loc < 5; ++loc) {
        hand[loc] = returnLabel(line[loc]);
      }
      ++loc;
      int value = stoi(line.substr(loc));
      Plays.push_back(Play{hand, value, handValue(hand)});
    }


  }
  
  int calculate_solution_1(){
    std::sort(Plays.begin(), Plays.end(), [](Play play1, Play play2) {
      if (play1.value == play2.value) {
        for (int i{0}; i < 5; ++i) {
          if (play1.hand[i] != play2.hand[i]) {
            return play1.hand[i] < play2.hand[i];
          }
        }
      }
      return play1.value < play2.value;
    });
    int acc{0};
    int mult{1};
    for (auto& play : Plays) {
      acc += mult * play.bid;
      ++mult;
    }
    return acc;
  }
  handType handValueP2(std::array<cardLabel,5>& hand) {
    auto countHand = [](std::pmr::unordered_map<cardLabel, int>& count, int i) {
      int acc{0};
      for (auto& [key, value] : count) {
        if (value == i) {
          ++acc;
        }
      }
      return acc;
    };

    int jokerCount{0};

    std::pmr::unordered_map<cardLabel, int> count;
    for (cardLabel& label : hand) {
      if (label == J) {
        jokerCount++;
        continue;
      }
      count[label] += 1;
    }
    int max{0};
    for (auto& [key, val] : count) {
      if (val > max) {
        max = val;
      }
    }

    if (max>=5-jokerCount) {
      return FiveOAK;
    }
    if (max>=4-jokerCount) {
      return FourOAK;
    }
    if (max >= 3-jokerCount && (jokerCount>0 ? countHand(count, 2) > 1 : countHand(count, 2) >= 1)) {
      return FullHouse;
    }
    if (max >= 3-jokerCount) {
      return ThreeOAK;
    }
    int numTwos{0};
    for (auto& [key, val] : count) {
      if (val == 2) {
        numTwos++;
      }
    }
    if (numTwos >= 2 - jokerCount) {
      return TwoPair;
    }
    if (numTwos >= 1 - jokerCount) {
      return OnePair;
    }
    return HighCard;

  }
  void recalculateValues() {
    for (Play& play : Plays) {
      play.value = handValueP2(play.hand);
    }
  };

  int calculate_solution_2(){
    recalculateValues();
    std::ranges::sort(Plays, [](const Play &play1, const Play &play2) {
      if (play1.value == play2.value) {
        for (int i{0}; i < 5; ++i) {
          if (play1.hand[i] != play2.hand[i]) {
            return play1.hand[i] < play2.hand[i];
          }
        }
      }
      return play1.value < play2.value;
    });
    std::cout << "\nNEXT:\n";
    for (const Play& play: Plays) {
      std::cout << play.bid << " "<< play.value << '\n';
    }
    std::cout << '\n';

    int acc{0};
    int mult{1};
    for (auto& play : Plays) {
      acc += mult * play.bid;
      ++mult;
    }
    return acc;
    return 1;
  }
private:


};

int main (int argc, char *argv[]) {
  Solution solution{};
  std::ifstream file{"input.txt"};
  solution.init(file); 
  std::cout << solution.calculate_solution_1() << '\n';
  std::cout << solution.calculate_solution_2() << '\n';
  return 0;
}
