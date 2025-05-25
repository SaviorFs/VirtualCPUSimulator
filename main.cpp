#include "cpu.hpp"
#include <vector>
#include <iostream>

std::vector<uint8_t> assemble(const std::string& filename); // declare

int main() {
    VirtualCPU cpu;

    std::vector<uint8_t> program = assemble("programs/test.asm");
    std::cout << "Loaded program size: " << program.size() << " bytes\n";

    cpu.loadProgram(program);
    cpu.run();

    std::cout << "Final CPU State:\n";
    cpu.printState();

    return 0;
}