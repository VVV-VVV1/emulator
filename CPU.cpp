//
// Created by VVV_V on 16.10.2026.
//

#include "CPU.h"
#include <stdexcept>

CPU::CPU()
    : PC(0),
      IR(0),
      FLAGS(0),
      halted(false)
{
    reset();
}

void CPU::reset() {
    PC = 0x0000;
    IR = 0;
    FLAGS = 0;

    stack.clear();

    halted = false;
}



void CPU::step() {
    if (halted) {
        return;
    }

    // FETCH
    IR = memory.read(PC);
    ++PC;

    // DECODE: PUSH/LIT
    if (IR & 0x8000) {
        uint16_t value = IR & 0x7FFF;
        stack.push(value);
        return;
    }

    // EXECUTE: остальные команды
    switch (IR) {
        case 0x0001: { // ADD
            if (stack.size() < 2) {
                throw std::underflow_error(
                    "ADD requires two operands"
                );
            }

            uint16_t b = stack.pop();
            uint16_t a = stack.pop();

            uint16_t result =
                static_cast<uint16_t>(a + b);

            stack.push(result);
            break;
        }

        default:
            throw std::runtime_error(
                "Unknown instruction"
            );
    }
}



void CPU::loadWord(uint16_t address, uint16_t value) {
    memory.write(address, value);
}

uint16_t CPU::getPC() const {
    return PC;
}

std::size_t CPU::getSP() const {
    return stack.size();
}

uint16_t CPU::getTop() const {
    return stack.peek();
}



