#include <chrono>
#include <complex>
#include <cstdint>
#include <future>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include "simulator.hpp"
#include "gtest/gtest.h"
#include "LC3Helper.h"

simulator sim2;

TEST(CheckLD, AllPositive) {
        sim2.memory[0x3002] = 0xDEAD;
        sim2.setPC(0x3000 - 1);

        sim2.doInst(LD | SETDR(1) | 0x2);
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0x3002]);

        sim2.memory[0x3020] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LD | SETDR(2) | 0x20);
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0x3020]);

        sim2.memory[0x30FF] = 0xCAFE;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LD | SETDR(3) | 0xFF);
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0x30FF]);
}

TEST(CheckLD, ALLNegative) {
        sim2.memory[0x3000 - 0x2] = 0xDEAD;
        sim2.setPC(0x3000 - 1);

        sim2.doInst(LD | SETDR(1) | (-0x2 & 0x1FF));
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0x3000 - 0x2]);

        sim2.memory[0x3000 - 0x20] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LD | SETDR(2) | (-0x20 & 0x1FF));
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0x3000 - 0x20]);

        sim2.memory[0x3000 - 0x100] = 0xCAFE;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LD | SETDR(3) | (-0x100 & 0x1FF));
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0x3000 - 0x100]);
}
