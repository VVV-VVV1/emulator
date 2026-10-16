
#include <iostream>
#include "CPU.h"

int main() {
    CPU cpu;

    // Начальное значение счётчика
    cpu.loadWord(0x0800, 3);

    // Безусловный переход к началу цикла
    cpu.loadWord(0x0000, 0x8003); // PUSH 3
    cpu.loadWord(0x0001, 0x0008); // JMP

    // Завершение программы
    cpu.loadWord(0x0002, 0x000A); // HALT

    // Начало цикла (адрес 3)
    cpu.loadWord(0x0003, 0x8800); // PUSH 0x0800
    cpu.loadWord(0x0004, 0x0006); // READ
    cpu.loadWord(0x0005, 0x8001); // PUSH 1
    cpu.loadWord(0x0006, 0x0002); // SUB

    // Сохраняем уменьшенный счётчик
    cpu.loadWord(0x0007, 0x0003); // DUP
    cpu.loadWord(0x0008, 0x8800); // PUSH 0x0800
    cpu.loadWord(0x0009, 0x0007); // WRITE

    // Проверяем счётчик и повторяем цикл
    cpu.loadWord(0x000A, 0x8003); // PUSH 3
    cpu.loadWord(0x000B, 0x0009); // JNZ

    cpu.loadWord(0x000C, 0x000A); // HALT

    int steps = 0;

    while (!cpu.isHalted() && steps < 100) {
        cpu.step();
        ++steps;
    }

    std::cout << "PC = " << cpu.getPC() << '\n';
    std::cout << "SP = " << cpu.getSP() << '\n';
    std::cout << "Counter = "
              << cpu.readWord(0x0800) << '\n';
    std::cout << "Halted = "
              << cpu.isHalted() << '\n';
    std::cout << "Steps = " << steps << '\n';

    return 0;
}
