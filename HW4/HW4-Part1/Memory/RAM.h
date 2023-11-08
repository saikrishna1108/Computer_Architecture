

#ifndef RAM_H
#define RAM_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void initializeRAM(uint32_t ram[], int start, int end);
void loadInstructions(uint32_t [], const std::vector<uint32_t>& instructions, int instructionAddress);

#endif