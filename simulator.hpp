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

/**
 * @brief Basic LC3 Simulator Class
 * @details This class is exposed to the Python Interface,
 * CLI, and GUI
 * 
 */
class simulator{
public:
        using MEM_type = vector<uint16_t>;
        vector<uint16_t> memory = vector<uint16_t>(ADDRESS_SPACE);
        bool stepN( int cycles );
        bool doInst( uint16_t );
        vector<uint16_t> sliceMem ( uint16_t start, uint16_t stop );
        uint16_t getReg ( int number );
        bool setReg ( int number , uint16_t newVal);
        bool getPcsrBit ( char mnemonic );
        bool setPcsrBit ( char mnemonic , bool newVal);
        uint16_t getPC(void);
        bool setPC(uint16_t);

private:
        vector<uint16_t> regs = vector<uint16_t>(NUM_REGS);
        uint16_t N, Z, P, S;
        uint16_t PC;
        void setNZP( uint16_t );
        uint16_t memRead( uint16_t addr );
        void memWrite( uint16_t addr, uint16_t newVal );
};
