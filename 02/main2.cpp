

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
  int maxNum[3];
  while (std::getline(file, buffer)) {
    int bag[3]{0,0,0};
    std::stringstream line(buffer);
    while (line >> word) {
      try {
        currNum = std::stoi(word);
      } catch (std::invalid_argument) {
      }
      
      if (word.starts_with("green")) {
        if (currNum > bag[0]) {
          bag[0] = currNum;
        }
      } else if (word.starts_with("red")) {
        if (currNum > bag[1]) {
          bag[1] = currNum;
        }
      } else if (word.starts_with("blue")) {
        if (currNum > bag[2]) {
          bag[2] = currNum;
        }
      }
    }
    correct += bag[0]*bag[1]*bag[2];

    
  }
  std::cout << correct << '\n';
  return 0;
}
