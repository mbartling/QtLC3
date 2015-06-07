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

simulator sim1;

TEST(CheckBR, All) {
   sim1.setPC(0x3002);
   sim1.setReg(0, 0x1010);
   sim1.setReg(1, 0xFFFF);
   sim1.setReg(2, 0x1000);
   sim1.setReg(3, 0x0000);

   sim1.doInst()
   sim1.doInst(NOT | SETDR(4) | SETSR1(0)); 
   EXPECT_EQ((uint16_t)~0x1010, sim1.getReg(4));

   sim1.doInst(NOT | SETDR(4) | SETSR1(1)); 
   EXPECT_EQ(0, sim1.getReg(4));

   sim1.doInst(NOT | SETDR(4) | SETSR1(2)); 
   EXPECT_EQ((uint16_t)~0x1000, sim1.getReg(4));

   sim1.doInst(NOT | SETDR(4) | SETSR1(3)); 
   EXPECT_EQ((uint16_t)0xFFFF, sim1.getReg(4));

}