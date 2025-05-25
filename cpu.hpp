#ifndef CPU_HPP
#define CPU_HPP

#include <array>
#include <vector>
#include <cstdint>

class VirtualCPU {
public:
    VirtualCPU(); 

    // this loads a program which is a vector of bytes into memory starting at address 0
    void loadProgram(const std::vector<uint8_t>& program);

    // this just runs the CPU it operates with a fetch-decode-execute loop
    void run();

    // print registers and pc (program counter)
    void printState() const;

private:
    std::array<uint8_t, 4> registers;      // R0, R1, R2, R3
    std::array<uint8_t, 256> memory;       // 256 bytes of RAM
    uint8_t pc;                            // Program counter
    bool halted;                           // Halt flag

    // Handle a single instruction based on opcode
    void executeInstruction(uint8_t opcode);
};

#endif 
