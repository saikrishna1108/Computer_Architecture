#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include "RAM.h"
#include <string>
#include <bitset>
#include <algorithm>
#include <unordered_map>
#include <stdio.h>
#include "decoder.h"
#include "execute.h"
#include "globalvar.h"
std::string output[256];
int count=0;
std::vector<int> registers = {0, 0, 0,0 , 0, 0, 0, 0, 0, 0}; //t0,t1,a0,a1// Initialize registers

std::string runExecute(uint32_t instr) {
    std::string opcode = checkOpcode(instr);
    int rs1 = getrs1(instr);
    int rs2 = getrs2(instr);
    int dest = getrd(instr);

    if (opcode == "lw") {
            // Simulate loading data from memory into registers
            int address = (rs1 == 0) ? ARRAY_A_START : (rs1 == 1) ? ARRAY_B_START : ARRAY_C_START;
            registers[dest] = address;
            RAM_COUNT += 1;
            clockCycle += 1;
            std::cout << "Clock cycle :" << clockCycle << " Stall" << "\n"; 
    } else if (opcode == "flw") {
        if (rs1 >= 0 && rs1 < 10) {
            // Simulate type conversion from integer to float
            int offset = getimm11_0(instr);
            ram[dest] = ram[registers[rs1]] + offset;
            RAM_COUNT += 1;
            clockCycle += 1;
            std::cout << "Clock cycle :" << clockCycle << " Stall" << "\n"; 
        }
    } else if (opcode == "add") {
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers[dest] = registers[rs1] + registers[rs2];
               clockCycle += 1;
            std::cout << "Clock cycle :" << clockCycle << " Stall" << "\n"; 
        }
    } else if (opcode == "fadd.s") {
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers[dest] = registers[rs1] + registers[rs2];
            output[count] = std::to_string(count+1) + "  " + std::to_string(registers[rs1]) + " + " + std::to_string(registers[rs2]) + " = " + std::to_string(registers[dest]);
            count += 1;

            }
        }
    else if (opcode == "fsw") {
            int offset = getimm11_5(instr);
            int address = registers[rs1] ;
            registers[address] = static_cast<float>(registers[rs2]) + offset;
              RAM_COUNT += 1;
            clockCycle += 1;
            std::cout << "Clock cycle :" << clockCycle << " Stall" << "\n"; 

    }
     else if (opcode == "addi") {
        if (rs1 >= 0 && rs1 < 10) {
            uint32_t imm = getimm11_0(instr);
            registers[dest] = registers[rs1] + static_cast<int>(imm);
          
        }
    } else if (opcode == "blt") {
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            if (registers[rs1] < registers[rs2]) {
                std::cout << " t0 values is " << registers[rs1] << " and t1 value is " << registers[rs2] << "  "<< "\n";
                 clockCycle += 1;
            std::cout << "Clock cycle :" << clockCycle << " Stall" << "\n"; 
                return "loop start";
            } else {
                std::cout << " t0 values is " << registers[rs1] << " and  t1 value is " << registers[rs2] << "\n";
                return "exit";
            }
        }
    }

    return "continue";
}
