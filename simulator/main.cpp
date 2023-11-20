#include "Memory.hpp"
#include "Program.hpp"
#include "Executer.hpp"
#include "TsoExecuter.hpp"
#include <vector> 
#include <cstring>
#include "time.h"

int main(int argc, char *argv[]) {
    int length;
    int idx;
    Memory memory;
    Program program1 = Program("programs/program1.txt");
    Program program2 = Program("programs/program2.txt");
    std::vector<Executer> cores;
    
    if (std::strcmp(argv[1], "TSO") == 0){
        cores.push_back(TsoExecuter(program1, 1));
	    cores.push_back(TsoExecuter(program2, 2));
    }
    else if (std::strcmp(argv[1], "SC") == 0){
        cores.push_back(Executer(program1, 1));
        cores.push_back(Executer(program2, 2));
    }
    else{
        std::cout <<argv[1] <<std::endl;
    }

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
