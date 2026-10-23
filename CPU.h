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

    static constexpr uint16_t FLAG_ZF = 0x0001;
    static constexpr uint16_t FLAG_CF = 0x0002;
    static constexpr uint16_t FLAG_SF = 0x0004;

    uint16_t getFLAGS() const;

    std::size_t run(std::size_t maxSteps = 100000);

    uint16_t getIR() const;

    uint16_t getStackAt(std::size_t index) const;


private:
    Memory memory;
    RegisterStack stack;

    uint16_t PC;
    uint16_t IR;
    uint16_t FLAGS;

    bool halted;
};



#endif //EMULATOR_CPU_H
