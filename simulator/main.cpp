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
    Program program1 = Program("programs/storeload1.txt");
    Program program2 = Program("programs/storeload2.txt");
    std::vector<Executer> cores;
    std::vector<bool> visited;

    if (std::strcmp(argv[1], "TSO") == 0){
        cores.push_back(TsoExecuter(program1, 1, true));
	    cores.push_back(TsoExecuter(program2, 2, true));
        visited.push_back(false);
        visited.push_back(false);
    }
    else if (std::strcmp(argv[1], "SC") == 0){
        cores.push_back(Executer(program1, 1, true));
        cores.push_back(Executer(program2, 2, true));
        visited.push_back(false);
        visited.push_back(false);
    }
    else{
        std::cout <<argv[1] <<std::endl;
    }
    int totalCores = cores.size();
    int completedCores = 0;

    srand(time(0));
    while(completedCores < totalCores){
        idx = rand() % (totalCores - completedCores);

        int actualIdx;
        // Iterate to the idx'th unvisited core
        for (actualIdx = 0; actualIdx < totalCores; actualIdx++) {
            if(visited[actualIdx] == false) {
                if (idx == 0) break;
                idx--;
            }
        }
        cores[actualIdx].executeNextInstruction(memory);
        if(cores[actualIdx].endOfProgram()){
            visited[actualIdx] = true;
            completedCores++;
            // programmes.erase(programmes.begin() + idx);
        }
    }
    
    std::unordered_map<std::string, int> registerC1 = cores[0].getRegisters();
    std::unordered_map<std::string, int> registerC2 = cores[1].getRegisters();
    std::unordered_map<std::string, int> memoryValues = memory.getMemoryVariables();
    
    std::cout <<"Printing register values for Core 1: "<<std::endl;
    for(auto it: registerC1){
        std::cout<<it.first <<": "<<it.second<<std::endl;
    }
    std::cout <<"Printing register values for Core 2: "<<std::endl;
    for(auto it: registerC2){
        std::cout<<it.first <<": "<<it.second<<std::endl;
    }
    std::cout <<"Printing values of variables from unified memory: "<<std::endl;
    for(auto it: memoryValues){
        std::cout<<it.first <<": "<<it.second<<std::endl;
    }

    
    return 0;
}
