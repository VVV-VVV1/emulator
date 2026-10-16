//
// Created by VVV_V on 16.10.2026.
//

#ifndef EMULATOR_REGISTERSTACK_H
#define EMULATOR_REGISTERSTACK_H


#pragma once

#include <array>
#include <cstdint>
#include <cstddef>

class RegisterStack {
public:
    static constexpr std::size_t SIZE = 16;

    RegisterStack();

    void push(uint16_t value);
    uint16_t pop();
    uint16_t peek() const;

    std::size_t size() const;
    bool empty() const;
    bool full() const;

    void clear();

private:
    std::array<uint16_t, SIZE> registers;
    std::size_t sp;
};

#endif //EMULATOR_REGISTERSTACK_H
