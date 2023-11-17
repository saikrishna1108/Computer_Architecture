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
#include "bus.cpp"
 int INSTRUCTION_START1 = 0x0;
 int INSTRUCTION_END1 = 0x093;
  int INSTRUCTION_START2 = 0x100;
 int INSTRUCTION_END2 = 0x193;
int STACK_START1 = 0x200;
 int STACK_END1 = 0x2FF;
 int STACK_START2 = 0x300;
 int STACK_END2 = 0x7FF;
 int ARRAY_A_START = 0x400;
  int ARRAY_A_END = 0x7FF;
 int ARRAY_B_START = 0x800;
  int ARRAY_B_END = 0xBFF;
 int ARRAY_C_START = 0xC00;
 int ARRAY_C_END = 0xFFF;
 int ARRAY_D_START = 0x1000;
 int ARRAY_D_END = 0x13FF;
 const int RAM_SIZE = 0x13FF;
 uint32_t ram[0x13FF];
 int clockCycle = 1;
 int clockCycle2 = 1;
 int inst_count1 = 0;
 int inst_count2 = 0;
 bool cpu1_finished = false;
bool cpu2_finished = false;
int i = 0;
uint32_t instruction1;
int k = INSTRUCTION_START1;
int j = 0;
uint32_t instruction2;
int l = INSTRUCTION_START2;
int RAM_COUNT = 0;
bool t0 = true;
BusArbitration bus2;
std::string runcpu1(int stage){
    std::cout << "CPU1 Clockcycle :" << clockCycle << " :";
    clockCycle++;
    if (stage == 1) {
            instruction1 = bus2.getDataFromRAM(i+k);
            RAM_COUNT+=1;
            std::cout << "FETCH INSTRUCTION: " << instruction1 << "\n";
            inst_count1++;
            i = i + 1;
        } else if (stage == 2) {
            std::cout << "DECODE INSTRUCTION: " <<checkOpcode(instruction1)<< "\n";
            runDecoder(instruction1);
          
            
        } else if (stage == 3) {
            std::cout << "EXECUTE INSTRUCTION: " << checkOpcode(instruction1) << "\n";
            std::string condition = runExecute(instruction1);
         
            if (condition == "loop start") {
                i = 0;
            }
            if (condition == "exit") {
            return "finish";
            }
        }
    return "Not Finished";
}

std::string runcpu2(int stage){
    std::cout << "CPU2 Clockcycle :" << clockCycle2 << " :";
    clockCycle2++;
    if (stage == 1) {
            instruction2 = bus2.getDataFromRAM(l+j);
            RAM_COUNT+=1;
            std::cout << "FETCH INSTRUCTION: " << instruction2 << "\n";
            inst_count2++;
            j = j + 1;
        } else if (stage == 2) {
            std::cout << "DECODE INSTRUCTION: " <<checkOpcode(instruction2)<< "\n";
            runDecoder(instruction2);
          
            
        } else if (stage == 3) {
            std::cout << "EXECUTE INSTRUCTION: " << checkOpcode(instruction2) << "\n";
            std::string condition = runExecute(instruction2);
         
            if (condition == "loop start") {
                j = 0;
            }
            if (condition == "exit") {
                return "finish";
            }
        }
    return "Not Finished";
}
int main(){
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = STACK_START1; i <= STACK_END1; ++i) {
        ram[i] = 0.0f;
    }
    for (int i = STACK_START2; i <= STACK_END2; ++i) {
        ram[i] = 0.0f;
    }
    initializeRAM(ram, ARRAY_A_START, ARRAY_A_END);
    initializeRAM(ram, ARRAY_B_START, ARRAY_B_END);

    

  const std::vector<uint32_t> instr1 = {
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
const std::vector<uint32_t> instr2 = {
  0b0000000000000000010000100000011
    ,0b0000000000000001010000110000011
  ,0b0000000000000010000000100110011
 ,0b0000000000000011000000110110011
    ,0b0000000000000010010001100000111
  ,0b0000000000000011010001110000111
      ,0b0001000011000111000010001010011
      ,0b0000000000000010010001000000011
          ,0b0000000000000100000001000110011
         ,0b0000000100000100010000000100111
         ,0b0000000000100000000000000010011
        ,0b0010000000001001000000010010011
   ,0b0000000000100000100000001100011
};


    loadInstructions(ram, instr1,INSTRUCTION_START1);
    loadInstructions(ram, instr2,INSTRUCTION_START2);

BusArbitration bus;
while (true) {
    for (int stage = 1; stage <= 3; stage++) {
        if (bus.arbitrate() == 1 && !cpu1_finished) {
            t0 = true;
            std::string cond1 = runcpu1(stage);
            if (cond1 == "finish") {
                cpu1_finished = true;
            }
        }

        if (bus.arbitrate() == 2 && !cpu2_finished) {
            t0 = false;
            std::string cond1 = runcpu2(stage);
            if (cond1 == "finish") {
                cpu2_finished = true;
            }
        }
    }
    if (cpu1_finished == true && cpu2_finished== true){
        break;
    }
}

    
    std::cout << "\n";
    std::cout <<"Clockcycles for cpu1: "<<clockCycle << "\n";
    std::cout <<"instrctions executed: "<<inst_count1 << "\n";
   std::cout << "CPI: " << clockCycle/inst_count1 <<"\n"; //CPI = Total program execution cycles / Instructions count
   std::cout <<"Clockcycles for cpu2: "<<clockCycle2 << "\n";
    std::cout <<"instrctions executed: "<<inst_count2 << "\n";
   std::cout << "CPI: " << clockCycle2/inst_count2 <<"\n"; //CPI = Total program execution cycles / Instructions count
   std::cout << "Total number of RAM Read/Write Latency: "<< RAM_COUNT << "\n";
for (int i = 0; i < 256; i++) {
        std::cout << output1[i] << "   "<< output2[i] << std::endl;
}

  return 0;  
}

 