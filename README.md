# Virtual CPU Simulator

This project is a fully custom, educational CPU simulator written in C++. It emulates a simplified processor with its own instruction set, memory, and registers. The CPU reads binary programs (or assembled `.asm` files), decodes instructions, and executes them step-by-step like a real processor.

## 🚀 Features
- 4 general-purpose 8-bit registers (R0–R3)
- 256 bytes of memory
- Instruction set includes `MOV`, `ADD`, `JMP`, and `HLT`
- Manual program loader and instruction executor
- Prints CPU state after every instruction for learning and debugging

## 📂 Project Structure

VirtualCPUSimulator/
├── cpu.cpp # CPU implementation
├── cpu.hpp # CPU class definition
├── main.cpp # Entry point to run the simulator
├── programs/ # Contains test .asm programs
├── assembler.cpp # (Coming Soon) Assembler from .asm to bytecode
└── README.md # This file

## 🧠 Learning Goals
This project is designed to teach:
- How real CPUs fetch-decode-execute instructions
- How memory, registers, and program counters work
- Basic assembly language design
- Emulator architecture

## 📜 License
This project is licensed under the MIT License. See `LICENSE` for details.
