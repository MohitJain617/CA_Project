#include "Memory.hpp"
#include "Program.hpp"
#include "Executer.hpp"

int main() {
    Memory memory;
    Program program("program.txt");
	Executer executer(program);

    // Coordinate the execution
	if (!executer.endOfProgram())
    	executer.executeNextInstruction(memory);

    return 0;
}
