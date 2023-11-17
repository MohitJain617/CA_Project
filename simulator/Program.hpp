#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

// Load Program from text file in a format the executer can understand
class Program {
public:
    Program(std::string filename);
    std::string getNextInstruction();
    bool hasNextInstruction();

private:
    std::vector<std::string> instructions;
    int instructionPointer = 0;
};

#endif // PROGRAM_HPP