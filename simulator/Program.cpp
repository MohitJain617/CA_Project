#include "Program.hpp"

Program::Program(std::string filename) {
    // Fetch instructions in file name and store each instruction
}

std::string Program::getNextInstruction() {
    return instructions[instructionPointer++];
}

bool Program::hasNextInstruction() {
    return instructionPointer < instructions.size();
}