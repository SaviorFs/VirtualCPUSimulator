#include "cpu.hpp"
#include <iostream>

// more later
enum Opcodes {
    MOV = 0x01, // this will move to an immediate value into a register
    ADD = 0x02, // this adds one register to another
    JMP = 0x03, // this jumps to a memory address
    SUB = 0x04, // this subtracts vals in registers
    CMP = 0x05, // compares two registers
    JZ  = 0x06, // jumps if the zeroFlag is set
    HLT = 0xFF, // this halts execution
};

// this is a constuctor that initalizes memory and registers
VirtualCPU::VirtualCPU() : pc(0), halted(false) {
    registers.fill(0);
    memory.fill(0);
}

// loads a vectory of bytes into memory starting at address 0
void VirtualCPU::loadProgram(const std::vector<uint8_t>& program) {
    for (size_t i = 0; i < program.size() && i < memory.size(); ++i) {
        memory[i] = program[i];
    }
}

void VirtualCPU::run() {
    while (!halted) {
        uint8_t opcode = memory[pc]; // fetches
        executeInstruction(opcode); // decode and execute
    }
}

// this will handles a single instruction
void VirtualCPU::executeInstruction(uint8_t opcode) {
    switch (opcode) {
        case MOV: {
            uint8_t reg = memory[++pc];
            uint8_t value = memory[++pc];
            registers[reg] = value;
            pc++;
            break;
        }

        case ADD: {
            uint8_t reg1 = memory[++pc];
            uint8_t reg2 = memory[++pc];
            registers[reg1] += registers[reg2];
            pc++;
            break;
        }

       case HLT: {
        halted = true;
        break;
       }
       
       case JMP: {
        uint8_t addr = memory[++pc];
        pc = addr;
        break;
}
       case SUB: {
        uint8_t reg1 = memory[++pc];
        uint8_t reg2 = memory[++pc];
        registers[reg1] -= registers[reg2];
        pc++;
        break;
}
        case CMP: {
            uint8_t reg1 = memory[++pc];
            uint8_t reg2 = memory[++pc];
            zeroFlag = (registers[reg1] == registers[reg2]);
            pc++;
            break;
}

        case JZ: {
            uint8_t addr = memory[++pc];
            if (zeroFlag) {
                pc = addr;
            } else {
                pc++;
            }
            break;
}

       default: {
        std::cerr << "Unknown opcode: " << static_cast<int>(opcode) << "\n";
        halted = true;
        break;
       }
    }
    
    printState();

}

// this prints registers and PC for debugging
void VirtualCPU::printState() const {
    std::cout << "PC: " << static_cast<int>(pc) << "\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << "R" << i << ": " << static_cast<int>(registers[i]) << " ";
    }
    std::cout << "\n---\n";
}