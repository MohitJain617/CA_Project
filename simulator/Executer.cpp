#include "Executer.hpp"

Executer::Executer(Program& programToExecute) : program(programToExecute){
    registers["R1"] = 0;
    registers["R2"] = 0;
    registers["R3"] = 0;
    registers["R4"] = 0;
    registers["R5"] = 0;
    registers["R6"] = 0;
}

void Executer::executeInstruction(std::string instruction, Memory& memory) {
    // Parse instruction
    // Execute instruction
    // Store X R1
    std::cout <<instruction <<std::endl;
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