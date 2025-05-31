#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <cstdint>

// Instruction opcodes
std::unordered_map<std::string, uint8_t> opcodes = {
    {"MOV", 0x01},
    {"ADD", 0x02},
    {"JMP", 0x03},
    {"SUB", 0x04},
    {"CMP", 0x05},
    {"JZ",  0x06},
    {"HLT", 0xFF},
};

// Register encodings
std::unordered_map<std::string, uint8_t> registers = {
    {"R0", 0x00},
    {"R1", 0x01},
    {"R2", 0x02},
    {"R3", 0x03},
};

// this trims whitespace from both ends of a string
std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

std::vector<uint8_t> assemble(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;
    std::unordered_map<std::string, uint8_t> labels;
    uint8_t address = 0;

    // first we find labels and calculate addresses
    while (std::getline(file, line)) {
        auto comment_pos = line.find(';');
        if (comment_pos != std::string::npos)
            line = line.substr(0, comment_pos);

        line = trim(line);
        if (line.empty()) continue;

        if (line.back() == ':') {
            std::string label = line.substr(0, line.size() - 1);
            labels[label] = address;
        } else {
            lines.push_back(line);

            std::istringstream iss(line);
            std::string instr;
            iss >> instr;
            std::transform(instr.begin(), instr.end(), instr.begin(), ::toupper);

            if (instr == "MOV") address += 3;
            else if (instr == "ADD") address += 3;
            else if (instr == "SUB") address += 3;
            else if (instr == "CMP") address += 3;
            else if (instr == "JMP") address += 2;
            else if (instr == "JZ")  address += 2;
            else if (instr == "HLT") address += 1;
        }
    }

    // second we assemble the instructions
    std::vector<uint8_t> program;
    for (const std::string& raw_line : lines) {
        std::istringstream iss(raw_line);
        std::string instr;
        iss >> instr;
        std::transform(instr.begin(), instr.end(), instr.begin(), ::toupper);

        if (opcodes.count(instr) == 0) {
            std::cerr << "Unknown instruction: " << instr << "\n";
            continue;
        }

        program.push_back(opcodes[instr]);

        if (instr == "MOV") {
            std::string reg;
            int value;
            iss >> reg >> value;
            program.push_back(registers[reg]);
            program.push_back(static_cast<uint8_t>(value));
        } else if (instr == "ADD" || instr == "SUB") {
            std::string r1, r2;
            iss >> r1 >> r2;
            program.push_back(registers[r1]);
            program.push_back(registers[r2]);
        } else if (instr == "JMP") {
            std::string target;
            iss >> target;
        } else if (instr == "CMP") {
            std::string r1, r2;
            iss >> r1 >> r2;
            program.push_back(registers[r1]);
            program.push_back(registers[r2]);
        } else if (instr == "JZ") {
            std::string target;
            iss >> target;

            if (labels.count(target)) {
                program.push_back(labels[target]);
            } else {
                program.push_back(static_cast<uint8_t>(std::stoi(target)));
            }

            if (labels.count(target)) {
                program.push_back(labels[target]);
            } else {
                // If it's a number we jump to that address
                program.push_back(static_cast<uint8_t>(std::stoi(target)));
            }
        }
    }

    return program;
}
