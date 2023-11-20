#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <unordered_map>

class Memory {
public:
    Memory();
    void store(std::string address, int data);
    int load(std::string address) const;
    std::unordered_map<std::string, int> getMemoryVariables();

private:
    std::unordered_map<std::string, int> memoryData; // storing values
};

#endif // MEMORY_HPP