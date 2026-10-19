//
// Created by VVV_V on 19.10.2026.
//

#ifndef EMULATOR_ASSEMBLER_H
#define EMULATOR_ASSEMBLER_H

#pragma once

#include <cstdint>
#include <string>
#include <vector>


struct AssembledWord {
    uint16_t address;
    uint16_t value;
};

class Assembler {
public:
    uint16_t assembleInstruction(
        const std::string& instruction
    ) const;
    
    std::vector<AssembledWord> assemble(
        const std::vector<std::string>& instructions
    ) const;

    std::vector<AssembledWord> assembleFile(
        const std::string& filename
    ) const;

};


#endif //EMULATOR_ASSEMBLER_H
