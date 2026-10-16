//
// Created by VVV_V on 16.10.2026.
//

#ifndef EMULATOR_CPU_H
#define EMULATOR_CPU_H



#pragma once

#include <cstdint>
#include "Memory.h"
#include "RegisterStack.h"

class CPU {
public:
    CPU();

    void reset();
    void step();
    void loadWord(uint16_t address, uint16_t value);

    uint16_t getPC() const;
    std::size_t getSP() const;
    uint16_t getTop() const;
    uint16_t readWord(uint16_t address) const;

    bool isHalted() const;

private:
    Memory memory;
    RegisterStack stack;

    uint16_t PC;
    uint16_t IR;
    uint16_t FLAGS;

    bool halted;
};



#endif //EMULATOR_CPU_H
