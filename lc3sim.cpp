#include "lc3sim.h"
#include <stdint.h>
#include <QString>

Lc3Sim::Lc3Sim()
{
}

void InstructionDecode(uint16_t inst){
    int opcode;
    int DR;
    int SR1;
    int SR2;
    int SR;
    int imm5;
    int N;
    int Z;
    int P;
    int alt = 0;
    int PCoffset11;
    int PCoffset9;
    int BaseR;
    int offset6;
    int trapvect8;
    bool setsCC;

    QString opStr;

    opcode = (int) (inst >> 12) & 0xF;
    DR = (int) (inst >> 9) & 0x7;
    SR1 = (int) (inst >> 6) & 0x7;

    switch(opcode){
       case 0x0:{
        opStr = "BR";
        N = (int) (inst >> 11) & 0x1;
        Z = (int) (inst >> 10) & 0x1;
        P = (int) (inst >> 9) & 0x1;
        if(N) opStr += "n";
        if(Z) opStr += "z";
        if(P) opStr += "p";

        setsCC = false;
    }
        case 0x1:{
            opStr = "ADD";
            int steering = (int) (inst >> 5) & 0x1;
            if(steering){
                opStr += "I";
                alt = 1;
            }
            setsCC = true;

 }
        case 0x2:{
            opStr = "LD";
            setsCC = true;
 }
        case 0x3:{
        opStr = "ST";
        setsCC = false;
 }
        case 0x4:{
        opStr = "JSR";
        setsCC = false;
        int steering = (int) (inst >> 11) & 0x1;
        if(!steering){
            opStr += "R";
            alt = 1;
        }

 }
        case 0x5:{

 }
        case 0x6:{

 }
        case 0x7:{

 }
        case 0x8:{

 }
        case 0x9:{

 }
        case 0xA:{

 }
        case 0xB:{

 }
        case 0xC:{

 }
        case 0xD:{

 }
        case 0xE:{

 }
        case 0xF:{

 }
    }
}
