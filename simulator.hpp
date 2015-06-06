#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <stdint>

constexpr int ADDRESS_SPACE 1<<16;
using std::cout;
using std::endl;
using std::vector;

class simulator{
public:

private:
  vector<uint16_t> memory(ADDRESS_SPACE);
  vector<uint16_t> regs(8);
  uint16_t N, Z, P;
  uint16_t PC; 
};