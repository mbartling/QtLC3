#include "simulator.hpp"
#include <chrono>
#include <complex>
#include <cstdint>
#include <future>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include "gtest/gtest.h"
#include "LC3Helper.h"

simulator sim1;

TEST(CheckBR, AllPositive) {
   sim1.setReg(0, 0x1010);
   sim1.setReg(1, 0xFFFF);
   sim1.setReg(2, 0x1000);
   sim1.setReg(3, 0x0000);

   //Simple NOP test
   sim1.setPC(0x3002);
   sim1.doInst(BR | 0x1);
   EXPECT_EQ(0x3003, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.setPcsrBit('p', true);
   sim1.setPcsrBit('n', true);
   sim1.setPcsrBit('z', true);
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | 0x1);
   EXPECT_EQ(0x3004, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.setPcsrBit('p', true);
   sim1.setPcsrBit('n', false);
   sim1.setPcsrBit('z', false);
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | 0x1);
   EXPECT_EQ(0x3004, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.setPcsrBit('p', false);
   sim1.setPcsrBit('n', true);
   sim1.setPcsrBit('z', false);
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | 0x1);
   EXPECT_EQ(0x3004, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.setPcsrBit('p', false);
   sim1.setPcsrBit('n', false);
   sim1.setPcsrBit('z', true);
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | 0x1);
   EXPECT_EQ(0x3004, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.setPcsrBit('n', true);
   sim1.setPcsrBit('z', false);
   sim1.setPcsrBit('p', false);
   sim1.doInst(BR | SETN(1) | SETZ(0) | SETP(0) | 0x1);
   EXPECT_EQ(0x3004, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.setPcsrBit('n', false);
   sim1.setPcsrBit('z', true);
   sim1.setPcsrBit('p', false);
   sim1.doInst(BR | SETN(0) | SETZ(1) | SETP(0) | 0x1);
   EXPECT_EQ(0x3004, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.setPcsrBit('n', false);
   sim1.setPcsrBit('z', false);
   sim1.setPcsrBit('p', true);
   sim1.doInst(BR | SETN(0) | SETZ(0) | SETP(1) | 0x1);
   EXPECT_EQ(0x3004, sim1.getPC());
}

TEST(CheckBR, AllNegative) {
   sim1.setReg(0, 0x1010);
   sim1.setReg(1, 0xFFFF);
   sim1.setReg(2, 0x1000);
   sim1.setReg(3, 0x0000);
   uint16_t bTarget = (uint16_t) (-4) & 0x1FF;
   //Simple NOP test
   sim1.setPC(0x3002);
   sim1.doInst(BR | bTarget);
   EXPECT_EQ(0x3003, sim1.getPC());

   sim1.setPC(0x3003);
   sim1.setPcsrBit('p', true);
   sim1.setPcsrBit('n', true);
   sim1.setPcsrBit('z', true);
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | bTarget);
   EXPECT_EQ(0x3000, sim1.getPC());

   sim1.setPC(0x3003);
   sim1.setPcsrBit('p', true);
   sim1.setPcsrBit('n', false);
   sim1.setPcsrBit('z', false);
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | bTarget);
   EXPECT_EQ(0x3000, sim1.getPC());

   sim1.setPC(0x3003);
   sim1.setPcsrBit('p', false);
   sim1.setPcsrBit('n', true);
   sim1.setPcsrBit('z', false);
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | bTarget);
   EXPECT_EQ(0x3000, sim1.getPC());

   sim1.setPC(0x3003);
   sim1.setPcsrBit('p', false);
   sim1.setPcsrBit('n', false);
   sim1.setPcsrBit('z', true);
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | bTarget);
   EXPECT_EQ(0x3000, sim1.getPC());

   sim1.setPC(0x3003);
   sim1.setPcsrBit('n', true);
   sim1.setPcsrBit('z', false);
   sim1.setPcsrBit('p', false);
   sim1.doInst(BR | SETN(1) | SETZ(0) | SETP(0) | bTarget);
   EXPECT_EQ(0x3000, sim1.getPC());

   sim1.setPC(0x3003);
   sim1.setPcsrBit('n', false);
   sim1.setPcsrBit('z', true);
   sim1.setPcsrBit('p', false);
   sim1.doInst(BR | SETN(0) | SETZ(1) | SETP(0) | bTarget);
   EXPECT_EQ(0x3000, sim1.getPC());

   sim1.setPC(0x3003);
   sim1.setPcsrBit('n', false);
   sim1.setPcsrBit('z', false);
   sim1.setPcsrBit('p', true);
   sim1.doInst(BR | SETN(0) | SETZ(0) | SETP(1) | bTarget);
   EXPECT_EQ(0x3000, sim1.getPC());

   sim1.setPC(0x3003);
   sim1.setPcsrBit('p', false);
   sim1.setPcsrBit('n', false);
   sim1.setPcsrBit('z', true);
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | (1 << 8));
   EXPECT_LT(sim1.getPC(), 0x3000);
   EXPECT_EQ(sim1.getPC(), (uint16_t)(0x3004 - (1 << 8)));

}

