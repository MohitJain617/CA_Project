#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <unordered_map>

class Memory {
public:
    Memory();
    void store(std::string address, int data);
    int load(std::string address) const;

private:
    std::unordered_map<std::string, int> memoryData;
};

#endif // MEMORY_HPP