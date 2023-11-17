#include "Memory.hpp"
#include "Program.hpp"
#include "Executer.hpp"
#include <vector> 
#include "time.h"

int main() {
    int length;
    int idx;
    Memory memory;
    std::vector<Executer> cores;
    // std::vector<Program> programmes;
    Program program1 = Program("program1.txt");
    // programmes.push_back(program1);
    cores.push_back(Executer(program1));
    Program program2 = Program("program2.txt");
    // programmes.push_back(program2);
	cores.push_back(Executer(program2));
    // Coordinate the execution
    srand(time(0));
    while(!cores.empty()){
        length = cores.size();
        idx = rand() % length;
        cores[idx].executeNextInstruction(memory);
        if(cores[idx].endOfProgram()){
            cores.erase(cores.begin() + idx);
            // programmes.erase(programmes.begin() + idx);
        }
    }
    
    return 0;
}
