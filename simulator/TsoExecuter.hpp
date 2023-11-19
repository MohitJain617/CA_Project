#ifndef TSOEXECUTER_HPP
#define TSOEXECUTER_HPP

#include <unordered_map>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <queue> 
#include <vector>
#include "Executer.hpp"
#include "Memory.hpp"
#include "Program.hpp"

// Load Program from text file in a format the executer can understand
class TsoExecuter : public Executer{
public:
	TsoExecuter(Program& programToExecute, int executerId);
    void executeNextInstruction(Memory& memory) override;
    bool endOfProgram() override;
    void executeStoreBuffer(Memory& memory);
    void readInstruction(std::string instruction, Memory& memory);
    
private:
    void executeInstructionTSO(std::vector<std::string> operands, Memory& memory);
    std::queue <std::vector<std::string>> storeBuffer; // store buffer 
    std::unordered_map<std::string, int> registerDependency; // register dependency visited buffer
    std::unordered_map<std::string, int> memoryDependency; // register dependency visited buffer
    // Add other program-related data members as needed
};

#endif // EXECUTER_HPP