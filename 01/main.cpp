

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

int getNums(std::string_view line) {
  int nums[2];
  int lastdigit = -1;
  for (char c : line) {
    if (std::isdigit((int)c)) {
      if (lastdigit == -1) {
        nums[0] = std::atoi(&c);
      }
      lastdigit = std::atoi(&c);
    }
  }
  nums[1] = lastdigit;
  return 10 * nums[0] + nums[1];
}

int main(int argc, char *argv[]) {
  std::ifstream MyFile;
  MyFile.open("input.txt");
  std::string buffer;
  int acc{0};

  if (!MyFile.is_open()) {
    std::cerr << "Could not open file!\n";
    return 1;
  }

  while (std::getline(MyFile, buffer)) {
    acc += getNums(buffer);
  }
  MyFile.close();
  std::cout << acc << '\n';
  return 0;
}
