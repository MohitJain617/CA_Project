#include "Memory.hpp"
#include "Program.hpp"
#include "Executer.hpp"
#include "Tsoexecuter.hpp"
#include <vector> 
#include "time.h"

int main() {
    int length;
    int idx;
    Memory memory;
    std::vector<Executer> cores;
    // std::vector<Tsoexecuter> cores;
    Program program1 = Program("program1.txt");
    cores.push_back(Executer(program1));
    // cores.push_back(Tsoexecuter(program1));
    Program program2 = Program("program2.txt");
	cores.push_back(Executer(program2));
	// cores.push_back(Tsoexecuter(program2));

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
