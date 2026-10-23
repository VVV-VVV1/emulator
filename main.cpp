
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <iomanip>

#include "CPU.h"
#include "Assembler.h"

int main() {
    CPU cpu;
    Assembler assembler;

    bool programLoaded = false;
    int choice = 0;

    while (true) {
        std::cout << "\n===== CPU EMULATOR =====\n";
        std::cout << "1. Load program\n";
        std::cout << "2. Run program\n";
        std::cout << "3. Step\n";
        std::cout << "4. Show CPU state\n";
        std::cout << "5. Show memory\n";
        std::cout << "6. Exit\n";
        std::cout << "Select option: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::string filename;

                std::cout << "Enter filename: ";
                std::cin >> filename;

                try {
                    std::vector<AssembledWord> program =
                        assembler.assembleFile(filename);

                    cpu.reset();

                    for (const AssembledWord& word : program) {
                        cpu.loadWord(word.address, word.value);
                    }

                    programLoaded = true;

                    std::cout << "Program loaded successfully\n";
                    std::cout << "Words loaded: "
                              << program.size() << '\n';
                }
                catch (const std::exception& error) {
                    programLoaded = false;
                    std::cout << "Error: "
                              << error.what() << '\n';
                }

                break;
            }

            case 2: {
                if (!programLoaded) {
                    std::cout << "Load a program first\n";
                    break;
                }

                try {
                    std::size_t steps = cpu.run();

                    std::cout << "Execution finished\n";
                    std::cout << "Steps: " << steps << '\n';
                    std::cout << "PC: " << cpu.getPC() << '\n';
                    std::cout << "SP: " << cpu.getSP() << '\n';
                    std::cout << "Halted: "
                              << cpu.isHalted() << '\n';
                }
                catch (const std::exception& error) {
                    std::cout << "Execution error: "
                              << error.what() << '\n';
                }

                break;
            }

            case 3: {
                if (!programLoaded) {
                    std::cout << "Load a program first\n";
                    break;
                }

                if (cpu.isHalted()) {
                    std::cout << "CPU is already halted\n";
                    break;
                }

                try {
                    uint16_t pcBefore = cpu.getPC();

                    cpu.step();

                    std::cout << "Instruction executed\n";
                    std::cout << "Previous PC: " << pcBefore << '\n';
                    std::cout << "Current PC: " << cpu.getPC() << '\n';
                    std::cout << "SP: " << cpu.getSP() << '\n';

                    if (cpu.getSP() > 0) {
                        std::cout << "Top of stack: "
                                  << cpu.getTop() << '\n';
                    }
                    else {
                        std::cout << "Stack is empty\n";
                    }

                    std::cout << "Halted: "
                              << cpu.isHalted() << '\n';
                }
                catch (const std::exception& error) {
                    std::cout << "Execution error: "
                              << error.what() << '\n';
                }

                break;
            }


            case 4: {
                if (!programLoaded) {
                    std::cout << "Load a program first\n";
                    break;
                }

                std::cout << "\n===== CPU STATE =====\n";

                std::cout << "PC: " << cpu.getPC() << '\n';
                std::cout << "IR: " << cpu.getIR() << '\n';
                std::cout << "SP: " << cpu.getSP() << '\n';
                std::cout << "FLAGS: " << cpu.getFLAGS() << '\n';
                std::cout << "Halted: " << cpu.isHalted() << '\n';

                std::cout << "\nStack:\n";

                if (cpu.getSP() == 0) {
                    std::cout << "Stack is empty\n";
                }
                else {
                    for (std::size_t i = 0; i < cpu.getSP(); ++i) {
                        std::cout << "[" << i << "] = "
                                  << cpu.getStackAt(i);

                        if (i == 0) {
                            std::cout << " <- TOP";
                        }

                        std::cout << '\n';
                    }
                }

                break;
            }

            case 5: {
                if (!programLoaded) {
                    std::cout << "Load a program first\n";
                    break;
                }

                unsigned int startAddress;
                unsigned int count;

                std::cout << "Enter start address (decimal): ";
                if (!(std::cin >> startAddress)) {
                    std::cout << "Invalid address\n";
                    return 1;
                }

                std::cout << "Enter number of cells: ";
                if (!(std::cin >> count)) {
                    std::cout << "Invalid count\n";
                    return 1;
                }

                // Проверяем границы 16-битной памяти
                constexpr unsigned int MEMORY_SIZE = 65536;

                if (startAddress >= MEMORY_SIZE ||
                    count == 0 ||
                    count > MEMORY_SIZE - startAddress) {
                    std::cout << "Invalid memory range\n";
                    break;
                    }

                std::cout << "\n===== MEMORY =====\n";

                std::cout << std::left
                          << std::setw(12) << "Address"
                          << "Value\n";

                for (unsigned int i = 0; i < count; ++i) {
                    uint16_t address =
                        static_cast<uint16_t>(startAddress + i);

                    uint16_t value = cpu.readWord(address);

                    std::cout << "0x"
                              << std::right
                              << std::hex
                              << std::uppercase
                              << std::setw(4)
                              << std::setfill('0')
                              << address
                              << std::dec
                              << std::setfill(' ')
                              << "      "
                              << value
                              << '\n';
                }

                break;
            }

            case 6:
                std::cout << "Exiting emulator\n";
                return 0;

            default:
                std::cout << "Unknown option\n";
                break;
        }
    }

    return 0;
}
