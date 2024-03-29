#include "Memory.hpp"

Memory::Memory() {}

void Memory::store(std::string address, int data) {
    memoryData[address] = data;
}

std::unordered_map<std::string, int> Memory:: getMemoryVariables(){
    return memoryData;
}

int Memory::load(std::string address) const {
    auto it = memoryData.find(address);
    if (it != memoryData.end()) {
        return it->second;
    } else {
        // std::cerr << "Error: Attempted to load from an invalid memory address: " << address << std::endl;
        return 0; // Return default as 0
    }
}