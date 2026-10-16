//
// Created by VVV_V on 16.10.2026.
//

#ifndef EMULATOR_MEMORY_H
#define EMULATOR_MEMORY_H

#endif //EMULATOR_MEMORY_H

#pragma once

#include <array>
#include <cstdint>
#include <cstddef>

class Memory {
public:
    static constexpr std::size_t SIZE = 65536;

    Memory();

    uint16_t read(uint16_t address) const;
    void write(uint16_t address, uint16_t value);

    void clear();

private:
    std::array<uint16_t, SIZE> cells{};
};