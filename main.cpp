
#include <iostream>
#include "CPU.h"

int main() {
    CPU cpu;

    cpu.loadWord(0x0000, 0x800A); // PUSH 10
    cpu.loadWord(0x0001, 0x8014); // PUSH 20
    cpu.loadWord(0x0002, 0x0001); // ADD

    cpu.step();
    cpu.step();
    cpu.step();

    std::cout << "PC = " << cpu.getPC() << '\n';
    std::cout << "SP = " << cpu.getSP() << '\n';
    std::cout << "TOP = " << cpu.getTop() << '\n';

    return 0;
}
