//
// Created by VVV_V on 19.10.2026.
//


#include "Assembler.h"

#include <sstream>
#include <stdexcept>
#include <fstream>

#include <unordered_map>
#include <algorithm>
#include <cctype>

#include <unordered_set>
#include <limits>

uint16_t Assembler::assembleInstruction(
    const std::string& instruction
) const {
    std::istringstream stream(instruction);

    std::string command;
    stream >> command;

    if (command == "PUSH") {
        unsigned int value;
        if (!(stream >> value)) {
            throw std::runtime_error(
                "PUSH requires a value"
            );
        }

        if (value > 0x7FFF) {
            throw std::out_of_range(
                "PUSH value must be <= 32767"
            );
        }

        return static_cast<uint16_t>(
            0x8000 | value
        );
    }

    if (command == "ADD")  return 0x0001;
    if (command == "SUB")  return 0x0002;
    if (command == "DUP")  return 0x0003;
    if (command == "DROP") return 0x0004;
    if (command == "SWAP") return 0x0005;
    if (command == "READ") return 0x0006;
    if (command == "WRITE") return 0x0007;
    if (command == "JMP")  return 0x0008;
    if (command == "JNZ")  return 0x0009;
    if (command == "HALT") return 0x000A;

    throw std::runtime_error(
        "Unknown instruction: " + command
    );
}




std::vector<AssembledWord> Assembler::assemble(
    const std::vector<std::string>& instructions
) const {
    std::unordered_map<std::string, uint16_t> labels;
    std::vector<std::string> program;

    // Первый проход: определяем адреса меток
    uint32_t address = 0;

    for (const std::string& sourceLine : instructions) {
        std::string line = sourceLine;

        const auto start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) {
            continue;
        }

        const auto end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);

        if (line.back() == ':') {
            std::string label = line.substr(0, line.size() - 1);

            if (label.empty()) {
                throw std::runtime_error("Empty label");
            }

            if (labels.find(label) != labels.end()) {
                throw std::runtime_error(
                    "Duplicate label: " + label
                );
            }

            if (address > 0xFFFF) {
                throw std::out_of_range("Label address out of range");
            }

            labels[label] = static_cast<uint16_t>(address);
            continue;
        }

        std::istringstream stream(line);
        std::string command;
        stream >> command;

        if (command == "ORG") {
            std::string operand;
            stream >> operand;

            address = std::stoul(operand, nullptr, 0);

            if (address > 0xFFFF) {
                throw std::out_of_range("ORG address out of range");
            }
        }
        else {
            if (address > 0xFFFF) {
                throw std::out_of_range("Program exceeds memory");
            }
            ++address;
        }

        program.push_back(line);
    }

    // Второй проход: формируем машинные слова
    std::vector<AssembledWord> machineCode;
    std::unordered_set<uint16_t> usedAddresses;

    address = 0;

    for (const std::string& line : program) {
        std::istringstream stream(line);
        std::string command;
        stream >> command;

        if (command == "ORG") {
            std::string operand;
            stream >> operand;
            address = std::stoul(operand, nullptr, 0);
            continue;
        }

        uint16_t value = 0;

        if (command == "WORD") {
            std::string operand;
            stream >> operand;

            unsigned long number =
                std::stoul(operand, nullptr, 0);

            if (number > 0xFFFF) {
                throw std::out_of_range("WORD value out of range");
            }

            value = static_cast<uint16_t>(number);
        }
        else if (command == "PUSH") {
            std::string operand;
            stream >> operand;

            auto it = labels.find(operand);

            if (it != labels.end()) {
                if (it->second > 0x7FFF) {
                    throw std::out_of_range(
                        "Label exceeds PUSH range"
                    );
                }

                value = static_cast<uint16_t>(
                    0x8000 | it->second
                );
            }
            else {
                value = assembleInstruction(line);
            }
        }
        else {
            value = assembleInstruction(line);
        }

        uint16_t currentAddress =
            static_cast<uint16_t>(address);

        if (!usedAddresses.insert(currentAddress).second) {
            throw std::runtime_error(
                "Overlapping memory addresses"
            );
        }

        machineCode.push_back({currentAddress, value});
        ++address;
    }

    return machineCode;
}



std::vector<AssembledWord> Assembler::assembleFile(
    const std::string& filename
) const {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Cannot open file: " + filename
        );
    }

    std::vector<std::string> instructions;
    std::string line;

    while (std::getline(file, line)) {
        instructions.push_back(line);
    }

    return assemble(instructions);
}

