//
// Created by VVV_V on 16.10.2026.
//
#include "Memory.h"

Memory::Memory() {
    clear();
}

uint16_t Memory::read(uint16_t address) const {
    return cells[address];
}

void Memory::write(uint16_t address, uint16_t value) {
    cells[address] = value;
}

void Memory::clear() {
    cells.fill(0);
}