#include "simulator.hpp"
#include "simulator-internals.hpp"
#include "stdio.h"


bool simulator::stepOnce( void ) {
        return true;
}

void simulator::setNZP( uint16_t result ) {
        int16_t signedResult = (int16_t) result;
        this->N = false;
        this->Z = false;
        this->P = false;
        if (signedResult < 0) this->N = true;
        else if (signedResult == 0) this-> Z = true;
        else if (signedResult > 0) this->P = true;
}

bool simulator::doInst( uint16_t inst ) {
        uint16_t result = 0;
        this->PC++;
        switch (inst2opcode(inst)) {
        case ADD:
                if (inst2steering(inst)) {
                        result = this->regs[inst2sr1(inst)]
                                + inst2imm5(inst);
                } else {
                        result = this->regs[inst2sr1(inst)]
                                + this->regs[inst2sr2(inst)];
                }
                break;
        case AND:
                if (inst2steering(inst)) {
                        result = this->regs[inst2sr1(inst)]
                                & inst2imm5(inst);
                } else {
                        result = this->regs[inst2sr1(inst)]
                                & this->regs[inst2sr2(inst)];
                }
                break;
        case NOT:
                result = ~this->regs[inst2sr1(inst)];
                break;
        case LEA:
                result = this->PC + inst2imm9(inst);
                break;
        default:
                return false;
        }
        switch (inst2opcode(inst)){
        case ADD:
        case AND:
        case NOT:
        case LEA:
                this->regs[inst2dr(inst)] = result;
                this->setNZP(result);
                break;
        default:
                return false;
        }
        return true;
}

bool simulator::getPcsrBit( char mnemonic ) {
        switch (mnemonic) {
        case 'n':
        case 'N':
                return this->N == 1;
        case 'z':
        case 'Z':
                return this->Z == 1;
        case 'p':
        case 'P':
                return this->P == 1;
        default:
                return false;

        }
}

bool simulator::setPcsrBit( char mnemonic , bool newVal) {
        switch (mnemonic) {
        case 'n':
        case 'N':
                this->N = newVal;
                return true;
        case 'z':
        case 'Z':
                this->Z = newVal;
                return true;
        case 'p':
        case 'P':
                this->P = newVal;
                return true;
        default:
                return false;

        }
}

uint16_t simulator::getReg( int number ) {
        return (number > NUM_REGS) ? 0 : this->regs[number];
}

bool simulator::setReg( int number, uint16_t newVal ) {
        if (number > NUM_REGS) {
                return false;
        } else {
                this->regs[number] = newVal;
                return true;
        }
}

vector<uint16_t> simulator::sliceMem( uint16_t start, uint16_t stop ){
        return vector<uint16_t>(this->memory.begin() + start,
                                this->memory.begin() + stop );
}

uint16_t simulator::getPC(void){ return PC; }
bool simulator::setPC(uint16_t pc){
        if(pc >= ADDRESS_SPACE) return false;
        this->PC = pc;
        return true;
}