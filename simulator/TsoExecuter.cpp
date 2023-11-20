#include "TsoExecuter.hpp"

// Initialize registers and registerDependency, along with storing program.
TsoExecuter::TsoExecuter(Program& programToExecute, int eId, bool verbose) : Executer(programToExecute, eId, verbose) {
    std::vector<std::string> registerNames = {"R1", "R2", "R3", "R4", "R5", "R6"};
    for (std::string registerName : registerNames){
        registers[registerName] = 0;
        registerDependency[registerName] = 0;
    }
}

void TsoExecuter::executeInstructionTSO(std::vector<std::string> operands, Memory& memory){
    // Printing the instruction currently being executed.
    if (verbose){
        std::cout <<"Core " <<executerId << " : ";
        for (std::string operand : operands){
            std::cout <<operand << " ";
        }
        std::cout<<"\n";
    }
    if(operands[0] == "Store"){
        memory.store(operands[1], registers[operands[2]]);
        memoryDependency[operands[1]] = 0;
        registerDependency[operands[2]] = 0;
    }
    else if (operands[0] == "Load"){
        registers[operands[1]] = memory.load(operands[2]);
    }
    else if (operands[1] == "="){
        registers[operands[0]] = stoi(operands[2]);
    }
}

void TsoExecuter::readInstruction(std::string instruction, Memory& memory){
    std::istringstream iss(instruction);
    std::vector<std::string> operands;
    std::string word;
    // Read each word from the stream
    while (iss >> word) {
        operands.push_back(word);
    }
    if (operands[0] == "Load") {
        // Check for dependency in Store Buffer
        if(memoryDependency[operands[2]] == 0 && registerDependency[operands[1]] == 0){
            executeInstructionTSO(operands, memory);
        }
        else {
            // Execute store buffer before executing this instruction
            executeStoreBuffer(memory);
            executeInstructionTSO(operands, memory);
        }
            
    }
    else if (operands[0] == "Store") {
        // Add Dependency, to lazy execute store
        memoryDependency[operands[1]] = 1;
        registerDependency[operands[2]] = 1;
        storeBuffer.push(operands);
    } 
    else if (operands[1] == "=") {
        // Check for dependency in Store Buffer
        if(registerDependency[operands[0]] == 0){
            executeInstructionTSO(operands, memory);
        }
        else {
            // Execute store buffer before executing this instruction
            executeStoreBuffer(memory);
            executeInstructionTSO(operands, memory);
        }
    }
}

void TsoExecuter::executeStoreBuffer(Memory& memory){
    if (storeBuffer.empty()){
        return;
    }
    while(!storeBuffer.empty()){
        std::vector<std::string> operands = storeBuffer.front();
        storeBuffer.pop();
        executeInstructionTSO(operands, memory);
    }
}

// Override
void TsoExecuter::executeNextInstruction(Memory& memory) {
    if(program.hasNextInstruction()) {
        std::string nextInstruction = program.getNextInstruction();
        readInstruction(nextInstruction, memory);
    }
    else {
        executeStoreBuffer(memory);
    }
}

// Override
bool TsoExecuter::endOfProgram() {
    return !program.hasNextInstruction() && storeBuffer.empty();
}