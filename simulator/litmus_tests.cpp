#include "Memory.hpp"
#include "Program.hpp"
#include "Executer.hpp"
#include "TsoExecuter.hpp"
#include <vector> 
#include "time.h"

int main(int argc, char *argv[]) {
    std::string model = argv[1];
	std::string litmusTestType = argv[2];

    int length;
    int idx;
	int iterations = 1000; // Number of iterations
	while(iterations--){
		Memory memory;
		// std::vector<TsoExecuter> cores;
		std::vector<Executer> cores;
		if (litmusTestType == "store_store") {
			Program program1 = Program("programs/storestore1.txt");
			Program program2 = Program("programs/storestore2.txt");
			if (model == "TSO"){
				cores.push_back(TsoExecuter(program1, 1));
				cores.push_back(TsoExecuter(program2, 2));
			} else {
				cores.push_back(Executer(program1, 1));
				cores.push_back(Executer(program2, 2));
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
		} else if (litmusTestType == "store_load") {

		} else if(litmusTestType == "load_load") {

		} else if(litmusTestType == "load_store") {
			
		} else {
			std::cout << "Invalid litmus test type" << std::endl;
			return 0;
		}

	}
    
    return 0;
}
