#include "Memory.hpp"
#include "Program.hpp"
#include "Executer.hpp"
#include "TsoExecuter.hpp"
#include <vector> 
#include "time.h"
#include <memory>

int main(int argc, char *argv[]) {
    std::string model = argv[1];
	std::string litmusTestType = argv[2];

    int length;
    int idx;
	int iterations = 5000; // Number of iterations
	int reorders = 0;
	int noreorders = 0;
	while(iterations--){
		Memory memory;
		// std::vector<TsoExecuter> cores;
		std::vector<std::shared_ptr<Executer>> cores;
    	std::vector<bool> visited;
    	visited.push_back(false);
    	visited.push_back(false);
    	int totalCores = 2;
    	int completedCores = 0;

		if (litmusTestType == "store_store") {

			Program program1 = Program("programs/storestore1.txt");
			Program program2 = Program("programs/storestore2.txt");
			if (model == "TSO"){
				cores.push_back(std::make_shared<TsoExecuter>(program1, 1, false));
				cores.push_back(std::make_shared<TsoExecuter>(program2, 2, false));
			} else {
				cores.push_back(std::make_shared<Executer>(program1, 1, false));
				cores.push_back(std::make_shared<Executer>(program2, 2, false));
			}
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
				cores[actualIdx]->executeNextInstruction(memory);
				if(cores[actualIdx]->endOfProgram()){
					visited[actualIdx] = true;
					completedCores++;
					// programmes.erase(programmes.begin() + idx);
				}
			}
			// Check for reordering
			if (cores[1]->getRegisterValue("R1") == 1 && cores[1]->getRegisterValue("R2") == 0) {
				reorders++;
			} else {
				noreorders++;
			}

		} else if (litmusTestType == "store_load") {

			Program program1 = Program("programs/storeload1.txt");
			Program program2 = Program("programs/storeload2.txt");
			if (model == "TSO"){
				cores.push_back(std::make_shared<TsoExecuter>(program1, 1, false));
				cores.push_back(std::make_shared<TsoExecuter>(program2, 2, false));
			} else {
				cores.push_back(std::make_shared<Executer>(program1, 1, false));
				cores.push_back(std::make_shared<Executer>(program2, 2, false));
			}

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
				cores[actualIdx]->executeNextInstruction(memory);
				if(cores[actualIdx]->endOfProgram()){
					visited[actualIdx] = true;
					completedCores++;
					// programmes.erase(programmes.begin() + idx);
				}
			}
			// Check for reordering
			if (cores[0]->getRegisterValue("R1") == 0 && cores[1]->getRegisterValue("R2") == 0) {
				reorders++;
			} else {
				noreorders++;
			}

		} else if(litmusTestType == "load_load") {

			Program program1 = Program("programs/loadload1.txt");
			Program program2 = Program("programs/loadload2.txt");
			if (model == "TSO"){
				cores.push_back(std::make_shared<TsoExecuter>(program1, 1, false));
				cores.push_back(std::make_shared<TsoExecuter>(program2, 2, false));
			} else {
				cores.push_back(std::make_shared<Executer>(program1, 1, false));
				cores.push_back(std::make_shared<Executer>(program2, 2, false));
			}
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
				cores[actualIdx]->executeNextInstruction(memory);
				if(cores[actualIdx]->endOfProgram()){
					visited[actualIdx] = true;
					completedCores++;
					// programmes.erase(programmes.begin() + idx);
				}
			}
			// Check for reordering
			if (cores[1]->getRegisterValue("R1") == 1 && cores[1]->getRegisterValue("R2") == 0) {
				reorders++;
			} else {
				noreorders++;
			}

		} else if(litmusTestType == "load_store") {
			
			Program program1 = Program("programs/loadstore1.txt");
			Program program2 = Program("programs/loadstore2.txt");
			if (model == "TSO"){
				cores.push_back(std::make_shared<TsoExecuter>(program1, 1, false));
				cores.push_back(std::make_shared<TsoExecuter>(program2, 2, false));
			} else {
				cores.push_back(std::make_shared<Executer>(program1, 1, false));
				cores.push_back(std::make_shared<Executer>(program2, 2, false));
			}
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
				cores[actualIdx]->executeNextInstruction(memory);
				if(cores[actualIdx]->endOfProgram()){
					visited[actualIdx] = true;
					completedCores++;
					// programmes.erase(programmes.begin() + idx);
				}
			}
			// Check for reordering
			if (cores[0]->getRegisterValue("R1") == 1 && cores[1]->getRegisterValue("R2") == 1) {
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
