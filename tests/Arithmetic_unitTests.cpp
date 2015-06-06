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

#include "simulator.hpp"
#include "gtest/gtest.h"

using std::cout;
using std::endl;
using std::string;
using std::complex;

#define SETDR(x) (((x & 0x7) << 9)
#define SETSR1(x) (((x & 0x7) << 6)
#define SETBASER(x) (((x & 0x7) << 6)
#define SETSR2(x) (((x & 0x7) << 0)

#define SETN(x) (((x & 0x1) << 11)
#define SETZ(x) (((x & 0x1) << 10)
#define SETP(x) (((x & 0x1) << 9)
#define STEERINGNORM 1<<5

#define ADDR 0x1000
#define ADDI ADDR | STEERINGNORM
#define ANDR 0x5000
#define ANDI ANDR | STEERINGNORM
#define BR   0x0000
#define JMP  0xC000
#define JSR  0x4800
#define JSRR 0x4000
#define LD   0x2000
#define LDI  0xA000
#define LDR  0x6000
#define LEA  0xE000
#define NOT  0x903F
#define RET  0xC000
#define RTI  0x8000
#define ST   0x3000
#define STI  0xB000
#define STR  0x7000
#define TRAP 0xF000
#define RESERVEDINST 0xD000
/*********************************************************************/
// Phase A Tests
/*********************************************************************/
simulator sim;

TEST(CheckADD, Register) {
   sim.setReg(0, 2);
   sim.setReg(1, 2);
   sim.setReg(2, (uint16_t) -4);

   doInst(ADDR + SETDR(3) + SETSR1(0) + SETSR2(1)); //2 + 2 =4
   EXPECT_EQ(4, sim.getReg(3));

   doInst(ADDR + SETDR(4) + SETSR1(0) + SETSR2(2)); //2 + -4 = -2
   EXPECT_EQ(-2, sim.getReg(4));

   doInst(ADDR + SETDR(3) + SETSR1(3) + SETSR2(2)); //4 + -4 = 0
   EXPECT_EQ(0, sim.getReg(3));

}

TEST(CheckADD, Immediate) {
   sim.setReg(0, 2);

   doInst(ADDI + SETDR(3) + SETSR1(0) + 2); //2 + 2 =4
   EXPECT_EQ(4, sim.getReg(3));

   doInst(ADDI + SETDR(4) + SETSR1(0) + -4); //2 + -4 = -2
   EXPECT_EQ(-2, sim.getReg(4));

   doInst(ADDI + SETDR(3) + SETSR1(3) + -4); //4 + -4 = 0
   EXPECT_EQ(0, sim.getReg(3));

}

TEST(CheckAND, Register) {
   sim.setReg(0, 0x1010);
   sim.setReg(1, 0xFFFF);
   sim.setReg(2, 0x1000);
   sim.setReg(3, 0x0000);

   doInst(ANDR + SETDR(3) + SETSR1(0) + SETSR2(3)); 
   EXPECT_EQ(0, sim.getReg(3));

   doInst(ANDR + SETDR(4) + SETSR1(0) + SETSR2(1)); 
   EXPECT_EQ(0x1010, sim.getReg(4));

   doInst(ANDR + SETDR(4) + SETSR1(0) + SETSR2(2)); 
   EXPECT_EQ(0x1000, sim.getReg(4));

}

TEST(CheckAND, Immediate) {
   sim.setReg(0, 0x1010);
   sim.setReg(1, 0xFFFF);
   sim.setReg(2, 0x1000);
   sim.setReg(3, 0x0000);

   doInst(ANDI + SETDR(3) + SETSR1(0) + 0x0000); 
   EXPECT_EQ(0, sim.getReg(3));

   doInst(ANDI + SETDR(4) + SETSR1(0) + 0x1F); 
   EXPECT_EQ(0x1010, sim.getReg(4));

   doInst(ANDI + SETDR(4) + SETSR1(1) + 0x10; 
   EXPECT_EQ(0xFFF0, sim.getReg(4));

}
TEST(CheckNOT, All) {
   sim.setReg(0, 0x1010);
   sim.setReg(1, 0xFFFF);
   sim.setReg(2, 0x1000);
   sim.setReg(3, 0x0000);

   doInst(NOT + SETDR(4) + SETSR1(0)); 
   EXPECT_EQ(~0x1010, sim.getReg(4));

   doInst(NOT + SETDR(4) + SETSR1(1)); 
   EXPECT_EQ(0, sim.getReg(4));

   doInst(NOT + SETDR(4) + SETSR1(2); 
   EXPECT_EQ(~0x1000, sim.getReg(4));

   doInst(NOT + SETDR(4) + SETSR1(3); 
   EXPECT_EQ(0xFFFF, sim.getReg(4));

}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto out = RUN_ALL_TESTS();

#ifdef _MSC_VER
    system("pause");
#endif

    return out;
}
