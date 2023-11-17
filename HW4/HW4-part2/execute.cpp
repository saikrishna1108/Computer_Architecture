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
#include "bus.cpp"
BusArbitration bus1;
int count1=0;
int count2=0;
std::string output1[256];
std::string output2[256];
std::vector<int> registers1 = {0, 0, 0,0 , 0, 0, 0, 0, 0, 0};
std::vector<int> registers2 = {0, 0, 0,0 , 0, 0, 0, 0, 0, 0}; //t0,t1,a0,a1// Initialize registers

std::string runExecute(uint32_t instr) {
    std::string opcode = checkOpcode(instr);
    int rs1 = getrs1(instr);
    int rs2 = getrs2(instr);
    int dest = getrd(instr);

    if (opcode == "lw") {
            // Simulate loading data from memory into registers
            if (t0 == true){
            int address = (rs1 == 0) ? ARRAY_A_START : (rs1 == 1) ? ARRAY_B_START : ARRAY_C_START;
            registers1[dest] = address;
            RAM_COUNT += 1;
            std::cout << "CPU1 Clock cycle :" << clockCycle << " Stall" << "\n"; 
            clockCycle += 1;
            }
            else{
            int address = (rs1 == 0) ? ARRAY_A_START : (rs1 == 1) ? ARRAY_B_START : ARRAY_D_START;
            registers2[dest] = address;
            RAM_COUNT += 1;
            std::cout << "CPU2 Clock cycle :" << clockCycle2 << " Stall" << "\n"; 
              clockCycle2 += 1;
            }

    } else if (opcode == "flw") {
        if (t0 == true){
        if (rs1 >= 0 && rs1 < 10) {
            // Simulate type conversion from integer to float
            int offset = getimm11_0(instr);
            int data = bus1.getDataFromRAM(registers1[rs1]);
            registers1[dest] = data+ offset;
            RAM_COUNT += 1;
            std::cout << "CPU1 Clock cycle :" << clockCycle << " Stall" << "\n"; 
             clockCycle += 1;
            }
        }
        else{
            if (rs1 >= 0 && rs1 < 10) {
            // Simulate type conversion from integer to float
            int offset = getimm11_0(instr);
             int data = bus1.getDataFromRAM(registers2[rs1]);
            registers2[dest] = data+ offset;
            RAM_COUNT += 1;
            std::cout << "CPU2 Clock cycle :" << clockCycle2<< " Stall" << "\n"; 
            clockCycle2 += 1;
            }
        }
    } else if (opcode == "add") {
    if (t0 == true){
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers1[dest] = registers1[rs1] + registers1[rs2];
            clockCycle += 1;
            std::cout << "CPU1 Clock cycle :" << clockCycle << " Stall" << "\n"; 
            
            } 
        }
    else{
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers2[dest] = registers2[rs1] + registers2[rs2];
            clockCycle2 += 1;
            std::cout << "CPU2 Clock cycle :" << clockCycle2 << " Stall" << "\n"; 
            
            } 
        }
        }
    else if (opcode == "fadd.s") {
        if(t0==true){
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers1[dest] = registers1[rs1] + registers1[rs2];
            output1[count1] = std::to_string(count1+1) + "  " + std::to_string(registers1[rs1]) + " + " + std::to_string(registers1[rs2]) + " = " + std::to_string(registers1[dest]);
            count1 += 1;

            }
        }
    else{
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers2[dest] = registers2[rs1] + registers2[rs2];
            output1[count1] = std::to_string(count1+1) + "  " + std::to_string(registers2[rs1]) + " + " + std::to_string(registers2[rs2]) + " = " + std::to_string(registers2[dest]);
            count1 += 1;
    }
    }
    }
    else if (opcode == "fsub.s") {
       if(t0==true){
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers1[dest] = registers1[rs1] - registers1[rs2];
            output2[count2] = std::to_string(count2+1) + "  " + std::to_string(registers1[rs1]) + " - " + std::to_string(registers1[rs2]) + " = " + std::to_string(registers2[dest]);
            count2 += 1;

            }
        }
    else{
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers2[dest] = registers2[rs1] - registers2[rs2];
            output2[count2] = std::to_string(count2+1) + "  " + std::to_string(registers2[rs1]) + " - " + std::to_string(registers2[rs2]) + " = " + std::to_string(registers2[dest]);
            count2 += 1;
    }
    }
        }
    else if (opcode == "fsw") {
        if (t0 == true){
            int offset = getimm11_5(instr);
            int address = registers1[rs1] ;
            int output = static_cast<float>(registers1[rs2]) + offset;
            bus1.writeDataToRAM(output,address);
            clockCycle += 1;
            std::cout << "CPU1 Clock cycle :" << clockCycle << " Stall" << "\n"; 
             
            }
            else{
                  int offset = getimm11_5(instr);
            int address = registers2[rs1] ;
            int data = static_cast<float>(registers2[rs2]) + offset;
            bus1.writeDataToRAM(data,address);
            clockCycle2 += 1;
            std::cout << "CPU2 Clock cycle :" << clockCycle2 << " Stall" << "\n"; 
             
            }

    }
     else if (opcode == "addi") {
        if(t0==true){
        if (rs1 >= 0 && rs1 < 10) {
            uint32_t imm = getimm11_0(instr);
            registers1[dest] = registers1[rs1] + static_cast<int>(imm);
            
            }
          
        }
        else{
            if (rs1 >= 0 && rs1 < 10) {
            uint32_t imm = getimm11_0(instr);
            registers2[dest] = registers2[rs1] + static_cast<int>(imm);
            
        }
        }
    } else if (opcode == "blt") {
        if(t0==true){
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            if (registers1[rs1] < registers1[rs2]) {
                std::cout << " t0 values is " << registers1[rs1] << " and t1 value is " << registers1[rs2] << "  "<< "\n";
                return "loop start";
            } else {
                std::cout << " t0 values is " << registers1[rs1] << " and  t1 value is " << registers1[rs2] << "\n";
                return "exit";
            }
        }
    }
    else{
if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            if (registers2[rs1] < registers2[rs2]) {
                std::cout << " t0 values is " << registers2[rs1] << " and t1 value is " << registers2[rs2] << "  "<< "\n";
                return "loop start";
            } else {
                std::cout << " t0 values is " << registers2[rs1] << " and  t1 value is " << registers2[rs2] << "\n";
                return "exit";
            }
        }
    }
    }
    return "continue";
}
