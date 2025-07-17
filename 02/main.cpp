

#include <cstdio>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>

int red = 12;
int green = 13;
int blue = 14;
int correct = 0;

int main(int argc, char *argv[]) {
  std::ifstream file("input.txt");
  if (!file.is_open()) {
    perror("file did not open");
    exit(1);
  }
  std::string buffer;
  std::string word;
  int currNum;
  int currGame;
  while (std::getline(file, buffer)) {
    bool correctGame = true;
    std::stringstream line(buffer);
    while (line >> word) {
      try {
        currNum = std::stoi(word);
      } catch (std::invalid_argument) {
      }
      if (word.starts_with("Game")) {
        line >> word;
        currGame = std::stoi(word);
      }
      if (word.starts_with("green")) {
        if (currNum > green) {
          correctGame = false;
          break;
        }
      } else if (word.starts_with("red")) {
        if (currNum > red) {
          correctGame = false;
          break;
        }
      } else if (word.starts_with("blue")) {
        if (currNum > blue) {
          correctGame = false;
          break;
        }
      }
    }
    if (correctGame) {
      correct += currGame;
      correctGame = true;
    }
  }
  std::cout << correct << '\n';
  return 0;
}
