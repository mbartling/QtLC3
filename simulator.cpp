#include "simulator.hpp"
#include "simulator-internals.hpp"
#include "stdio.h"

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param d [description]
 * @return [description]
 */
bool simulator::stepOnce( void ) {
        return true;
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param result [description]
 */
void simulator::setNZP( uint16_t result ) {
        int16_t signedResult = (int16_t) result;
        this->N = false;
        this->Z = false;
        this->P = false;
        if (signedResult < 0) this->N = true;
        else if (signedResult == 0) this-> Z = true;
        else if (signedResult > 0) this->P = true;
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param inst [description]
 * @return [description]
 */
bool simulator::doInst( uint16_t inst ) {
        uint16_t result = 0;
        //LC3 PreIncrements the PC
        this->PC = (this->PC + 1) % ADDRESS_SPACE;

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
        case LD:
        case LDI:
        case ST:
        case STI:
        case LEA:
                result = this->PC + inst2imm9(inst);
                break;

        case LDR:
        case STR:
                result = this->regs[inst2sr1(inst)] + inst2imm6(inst);
                break;

        case BR:
                if ((this->N && inst2n(inst))
                    || (this->Z && inst2z(inst))
                    || (this->P && inst2p(inst)))
                        this->PC += inst2imm9(inst);
                break;

        case JSR:
                this->regs[7] = this->PC;
        case JMP:
                if (inst2n(inst))
                        this->PC += inst2imm11(inst);
                else
                        this->PC = this->regs[inst2sr1(inst)];
                break;


        default:
                return false;
        }

        switch (inst2opcode(inst)){
        case LDI:
                result = this->memory[result];
        case LD:
        case LDR:
                result = this->memory[result];
        case ADD:
        case AND:
        case NOT:
        case LEA:
                this->regs[inst2dr(inst)] = result;
                this->setNZP(result);
                break;
        case JSR:
        case JMP:
        case BR:
                break;
        case STI:
                result = this->memory[result];
        case ST:
        case STR:
                this->memory[result] = this->regs[inst2dr(inst)];
                break;
        default:
                return false;
        }
        return true;
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param mnemonic [description]
 * @return [description]
 */
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

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param mnemonic [description]
 * @param newVal [description]
 * 
 * @return [description]
 */
bool simulator::setPcsrBit( char mnemonic , bool newVal) {
        switch (mnemonic) {
        case 'n':
        case 'N':
                this->N = newVal;
                break;
        case 'z':
        case 'Z':
                this->Z = newVal;
                break;
        case 'p':
        case 'P':
                this->P = newVal;
                break;
        default:
                return false;

        }
        return true;

}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param number [description]
 * @return [description]
 */
uint16_t simulator::getReg( int number ) {
        return (number > NUM_REGS) ? 0 : this->regs[number];
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param number [description]
 * @param newVal [description]
 * 
 * @return [description]
 */
bool simulator::setReg( int number, uint16_t newVal ) {
        if (number > NUM_REGS) {
                return false;
        } else {
                this->regs[number] = newVal;
                return true;
        }
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param start [description]
 * @param stop [description]
 * 
 * @return [description]
 */
vector<uint16_t> simulator::sliceMem( uint16_t start, uint16_t stop ){
        return vector<uint16_t>(this->memory.begin() + start,
                                this->memory.begin() + stop );
}

/**
 * @brief Set the Current PC
 * @details Checks if the desired PC is Valid, then sets it
 * @return boolean if valid or not
 */
uint16_t simulator::getPC(void){ return PC; }
bool simulator::setPC(uint16_t pc){
        if(pc >= ADDRESS_SPACE) return false;
        this->PC = pc;
        return true;
}

