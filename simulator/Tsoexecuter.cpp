#include "Tsoexecuter.hpp"

Tsoexecuter::Tsoexecuter(Program& programToExecute) : program(programToExecute){
    registers["R1"] = 0;
    registers["R2"] = 0;
    registers["R3"] = 0;
    registers["R4"] = 0;
    registers["R5"] = 0;
    registers["R6"] = 0;
    registerDependency["R1"] = 0;
    registerDependency["R2"] = 0;
    registerDependency["R3"] = 0;
    registerDependency["R4"] = 0;
    registerDependency["R5"] = 0;
    registerDependency["R6"] = 0;
}

void Tsoexecuter::executeInstruction(std::vector<std::string> operands, Memory& memory){
    if(operands[0] == "Store"){
        memory.store(operands[1], registers[operands[2]]);
        memoryDependency[operands[1]] = 0;
        registerDependency[operands[2]] = 0;
    }
    else if (operands[0] == "Load"){
        registers[operands[1]] = memory.load(operands[2]);
        memoryDependency[operands[2]] = 0;
        registerDependency[operands[1]] = 0;
    }
    else if (operands[1] == "="){
        registers[operands[0]] = stoi(operands[2]);
    }
}

void Tsoexecuter::readInstruction(std::string instruction, Memory& memory){
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
    if (operands[0] == "Load"){
        if(memoryDependency[operands[1]] == 0 && registerDependency[operands[2]] == 0){
            executeInstruction(operands, memory);
        }
        else {
            executeStoreBuffer(memory);
            executeInstruction(operands, memory);
        }
            
    }
    else if (operands[0] == "Store"){
        memoryDependency[operands[1]] = 1;
        registerDependency[operands[2]] = 1;
        storeBuffer.push(operands);
    }
}

void Tsoexecuter::executeStoreBuffer(Memory& memory){
    if (storeBuffer.empty()){
        return;
    }
    while(!storeBuffer.empty()){
        std::vector<std::string> operands = storeBuffer.front();
        storeBuffer.pop();
        executeInstruction(operands, memory);
    }
}

void Tsoexecuter::executeNextInstruction(Memory& memory) {
    std::string nextInstruction = program.getNextInstruction();
    readInstruction(nextInstruction, memory);
    if(!program.hasNextInstruction()){
        executeStoreBuffer(memory);
    }
}

bool Tsoexecuter::endOfProgram() {
    return !program.hasNextInstruction() && storeBuffer.empty();
}