TEST(CheckBR, AllPositiveInstructions) {
   sim1.setReg(0, 0x1010);
   sim1.setReg(1, 0xFFFF);
   sim1.setReg(2, 0x1000);
   sim1.setReg(3, 0x0000);

   //Simple NOP test
   sim1.setPC(0x3002);
   sim1.doInst(ADDI | SETDR(4) | SETSR1(3) | 1 );  
   sim1.doInst(BR | 0x1);
   EXPECT_EQ(0x3004, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.doInst(ADDI | SETDR(4) | SETSR1(3) | 1 );  
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | 0x1);
   EXPECT_EQ(0x3005, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.doInst(ADDI | SETDR(4) | SETSR1(3) | 1 );  
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | 0x1);
   EXPECT_EQ(0x3005, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.doInst(ADDI | SETDR(4) | SETSR1(3) | (((uint16_t) -1) & 0x1F));  
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | 0x1);
   EXPECT_EQ(0x3005, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.doInst(ADDI | SETDR(4) | SETSR1(3) | 0 );  
   sim1.doInst(BR | SETN(1) | SETZ(1) | SETP(1) | 0x1);
   EXPECT_EQ(0x3005, sim1.getPC());

// ----------------------------------------
   sim1.setPC(0x3002);
   sim1.doInst(ADDI | SETDR(4) | SETSR1(3) | 1 );  
   sim1.doInst(BR | SETN(0) | SETZ(0) | SETP(1) | 0x1);
   EXPECT_EQ(0x3005, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.doInst(ADDI | SETDR(4) | SETSR1(3) | (((uint16_t) -1) & 0x1F));  
   sim1.doInst(BR | SETN(1) | SETZ(0) | SETP(0) | 0x1);
   EXPECT_EQ(0x3005, sim1.getPC());

   sim1.setPC(0x3002);
   sim1.doInst(ADDI | SETDR(4) | SETSR1(3) | 0 );  
   sim1.doInst(BR | SETN(0) | SETZ(1) | SETP(0) | 0x1);
   EXPECT_EQ(0x3005, sim1.getPC());
}

TEST(CheckJMP, All) {
   sim1.setReg(0, 0x1010);
   sim1.setReg(1, 0xFFFF);
   sim1.setReg(2, 0x1000);
   sim1.setReg(3, 0x0000);
   sim1.setReg(4, 0x3000);
   sim1.setPC(0x3002);
   sim1.doInst(JMP | SETBASER(2));
   EXPECT_EQ(sim1.getReg(2), sim1.getPC());
 
   sim1.doInst(JMP | SETBASER(0));
   EXPECT_EQ(sim1.getReg(0), sim1.getPC());

   sim1.doInst(JMP | SETBASER(1));
   EXPECT_EQ(sim1.getReg(1), sim1.getPC());

   sim1.doInst(JMP | SETBASER(3));
   EXPECT_EQ(sim1.getReg(3), sim1.getPC());

   sim1.doInst(JMP | SETBASER(0));
   sim1.doInst(ADDR | SETDR(5) | SETSR1(3) | SETSR2(4));
   sim1.doInst(JMP | SETBASER(5));
   EXPECT_EQ(0x3000, sim1.getPC());
   EXPECT_EQ(sim1.getReg(5), sim1.getPC());

}

TEST(CheckJSR, All) {
   uint16_t currPC;
   uint16_t offSet9;
   sim1.setReg(0, 0x1010);
   sim1.setReg(1, 0xFFFF);
   sim1.setReg(2, 0x1000);
   sim1.setReg(3, 0x0000);
   sim1.setReg(4, 0x3000);

   sim1.setPC(0x3002);
   currPC = sim1.getPC() + 1;
   offSet9 = 32;
   sim1.doInst(JSR | offSet9);
   EXPECT_EQ(sim1.getReg(7), currPC);
   EXPECT_EQ(sim1.getPC(), (uint16_t)(currPC + offSet9));

   sim1.setPC(0x3002);
   currPC = sim1.getPC() + 1;
   offSet9 = ((uint16_t) -1000);
   sim1.doInst(JSR | (offSet9 & 0x7FF));
   EXPECT_EQ(sim1.getReg(7), currPC);
   EXPECT_EQ(sim1.getPC(), (uint16_t)(currPC + offSet9));

   sim1.setPC(0x3002);
   currPC = sim1.getPC() + 1;
   offSet9 = (uint16_t) 1000;
   sim1.doInst(JSR | offSet9);
   EXPECT_EQ(sim1.getReg(7), currPC);
   EXPECT_EQ(sim1.getPC(), (uint16_t)(currPC + offSet9));

   sim1.setPC(0x3002);
   currPC = sim1.getPC() + 1;
   offSet9 = (uint16_t) -1024;
   sim1.doInst(JSR | (offSet9 &0x7FF));
   EXPECT_EQ(sim1.getReg(7), currPC);
   EXPECT_EQ(sim1.getPC(), (uint16_t)(currPC + offSet9));
}

TEST(CheckJSRR, All) {
   uint16_t currPC;

   sim1.setReg(0, 0x1010);
   sim1.setReg(1, 0xFFFF);
   sim1.setReg(2, 0x1000);
   sim1.setReg(3, 0x0000);
   sim1.setReg(4, 0x3000);


   sim1.setPC(0x3002);
   currPC = sim1.getPC() + 1;
   sim1.doInst(JSRR | SETBASER(2));
   EXPECT_EQ(sim1.getReg(2), sim1.getPC());
   EXPECT_EQ(sim1.getReg(7), currPC);

   currPC = sim1.getPC() + 1;
   sim1.doInst(JSRR | SETBASER(0));
   EXPECT_EQ(sim1.getReg(0), sim1.getPC());
   EXPECT_EQ(sim1.getReg(7), currPC);

   currPC = sim1.getPC() + 1;
   sim1.doInst(JSRR | SETBASER(1));
   EXPECT_EQ(sim1.getReg(1), sim1.getPC());
   EXPECT_EQ(sim1.getReg(7), currPC);

   currPC = sim1.getPC() + 1;
   sim1.doInst(JSRR | SETBASER(3));
   EXPECT_EQ(sim1.getReg(3), sim1.getPC());
   EXPECT_EQ(sim1.getReg(7), currPC);

   sim1.doInst(JSRR | SETBASER(0));
   sim1.doInst(ADDR | SETDR(5) | SETSR1(3) | SETSR2(4));
   currPC = sim1.getPC() + 1;
   sim1.doInst(JSRR | SETBASER(5));
   EXPECT_EQ(0x3000, sim1.getPC());
   EXPECT_EQ(sim1.getReg(5), sim1.getPC());
   EXPECT_EQ(sim1.getReg(7), currPC);

   //Check if return works
   sim1.doInst(RET);
   EXPECT_EQ(sim1.getPC(), sim1.getReg(7));
   EXPECT_EQ(sim1.getPC(), currPC);

}
