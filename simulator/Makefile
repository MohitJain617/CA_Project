all: basiccompile litmuscompile

basiccompile:
	g++ main.cpp Program.cpp Memory.cpp Executer.cpp TsoExecuter.cpp -o ProgramSimulator

litmuscompile:
	g++ litmus_tests.cpp Program.cpp Memory.cpp Executer.cpp TsoExecuter.cpp -o LitmusTester

clean:
	rm -f ProgramSimulator LitmusTester