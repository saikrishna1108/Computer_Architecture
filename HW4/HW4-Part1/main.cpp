#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "RAM.h"
#include <string>
#include <bitset>
#include <algorithm>
#include <unordered_map>
#include <stdio.h>
#include "decoder.h"
#include "execute.h"
#include "globalvar.h"



 int INSTRUCTION_START = 0x0;
 int INSTRUCTION_END = 0x093;
int STACK_START = 0x200;
 int STACK_END = 0x2FF;
 int ARRAY_A_START = 0x400;
  int ARRAY_A_END = 0x7FF;
 int ARRAY_B_START = 0x800;
  int ARRAY_B_END = 0xBFF;
 int ARRAY_C_START = 0xC00;
 int ARRAY_C_END = 0xFFF;
 const int RAM_SIZE = 0x13FF;
int RAM_COUNT = 0;
 uint32_t ram[0x13FF];
 int clockCycle = 0;
int main(){
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = STACK_START; i <= STACK_END; ++i) {
        ram[i] = 0.0f;
    }
    initializeRAM(ram, ARRAY_A_START, ARRAY_A_END);
    initializeRAM(ram, ARRAY_B_START, ARRAY_B_END);
    

  const std::vector<uint32_t> instr = {
  0b0000000000000000010000100000011
    ,0b0000000000000001010000110000011
  ,0b0000000000000010000000100110011
 ,0b0000000000000011000000110110011
    ,0b0000000000000010010001100000111
  ,0b0000000000000011010001110000111
      ,0b0000000011000111000010001010011
      ,0b0000000000000010010001000000011
          ,0b0000000000000100000001000110011
         ,0b0000000100000100010000000100111
         ,0b0000000000100000000000000010011
        ,0b0010000000001001000000010010011
   ,0b0000000000100000100000001100011
};


    loadInstructions(ram, instr,INSTRUCTION_START);


    // Pipelined Structure:

    int i = 0;
    uint32_t instruction;
    int k = INSTRUCTION_START;
    int inst_count = 0;
    int t = 22;
  while (t > 0) {
    for (int stage = 1; stage <= 3; stage++) {
        clockCycle += 1;
        std::cout<< "Clock Cycle : " << clockCycle<<"  ";
        if (stage == 1) {
            instruction = ram[k + i];
            RAM_COUNT+=1;
            std::cout << "FETCH INSTRUCTION: " << instruction << "\n";
            inst_count++;
            i = i + 1;
        } else if (stage == 2) {
            std::cout << "DECODE INSTRUCTION: " <<checkOpcode(instruction)<< "\n";
            runDecoder(instruction);
          
            
        } else if (stage == 3) {
            std::cout << "EXECUTE INSTRUCTION: " << checkOpcode(instruction) << "\n";
            std::string condition = runExecute(instruction);
         
            if (condition == "loop start") {
                i = 0;
            }
            if (condition == "exit") {
                t = -1; // Set t to 0 to exit the while loop
                break; // Break out of the for loop
            }
        }
    }
}

    
    std::cout << "\n";
    std::cout <<"Clockcycles: "<<clockCycle << "\n";
    std::cout <<"instrctions executed: "<<inst_count << "\n";
   std::cout << "CPI: " << clockCycle/inst_count <<"\n"; //CPI = Total program execution cycles / Instructions count
   std::cout << "Total number of RAM Read/Write Latency: "<< RAM_COUNT << "\n";
    
      for (int i = 0; i < 256; i++) {
        std::cout << output[i] << std::endl;
    }
    std::cout << "Array A" << "\n";
    for(i = 0; i <256; i++){
    std::cout << ram[i+ARRAY_A_START] << ", ";
    }
    std::cout  << "\n";
     std::cout << "Array B" << "\n";
    for(i =0; i < 256; i++){
    std::cout << ram[i+ARRAY_B_START] << ", ";
    }
    std::cout  << "\n";

     std::cout << "Array C" << "\n";
    for(i = 0; i < 256; i++){
    std::cout << ram[i+ARRAY_C_START] << ", ";
    }
    return 0;
}


 