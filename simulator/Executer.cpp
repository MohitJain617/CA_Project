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
}

void Executer::executeNextInstruction(Memory& memory) {
    std::string nextInstruction = program.getNextInstruction();
    executeInstruction(nextInstruction, memory);
}

bool Executer::endOfProgram() {
    return !program.hasNextInstruction();
}