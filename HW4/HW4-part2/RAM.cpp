#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "RAM.h"
#include "globalvar.h"



// Function to initialize the RAM with random FP32 values

void initializeRAM(uint32_t ran[],int start, int end) {
    for (int i = start; i <= end; ++i) {
        RAM_COUNT += 1;
        ram[i] = static_cast<int>(rand())/10.0f; // Use rand() directly
    }
}


// Function to load instructions into RAM
void loadInstructions(uint32_t ram[], const std::vector<uint32_t>& instructions, int instructionAddress) {
    for (const uint32_t& inst : instructions) {
        RAM_COUNT += 1;
        ram[instructionAddress++] = inst;
    }
}
