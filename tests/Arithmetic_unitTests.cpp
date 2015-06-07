/*
 * Valarray_PhaseA_unittests.cpp
 * EPL - Spring 2015
 */

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
using std::cout;
using std::endl;
using std::string;
using std::complex;

/*********************************************************************/
// Phase A Tests
/*********************************************************************/
simulator sim;

TEST(CheckADD, Register) {
   sim.setReg(0, 2);
   sim.setReg(1, 2);
   sim.setReg(2, (uint16_t) -4);

   sim.doInst(ADDR | SETDR(3) | SETSR1(0) | SETSR2(1)); //2 + 2 =4
   EXPECT_EQ(4, sim.getReg(3));
   EXPECT_EQ(false, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(true, sim.getPcsrBit('p'));

   sim.doInst(ADDR | SETDR(4) | SETSR1(0) | SETSR2(2)); //2 + -4 = -2
   EXPECT_EQ((uint16_t) -2, sim.getReg(4));
   EXPECT_EQ(true, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

   sim.doInst(ADDR | SETDR(3) | SETSR1(3) | SETSR2(2)); //4 + -4 = 0
   EXPECT_EQ(0, sim.getReg(3));
   EXPECT_EQ(false, sim.getPcsrBit('n'));
   EXPECT_EQ(true, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

}

TEST(CheckADD, Immediate) {
   sim.setReg(0, 2);

   sim.doInst(ADDI | SETDR(3) | SETSR1(0) | (2 & 0x1F));  //2 + 2 =4
   EXPECT_EQ(4, sim.getReg(3));
   EXPECT_EQ(false, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(true, sim.getPcsrBit('p'));

   sim.doInst(ADDI | SETDR(4) | SETSR1(0) | (((uint16_t)-4) & 0x1F)); //2 + -4 = -2
   EXPECT_EQ((uint16_t)-2, sim.getReg(4));
   EXPECT_EQ(true, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

   sim.doInst(ADDI | SETDR(3) | SETSR1(3) | (((uint16_t)-4) & 0x1F)); //4 + -4 = 0
   EXPECT_EQ(0, sim.getReg(3));
   EXPECT_EQ(false, sim.getPcsrBit('n'));
   EXPECT_EQ(true, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

}

TEST(CheckAND, Register) {
   sim.setReg(0, 0x1010);
   sim.setReg(1, 0xFFFF);
   sim.setReg(2, 0x1000);
   sim.setReg(3, 0x0000);

   sim.doInst(ANDR | SETDR(3) | SETSR1(0) | SETSR2(3)); 
   EXPECT_EQ(0, sim.getReg(3));
   EXPECT_EQ(false, sim.getPcsrBit('n'));
   EXPECT_EQ(true, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

   sim.doInst(ANDR | SETDR(4) | SETSR1(0) | SETSR2(1)); 
   EXPECT_EQ(0x1010, sim.getReg(4));
   EXPECT_EQ(false, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(true, sim.getPcsrBit('p'));

   sim.doInst(ANDR | SETDR(4) | SETSR1(0) | SETSR2(2)); 
   EXPECT_EQ(0x1000, sim.getReg(4));
   EXPECT_EQ(false, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(true, sim.getPcsrBit('p'));

}

TEST(CheckAND, Immediate) {
   sim.setReg(0, 0x1010);
   sim.setReg(1, 0xFFFF);
   sim.setReg(2, 0x1000);
   sim.setReg(3, 0x0000);

   sim.doInst(ANDI | SETDR(3) | SETSR1(0) | 0x0000); 
   EXPECT_EQ(0, sim.getReg(3));
   EXPECT_EQ(false, sim.getPcsrBit('n'));
   EXPECT_EQ(true, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

   sim.doInst(ANDI | SETDR(4) | SETSR1(0) | 0x1F); 
   EXPECT_EQ(0x1010, sim.getReg(4));
   EXPECT_EQ(false, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(true, sim.getPcsrBit('p'));

   sim.doInst(ANDI | SETDR(4) | SETSR1(1) | 0x10); 
   EXPECT_EQ(0xFFF0, sim.getReg(4));
   EXPECT_EQ(true, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

}

TEST(CheckNOT, All) {
   sim.setReg(0, 0x1010);
   sim.setReg(1, 0xFFFF);
   sim.setReg(2, 0x1000);
   sim.setReg(3, 0x0000);

   sim.doInst(NOT | SETDR(4) | SETSR1(0)); 
   EXPECT_EQ((uint16_t)~0x1010, sim.getReg(4));
   EXPECT_EQ(true, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

   sim.doInst(NOT | SETDR(4) | SETSR1(1)); 
   EXPECT_EQ(0, sim.getReg(4));
   EXPECT_EQ(false, sim.getPcsrBit('n'));
   EXPECT_EQ(true, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

   sim.doInst(NOT | SETDR(4) | SETSR1(2)); 
   EXPECT_EQ((uint16_t)~0x1000, sim.getReg(4));
   EXPECT_EQ(true, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

   sim.doInst(NOT | SETDR(4) | SETSR1(3)); 
   EXPECT_EQ((uint16_t)0xFFFF, sim.getReg(4));
   EXPECT_EQ(true, sim.getPcsrBit('n'));
   EXPECT_EQ(false, sim.getPcsrBit('z'));
   EXPECT_EQ(false, sim.getPcsrBit('p'));

}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto out = RUN_ALL_TESTS();

#ifdef _MSC_VER
    system("pause");
#endif

    return out;
}
