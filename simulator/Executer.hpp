#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include <unordered_map>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "Memory.hpp"
#include "Program.hpp"

// Load Program from text file in a format the executer can understand
class Executer {
public:
	Executer(Program& programToExecute);
    void executeNextInstruction(Memory& memory);
    bool endOfProgram();

private:
    void executeInstruction(std::string instruction, Memory& memory);
    std::unordered_map<std::string, int> registers;
	Program program;
    // Add other program-related data members as needed
};

#endif // EXECUTER_HPP