#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <stdint.h>

constexpr int ADDRESS_SPACE = 1<<16;
constexpr int NUM_REGS = 8;
using std::cout;
using std::endl;
using std::vector;

class simulator{
public:
        bool stepOnce( void );
        bool doInst( uint16_t );
        vector<uint16_t> sliceMem ( uint16_t start, uint16_t stop );
        uint16_t sliceMem ( uint16_t addr );
        uint16_t getReg ( int number );
        bool setReg ( int number , uint16_t newVal);
        bool getPcsrBit ( char mnemonic );
        bool setPcsrBit ( char mnemonic , bool newVal);

private:
        vector<uint16_t> memory = vector<uint16_t>(ADDRESS_SPACE);
        vector<uint16_t> regs = vector<uint16_t>(NUM_REGS);
        uint16_t N, Z, P;
        uint16_t PC;
};
