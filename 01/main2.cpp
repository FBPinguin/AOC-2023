

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

struct returnArg {
  int num;
  size_t numLen;
};


void getStringNum(returnArg &ra, std::string_view line) {
  std::string arg[]{"one", "two",   "three", "four", "five",
                    "six", "seven", "eight", "nine"};
  for (int i = 0; i < std::size(arg); ++i){
    if (line.starts_with(arg[i])){
      ra.num = i+1;
      ra.numLen = std::size(arg[i]);
      return;
    }
  }
  ra.num = -1;
  ra.numLen = -1;
  return;
}

int getNums(std::string_view line) {
  int nums[2];
  int lastdigit = -1;
  char c;
  returnArg arg;
  for (;std::size(line) > 0; line.remove_prefix(1)) {

    c = line[0];
    getStringNum(arg, line);
    if (arg.num > -1){
      if (lastdigit == -1){
        nums[0] = arg.num;
      }
      lastdigit = arg.num;
      continue;
    }
    if (std::isdigit((int)c)) {
      if (lastdigit == -1) {
        nums[0] = std::atoi(&c);
      }
      lastdigit = std::atoi(&c);
    }
  }
  nums[1] = lastdigit;
  std::cout << nums[0] << " " << nums[1] << '\n';
  return 10 * nums[0] + nums[1];
}

int main(int argc, char *argv[]) {
  std::ifstream MyFile("input.txt");
  std::string buffer;
  int acc{0};

  if (!MyFile.is_open()) {
    std::cerr << "Could not open file!\n";
    return 1;
  }

  while (std::getline(MyFile, buffer)) {
    int curnum = getNums(buffer);
    acc += curnum;
  }
  MyFile.close();
  std::cout << acc << '\n';
  return 0;
}
