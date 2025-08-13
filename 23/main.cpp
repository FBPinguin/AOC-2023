

#include <chrono>
#include <fstream>
#include <iostream>

#include "Solution.h"


int main (int argc, char *argv[]) {
  Solution solution{};
  std::ifstream file{"input.txt"};

  solution.init(file);

  auto start1 = std::chrono::_V2::high_resolution_clock::now();
  // std::cout << "Solution 1: " << solution.calculate_solution_1() << '\n';
  auto end1= std::chrono::_V2::high_resolution_clock::now();

  auto start2 = std::chrono::_V2::high_resolution_clock::now();
  std::cout << "Solution 2: " << solution.calculate_solution_2() << '\n';
  auto end2 = std::chrono::_V2::high_resolution_clock::now();

  std::cout << "Solution 1 took: " << std::chrono::duration_cast<std::chrono::microseconds>(end1-start1) << '\n';
  std::cout << "Solution 2 took: " << std::chrono::duration_cast<std::chrono::microseconds>(end2-start2) << '\n';
  return 0;
}
