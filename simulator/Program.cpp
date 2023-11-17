#include "Program.hpp"

Program::Program(std::string filename) {
    // Fetch instructions in file name and store each instruction
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        //handling error in opening file (can create a function later)
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line == "") continue;
        instructions.push_back(line);
        // std:: cout <<line <<std::endl;
    }
    // std:: cout <<instructions.size() <<std::endl;
    file.close();
}

std::string Program::getNextInstruction() {
    return instructions[instructionPointer++];
}

bool Program::hasNextInstruction() {
    // std::cout<<instructionPointer<<std::endl;
    return instructionPointer < instructions.size();
}