
#include <iostream>
#include "CPU.h"
#include "Assembler.h"

int main() {
    CPU cpu;
    Assembler assembler;

    std::vector<AssembledWord> program =
        assembler.assembleFile("program.asm");

    for (const AssembledWord& word : program) {
        cpu.loadWord(word.address, word.value);
    }

    std::size_t steps = cpu.run();

    std::cout << "SUM = "
              << cpu.readWord(0x0805) << '\n';
    std::cout << "INDEX = "
              << cpu.readWord(0x0806) << '\n';
    std::cout << "COUNT = "
              << cpu.readWord(0x0807) << '\n';
    std::cout << "SP = " << cpu.getSP() << '\n';
    std::cout << "Halted = "
              << cpu.isHalted() << '\n';
    std::cout << "Steps = " << steps << '\n';

    return 0;
}
