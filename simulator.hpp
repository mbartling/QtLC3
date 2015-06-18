#pragma once

#include <Python.h>
#include <string>
#include <iostream>
#include <vector>
#include <stdint.h>
#include <functional>

constexpr int ADDRESS_SPACE = 1<<16;
constexpr int NUM_REGS = 8;
using std::cout;
using std::endl;
using std::vector;

struct WatchPoint;
class simulator;

struct WatchPoint {
        uint16_t address;
        uint16_t prevVal;
        uint16_t currVal;
        bool readPoint;
        bool writePoint;
        PyObject *cb;

};
struct BreakPoint {
        uint16_t address;
        PyObject *cb;
};

void doJack(uint16_t, uint16_t);
/**
 * @brief Basic LC3 Simulator Class
 * @details This class is exposed to the Python Interface,
 * CLI, and GUI
 * 
 */
class simulator{
public:
        using MEM_type = vector<uint16_t>;
        vector<uint16_t> memory = vector<uint16_t>(ADDRESS_SPACE);
        bool stepN( int cycles );
        bool doInst( uint16_t );
        vector<uint16_t> sliceMem ( uint16_t start, uint16_t stop );
        uint16_t getReg ( int number );
        bool setReg ( int number , uint16_t newVal);
        bool getPcsrBit ( char mnemonic );
        bool setPcsrBit ( char mnemonic , bool newVal);
        uint16_t getPC(void);
        bool setPC(uint16_t);

        bool addWatchPoint(uint16_t addr, bool read, bool write, PyObject* cb);
        bool addBreakPoint(uint16_t addr, PyObject* cb);
        int getNumWatchPoints();
        bool loadBinFile(std::string);
        bool run();
        void setOnMemChanged(std::function<void (uint16_t, uint16_t)> handlerFunction);
        void setOnEndOfCycle(std::function<void (void)> handlerFunction);
        void setRefreshGUIMemHook(std::function<void (void)> handlerFunction);
        void refreshGUIMemCall(void);

        uint16_t memRead( uint16_t addr );
        void memWrite( uint16_t addr, uint16_t newVal );
private:
        vector<uint16_t> regs = vector<uint16_t>(NUM_REGS);
        vector<WatchPoint> watchPoints = vector<WatchPoint>();
        vector<BreakPoint> breakPoints = vector<BreakPoint>();
        uint16_t N, Z, P, S;
        uint16_t PC;
        void setNZP( uint16_t );

        std::function<void (uint16_t, uint16_t)> onMemChanged;
        std::function<void (void)> onEndOfCycle;
        std::function<void (void)> refreshGUIMem;


};
