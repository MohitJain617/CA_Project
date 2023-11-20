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
	int reorders = 0;
	int noreorders = 0;
	while(iterations--){
		Memory memory;
		// std::vector<TsoExecuter> cores;
		std::vector<Executer> cores;
		if (litmusTestType == "store_store") {

			Program program1 = Program("programs/storestore1.txt");
			Program program2 = Program("programs/storestore2.txt");
			if (model == "TSO"){
				cores.push_back(TsoExecuter(program1, 1, false));
				cores.push_back(TsoExecuter(program2, 2, false));
			} else {
				cores.push_back(Executer(program1, 1, false));
				cores.push_back(Executer(program2, 2, false));
			}
			Executer& core1 = cores[0];
			Executer& core2 = cores[1];
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
			// Check for reordering
			if (core2.getRegisterValue("R1") == 1 && core2.getRegisterValue("R2") == 0) {
				reorders++;
			} else {
				noreorders++;
			}

		} else if (litmusTestType == "store_load") {

			Program program1 = Program("programs/storeload1.txt");
			Program program2 = Program("programs/storeload2.txt");
			if (model == "TSO"){
				cores.push_back(TsoExecuter(program1, 1, false));
				cores.push_back(TsoExecuter(program2, 2, false));
			} else {
				cores.push_back(Executer(program1, 1, false));
				cores.push_back(Executer(program2, 2, false));
			}
			Executer& core1 = cores[0];
			Executer& core2 = cores[1];
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
			// Check for reordering
			if (core1.getRegisterValue("R1") == 0 && core2.getRegisterValue("R2") == 0) {
				reorders++;
			} else {
				noreorders++;
			}

		} else if(litmusTestType == "load_load") {

			Program program1 = Program("programs/loadload1.txt");
			Program program2 = Program("programs/loadload2.txt");
			if (model == "TSO"){
				cores.push_back(TsoExecuter(program1, 1, false));
				cores.push_back(TsoExecuter(program2, 2, false));
			} else {
				cores.push_back(Executer(program1, 1, false));
				cores.push_back(Executer(program2, 2, false));
			}
			Executer& core1 = cores[0];
			Executer& core2 = cores[1];
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
			// Check for reordering
			if (core2.getRegisterValue("R1") == 1 && core2.getRegisterValue("R2") == 0) {
				reorders++;
			} else {
				noreorders++;
			}

		} else if(litmusTestType == "load_store") {
			
			Program program1 = Program("programs/loadstore1.txt");
			Program program2 = Program("programs/loadstore2.txt");
			if (model == "TSO"){
				cores.push_back(TsoExecuter(program1, 1, false));
				cores.push_back(TsoExecuter(program2, 2, false));
			} else {
				cores.push_back(Executer(program1, 1, false));
				cores.push_back(Executer(program2, 2, false));
			}
			Executer& core1 = cores[0];
			Executer& core2 = cores[1];
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
			// Check for reordering
			if (core1.getRegisterValue("R1") == 1 && core2.getRegisterValue("R2") == 1) {
				reorders++;
			} else {
				noreorders++;
			}

		} else {
			std::cout << "Invalid litmus test type\n";
			return 0;
		}

	}
    std::cout<<"Re-orders: "<<reorders<<"\n";
	std::cout<<"No Re-orders: "<<noreorders<<"\n";
    return 0;
}
