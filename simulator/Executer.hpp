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
	Executer(Program& programToExecute, int executerId, bool verbose);
    virtual void executeNextInstruction(Memory& memory);
    virtual bool endOfProgram();
    int getRegisterValue(std::string registerName);
    std::unordered_map<std::string, int> getRegisters();

protected:
    void executeInstruction(std::string instruction, Memory& memory);
    std::unordered_map<std::string, int> registers;
	Program program;
    int executerId;
    bool verbose;
    // Add other program-related data members as needed
};

#endif // EXECUTER_HPP