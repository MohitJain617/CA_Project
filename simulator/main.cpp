#include "Memory.hpp"
#include "Program.hpp"
#include "Executer.hpp"
#include "TsoExecuter.hpp"
#include <vector> 
#include "time.h"

int main() {
    int length;
    int idx;
    Memory memory;
    // std::vector<TsoExecuter> cores;
    std::vector<Executer> cores;
    Program program1 = Program("/home/monsoon2023/abhik20165/CA_Project/simulator/program/program1.txt");
    cores.push_back(Executer(program1, 1));
    Program program2 = Program("/home/monsoon2023/abhik20165/CA_Project/simulator/program/program2.txt");
	cores.push_back(Executer(program2, 2));

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
