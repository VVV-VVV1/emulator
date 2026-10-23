//
// Created by VVV_V on 16.10.2026.
//

#include "RegisterStack.h"
#include <stdexcept>

RegisterStack::RegisterStack() {
    clear();
}

void RegisterStack::push(uint16_t value) {
    if (full()) {
        throw std::overflow_error("Stack overflow");
    }

    for (std::size_t i = sp; i > 0; --i) {
        registers[i] = registers[i - 1];
    }

    registers[0] = value;
    ++sp;
}

uint16_t RegisterStack::pop() {
    if (empty()) {
        throw std::underflow_error("Stack underflow");
    }

    uint16_t value = registers[0];

    for (std::size_t i = 0; i < sp - 1; ++i) {
        registers[i] = registers[i + 1];
    }

    --sp;
    registers[sp] = 0;

    return value;
}

uint16_t RegisterStack::peek() const {
    if (empty()) {
        throw std::underflow_error("Stack is empty");
    }

    return registers[0];
}

std::size_t RegisterStack::size() const {
    return sp;
}

bool RegisterStack::empty() const {
    return sp == 0;
}

bool RegisterStack::full() const {
    return sp == SIZE;
}

void RegisterStack::clear() {
    registers.fill(0);
    sp = 0;
}

uint16_t RegisterStack::getAt(std::size_t index) const {
    if (index >= sp) {
        throw std::out_of_range("Stack index out of range");
    }

    return registers[index];
}