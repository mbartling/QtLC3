#include "simulator.hpp"


bool simulator::stepOnce( void ) {
        return true;
}

bool simulator::doInst( uint16_t inst ) {
        return true;
}

bool simulator::getPcsrBit( char mnemonic ) {
        switch (mnemonic) {
        case 'n':
        case 'N':
                return this->N;
        case 'z':
        case 'Z':
                return this->Z;
        case 'p':
        case 'P':
                return this->P;
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

uint16_t simulator::sliceMem( uint16_t addr ) {
        return this->memory[addr];
}
