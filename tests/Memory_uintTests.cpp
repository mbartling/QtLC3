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

TEST(CheckLDR, AllPositive) {

        sim2.memory[0x3002] = 0xDEAD;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(0,0x3000);
        sim2.doInst(LDR | SETDR(1) | SETSR1(0) | 0x2);
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0x3002]);

        sim2.memory[0x3010] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(0,0x3000);
        sim2.doInst(LDR | SETDR(2) | SETSR1(0) | 0x10);
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0x3020]);

        sim2.memory[0x301F] = 0xCAFE;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(0,0x3000);
        sim2.doInst(LDR | SETDR(3) | SETSR1(0) | 0x1F);
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0x30FF]);
}

TEST(CheckLDR, ALLNegative) {
        sim2.memory[0x3000 - 2] = 0xDEAD;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LDR | SETDR(1) | (-0x2 & 0x3F));
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0x3000 - 0x2]);

        sim2.memory[0x3000 - 0x10] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LDR | SETDR(2) | (-0x10 & 0x3F));
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0x3000 - 0x10]);

        sim2.memory[0x3000 - 0x20] = 0xCAFE;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LDR | SETDR(3) | (-0x20 & 0x3F));
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0x3000 - 0x20]);
}

TEST(CheckLDI, AllPositive) {

        sim2.memory[0x3002] = 0xDEAD;
        sim2.memory[0xDEAD] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LDI | SETDR(1) | 0x2);
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0xDEAD]);

        sim2.memory[0x3020] = 0xBEEF;
        sim2.memory[0xBEEF] = 0xF000;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LDI | SETDR(2) | 0x20);
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0xBEEF]);

        sim2.memory[0x30FF] = 0xCAFE;
        sim2.memory[0xCAFE] = 0x64F0;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LDI | SETDR(3) | 0xFF);
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0xCAFE]);
}

TEST(CheckLDI, ALLNegative) {

        sim2.memory[0x3000 - 0x2] = 0xDEAD;
        sim2.memory[0xDEAD] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LDI | SETDR(1) | (-0x2 & 0x1FF));
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0xDEAD]);

        sim2.memory[0x3000 - 0x20] = 0xBEEF;
        sim2.memory[0xBEEF] = 0xF000;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LDI | SETDR(2) | (-0x20 & 0x1FF));
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0xBEEF]);

        sim2.memory[0x3000 - 0x100] = 0xCAFE;
        sim2.memory[0xCAFE] = 0x64F0;
        sim2.setPC(0x3000 - 1);
        sim2.doInst(LDI | SETDR(3) | (-0x100 & 0x1FF));
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0xCAFE]);
}

TEST(CheckST, ALLPositive) {

        sim2.memory[0x3002] = 0xDEAD;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(1,0);
        sim2.doInst(ST | SETDR(1) | 0x2);
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0x3002]);

        sim2.memory[0x3020] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(2,0);
        sim2.doInst(ST | SETDR(2) | 0x20);
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0x3020]);

        sim2.memory[0x30FF] = 0xCAFE;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(3,0);
        sim2.doInst(ST | SETDR(3) | 0xFF);
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0x30FF]);
}

TEST(CheckST, ALLNegative) {

        sim2.memory[0x3000 - 0x2] = 0xDEAD;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(1,0);
        sim2.doInst(LD | SETDR(1) | (-0x2 & 0x1FF));
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0x3000 - 0x2]);

        sim2.memory[0x3000 - 0x20] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(2,0);
        sim2.doInst(LD | SETDR(2) | (-0x20 & 0x1FF));
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0x3000 - 0x20]);

        sim2.memory[0x3000 - 0x100] = 0xCAFE;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(3,0);
        sim2.doInst(LD | SETDR(3) | (-0x100 & 0x1FF));
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0x3000 - 0x100]);
}

TEST(CheckSTR, AllPositive) {

        sim2.memory[0x3002] = 0xDEAD;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(0,0x3000);
        sim2.setReg(1,0);
        sim2.doInst(STR | SETDR(1) | SETSR1(0) | 0x2);
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0x3002]);

        sim2.memory[0x3010] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(0,0x3000);
        sim2.setReg(2,0);
        sim2.doInst(STR | SETDR(2) | SETSR1(0) | 0x10);
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0x3020]);

        sim2.memory[0x301F] = 0xCAFE;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(0,0x3000);
        sim2.setReg(3,0);
        sim2.doInst(STR | SETDR(3) | SETSR1(0) | 0x1F);
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0x30FF]);
}

TEST(CheckSTR, ALLNegative) {
        sim2.memory[0x3000 - 2] = 0xDEAD;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(1,0);
        sim2.doInst(STR | SETDR(1) | (-0x2 & 0x3F));
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0x3000 - 0x2]);

        sim2.memory[0x3000 - 0x10] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(2,0);
        sim2.doInst(STR | SETDR(2) | (-0x10 & 0x3F));
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0x3000 - 0x10]);

        sim2.memory[0x3000 - 0x20] = 0xCAFE;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(3,0);
        sim2.doInst(STR | SETDR(3) | (-0x20 & 0x3F));
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0x3000 - 0x20]);
}

TEST(CheckSTI, AllPositive) {

        sim2.memory[0x3002] = 0xDEAD;
        sim2.memory[0xDEAD] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(1,0);
        sim2.doInst(STI | SETDR(1) | 0x2);
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0xDEAD]);

        sim2.memory[0x3020] = 0xBEEF;
        sim2.memory[0xBEEF] = 0xF000;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(2,0);
        sim2.doInst(STI | SETDR(2) | 0x20);
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0xBEEF]);

        sim2.memory[0x30FF] = 0xCAFE;
        sim2.memory[0xCAFE] = 0x64F0;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(3,0);
        sim2.doInst(STI | SETDR(3) | 0xFF);
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0xCAFE]);
}

TEST(CheckSTI, ALLNegative) {

        sim2.memory[0x3000 - 0x2] = 0xDEAD;
        sim2.memory[0xDEAD] = 0xBEEF;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(1,0);
        sim2.doInst(STI | SETDR(1) | (-0x2 & 0x1FF));
        EXPECT_EQ(sim2.getReg(1), sim2.memory[0xDEAD]);

        sim2.memory[0x3000 - 0x20] = 0xBEEF;
        sim2.memory[0xBEEF] = 0xF000;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(2,0);
        sim2.doInst(STI | SETDR(2) | (-0x20 & 0x1FF));
        EXPECT_EQ(sim2.getReg(2), sim2.memory[0xBEEF]);

        sim2.memory[0x3000 - 0x100] = 0xCAFE;
        sim2.memory[0xCAFE] = 0x64F0;
        sim2.setPC(0x3000 - 1);
        sim2.setReg(3,0);
        sim2.doInst(STI | SETDR(3) | (-0x100 & 0x1FF));
        EXPECT_EQ(sim2.getReg(3), sim2.memory[0xCAFE]);
}
