#include "Executer.hpp"

Executer::Executer(Program& programToExecute, int eId, bool verbose) : program(programToExecute), executerId(eId), verbose(verbose){
    std::vector<std::string> registerNames = {"R1", "R2", "R3", "R4", "R5", "R6"};
    for (std::string registerName : registerNames){
        registers[registerName] = 0;
    }
}

std::unordered_map<std::string, int> Executer::getRegisters(){
    return registers;
}

int Executer::getRegisterValue(std::string registerName){
    return registers[registerName];
}

void Executer::executeInstruction(std::string instruction, Memory& memory) {
    if(verbose){
        std::cout <<"Core " <<executerId << " : ";
        std::cout <<instruction <<std::endl;
    }
    std::istringstream iss(instruction);
    std::vector<std::string> operands;
    std::string word;
    // Read each word from the stream
    while (iss >> word) {
        // Process or store the word as needed
        // std:: cout <<word <<std::endl;
        operands.push_back(word);
    }
    if(operands[0] == "Store"){
        memory.store(operands[1], registers[operands[2]]);

    }
    else if (operands[0] == "Load"){
        registers[operands[1]] = memory.load(operands[2]);
    }
    else if (operands[1] == "="){
        registers[operands[0]] = stoi(operands[2]);
    }
}

void Executer::executeNextInstruction(Memory& memory) {
    std::string nextInstruction = program.getNextInstruction();
    executeInstruction(nextInstruction, memory);
}

bool Executer::endOfProgram() {
    return !program.hasNextInstruction();
}