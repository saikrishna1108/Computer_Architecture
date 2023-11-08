#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <unordered_map>
#include <stdio.h>
#include <cstdint>
#include "decoder.h"
#include "globalvar.h"
using namespace std;

int reg_we;
int reg_re;
int alu_op;
int mem_we;
int mem_re;
int branch;
int lui;
int auipc;

string opcodeN = "None";

uint8_t getOpcode(uint32_t inst) {
    uint8_t opcode;
    opcode = (uint8_t)((inst & 0b00000000000000000000000001111111) >> 0);
    return opcode;
}

uint8_t getrd(uint32_t inst) {
    uint8_t rd;
    rd = (uint8_t)((inst & 0b00000000000000000000111110000000) >> 7);
    return rd;
}

uint8_t getfun3(uint32_t inst) {
    uint8_t fun3;
    fun3 = (uint8_t)((inst & 0b00000000000000000111000000000000) >> 12);
    return fun3;
}

uint8_t getrs1(uint32_t inst) {
    uint8_t rs1;
    rs1 = (uint8_t)((inst & 0b00000000000011111000000000000000) >> 15);
    return rs1;
}

uint8_t getrs2(uint32_t inst) {
    uint8_t rs2;
    rs2 = (uint8_t)((inst & 0b00000001111100000000000000000000) >> 20);
    return rs2;
}

uint8_t getfun7(uint32_t inst) {
    uint8_t fun7;
    fun7 = (uint8_t)((inst & 0b11111110000000000000000000000000) >> 25);
    return fun7;
}

uint16_t getimm11_0(uint32_t inst) {
    uint16_t imm11_0;
    imm11_0 = (uint16_t)((inst & 0b11111111111100000000000000000000) >> 20);
    return imm11_0;
}

uint8_t getimm4_0(uint32_t inst) {
    uint8_t imm4_0;
    imm4_0 = (uint8_t)((inst & 0b00000000000000000000111110000000) >> 7);
    return imm4_0;
}

uint8_t getimm11_5(uint32_t inst) {
    uint8_t imm11_5;
    imm11_5 = (uint8_t)((inst & 0b11111110000000000000000000000000) >> 25);
    return imm11_5;
}

uint8_t getimm11_B(uint32_t inst) {
    uint8_t imm11_B;
    imm11_B = (uint8_t)((inst & 0b00000000000000000000000010000000) >> 7);
    return imm11_B;
}

uint8_t getimm4_1(uint32_t inst) {
    uint8_t imm4_1;
    imm4_1 = (uint8_t)((inst & 0b00000000000000000000111100000000) >> 8);
    return imm4_1;
}

uint8_t getimm10_5(uint32_t inst) {
    uint8_t imm10_5;
    imm10_5 = (uint8_t)((inst & 0b00111110000000000000000000000000) >> 25);
    return imm10_5;
}

uint8_t getimm12(uint32_t inst) {
    uint8_t imm12;
    imm12 = (uint8_t)((inst & 0b11000000000000000000000000000000) >> 30);
    return imm12;
}

uint8_t getimm31_12(uint32_t inst) {
    uint8_t imm31_12;
    imm31_12 = (uint8_t)((inst & 0b11111111111111111111000000000000) >> 12);
    return imm31_12;
}

uint8_t getimm19_12(uint32_t inst) {
    uint8_t imm19_12;
    imm19_12 = (uint8_t)((inst & 0b00000000000011111111000000000000) >> 12);
    return imm19_12;
}

uint8_t getimm11_J(uint32_t inst) {
    uint8_t imm11_J;
    imm11_J = (uint8_t)((inst & 0b00000000000100000000000000000000) >> 20);
    return imm11_J;
}

uint8_t getimm10_1(uint32_t inst) {
    uint8_t imm10_1;
    imm10_1 = (uint8_t)((inst & 0b01111111111000000000000000000000) >> 21);
    return imm10_1;
}

uint8_t getimm20(uint32_t inst) {
    uint8_t imm20;
    imm20 = (uint8_t)((inst & 0b10000000000000000000000000000000) >> 31);
    return imm20;
}

std::string checkOpcode(uint32_t inst) {;
    if (!(getOpcode(inst) ^ 0b00110011)) {
        if (!(getfun7(inst) ^ 0b00000000)) {
            unsigned int c = getfun3(inst);
            switch (c) {
            case 0b000: opcodeN = "add";
                break;
            case 0b001: opcodeN = "sll";
                break;
            case 0b010: opcodeN = "slt";
                break;
            case 0b011: opcodeN = "sltu";
                break;
            case 0b100: opcodeN = "xor";
                break;
            case 0b101: opcodeN = "srl";
                break;
            case 0b110: opcodeN = "or";
                break;
            case 0b111: opcodeN = "and";
                break;
            default: opcodeN = "NOPE";
                break;
            }
        }
        if (!(getfun7(inst) ^ 0b00100000)) {
            unsigned int c = getfun3(inst);
            switch (c) {
            case 0b000: opcodeN = "sub";
                break;
            case 0b101: opcodeN = "sra";
                break;
            default: opcodeN = "NOPE";
            }
        }
        if (!(getfun7(inst) ^ 0b00000001)) {
            unsigned int c = getfun3(inst);
            switch (c) {
            case 0b000: opcodeN = "mul";
                break;
            case 0b001: opcodeN = "mulh";
                break;
            case 0b010: opcodeN = "mulhsu";
                break;
            case 0b011: opcodeN = "mulhu";
                break;
            case 0b100: opcodeN = "div";
                break;
            case 0b101: opcodeN = "divu";
                break;
            case 0b110: opcodeN = "rem";
                break;
            case 0b111: opcodeN = "remu";
                break;
            default: opcodeN = "NOPE";
            }
        }
    }
;
    if (!(getOpcode(inst) ^ 0b00111011)) {
        if (!(getfun7(inst) ^ 0b00000000)) {
            unsigned int c = getfun3(inst);
            switch (c) {
            case 0b001: opcodeN = "sllw";
                break;
            case 0b101: opcodeN = "srlw";
                break;
            default: opcodeN = "NOPE";
            }
        }
        if (!(getfun7(inst) ^ 0b00100000)) {
            opcodeN = "sraw";
            }
        if (!(getfun7(inst) ^ 0b00000001)) {
            unsigned int c = getfun3(inst);
            switch (c) {
            case 0b000: opcodeN = "mulw";
                break;
            case 0b100: opcodeN = "divw";
                break;
            case 0b101: opcodeN = "divuw";
                break;
            case 0b110: opcodeN = "remw";
                break;
            case 0b111: opcodeN = "remuw";
                break;
            default: opcodeN = "NOPE";
            }
        }
    }

    if (!(getOpcode(inst) ^ 0b00000011)) {
        unsigned int b = getfun3(inst);
        switch (b) {
        case 0b000: opcodeN = "lb";
            break;
        case 0b001: opcodeN = "lh";
            break;
        case 0b010: opcodeN = "lw";
            break;
        case 0b100: opcodeN = "lbu";
            break;
        case 0b101: opcodeN = "lhu";
            break;
        case 0b110: opcodeN = "lwu";
            break;
        case 0b011: opcodeN = "ld";
            break;
        default: opcodeN = "NOPE";
        }
    }
    }
    

    if (!(getOpcode(inst) ^ 0b00010011)) {
        unsigned int b = getfun3(inst);
        switch (b) {
        case 0b000: opcodeN = "addi";
            break;
        case 0b001: if (!(getfun7(inst) ^ 0b00000000)) { opcodeN = "slli"; };
            break;
        case 0b010: opcodeN = "slti";
            break;
        case 0b011: opcodeN = "sltiu";
            break;
        case 0b100: opcodeN = "xori";
            break;
        case 0b101: if (!(getfun7(inst) ^ 0b00000000)) { opcodeN = "srli"; } 
                    if (!(getfun7(inst) ^ 0b00100000)) { opcodeN = "srai"; };
            break;
        case 0b110: opcodeN = "ori";
            break;
        case 0b111: opcodeN = "andi";
            break;
        default: opcodeN = "NOPE";
        }
    }

    if (!(getOpcode(inst) ^ 0b01100111)) {
        opcodeN = "jalr";
    }
     if (!(getOpcode(inst) ^ 0b01010011)) {
        opcodeN = "fadd.s";
    }

    if (!(getOpcode(inst) ^ 0b00011011)) {
        if (!(getfun7(inst) ^ 0b00000000)) {
            unsigned int c = getfun3(inst);
            switch (c) {
            case 0b001: opcodeN = "slliw";
                break;
            case 0b101: opcodeN = "srliw";
                break;
            default: opcodeN = "NOPE";
            }
        }
        if (!(getfun7(inst) ^ 0b00100000)) {
            if (!(getfun3(inst) ^ 0b00000101)) {
                opcodeN = "sraiw";
            }
        }
    }

    if (!(getOpcode(inst) ^ 0b01101111)) {
        opcodeN = "jal";
    }

    if (!(getOpcode(inst) ^ 0b00100011)) {
        unsigned int b = getfun3(inst);
        switch (b) {
        case 0b000: opcodeN = "sb";
            break;
        case 0b001: opcodeN = "sh";
            break;
        case 0b010: opcodeN = "sw";
            break;
        case 0b011: opcodeN = "sd";
            break;
        default: opcodeN = "NOPE";
        }
    }

    if (!(getOpcode(inst) ^ 0b01100011)) {
        unsigned int b = getfun3(inst);
        switch (b) {
        case 0b000: opcodeN = "beq";
            break;
        case 0b001: opcodeN = "bne";
            break;
        case 0b100: opcodeN = "blt";
            break;
        case 0b101: opcodeN = "bge";
            break;
        case 0b110: opcodeN = "bltu";
            break;
        case 0b111: opcodeN = "bgeu";
            break;
        default: opcodeN = "NOPE";
        }
    }

    if (!(getOpcode(inst) ^ 0b00110111)) {
        opcodeN = "lui";
    }

    if (!(getOpcode(inst) ^ 0b00010111)) {
        opcodeN = "auipc";
    }
return opcodeN;
}

string check_type(string opcode) {
    vector<string>  rtype_list
    { "add", "addw", "sub", "subw", "mul", "mulw", "mulh", "mulhsu", "mulhu", "div", "divu", "rem", "remu",
    "divw", "divuw", "remw", "remuw", "and", "or", "xor", "sll", "srl", "sra", "sllw", "srkw", "sraw", "slt", "sltu","fadd.s" };
    vector<string>  itype_list
    { "lb", "lbu", "lh", "lhu", "lw", "lwu", "ld", "flw", "fld", "addi", "addiw", "andi", "ori", "xori",
    "slli", "srli", "sra", "slliw", "srliw", "sraiw", "slti", "sltiu", "jalr" };
    vector<string>  stype_list
    { "sb", "sh", "sw", "sd", "fsw", "fsd" };
    vector<string>  btype_list
    { "beq", "bne", "blt", "bge", "bltu", "bgeu" };
    vector<string>  utype_list
    { "lui", "auipc" };
    vector<string>  jtype_list
    { "jal" };

    bool isInRList = false;
    isInRList = find(rtype_list.begin(), rtype_list.end(), opcode) != rtype_list.end();
    if (isInRList == true) {
        return "Rtype";
    }
    bool isInIList = false;
    isInIList = find(itype_list.begin(), itype_list.end(), opcode) != itype_list.end();
    if (isInIList == true) {
        return "Itype";
    }
    bool isInSList = false;
    isInSList = find(stype_list.begin(), stype_list.end(), opcode) != stype_list.end();
    if (isInSList == true) {
        return "Stype";
    }
    bool isInBList = false;
    isInBList = find(btype_list.begin(), btype_list.end(), opcode) != btype_list.end();
    if (isInBList == true) {
        return "Btype";
    }
    bool isInUList = false;
    isInUList = find(utype_list.begin(), utype_list.end(), opcode) != utype_list.end();
    if (isInUList == true) {
        return "Utype";
    }
    bool isInJList = false;
    isInJList = find(jtype_list.begin(), jtype_list.end(), opcode) != jtype_list.end();
    if (isInJList == true) {
        return "Jtype";
    }
    return "NOPE";

}

void controlSignalRtype() {
    //all Rtype have the same control signal
    reg_we = 1; reg_re = 1; alu_op = 1;
    mem_we = 0; mem_re = 0;
    branch = 0; lui = 0; auipc = 0;
}

void controlSignalItype(string opcode) {

    const static unordered_map<string, int> stringToNum{
        //Itype list
       {"flw",1} ,{"lb",1}, {"lw",1}, {"lh",1}, {"lbu",1}, {"lhu",1}, {"lwu",1}, {"ld",1},
        {"addi",2}, {"addiw",2}, {"andi",2}, {"ori",2}, {"xori",2}, {"slti",2}, {"sltiu",2},
        {"slli",3}, {"srlim",3}, {"slliw",3}, {"srliw",3}, {"srai",3}, {"sraiw",3}, {"muli",3},
        {"jalr",4}
    };

    string opcodes = opcode;

    switch (stringToNum.at(opcodes)) {
        //lb, lw, lh, lbu, lhu, lwu, ld,
    case 1: reg_we = 1; reg_re = 1; alu_op = 1;
        mem_we = 0; mem_re = 1;
        branch = 0; lui = 0; auipc = 0;
        break;
        //addi, addiw, andi, ori, xori, slti, sltiu,
    case 2: reg_we = 1; reg_re = 1; alu_op = 1;
        mem_we = 0; mem_re = 0;
        branch = 0; lui = 0; auipc = 0;
        break;
        //slli, srlim, slliw, srliw, srai, sraiw,
    case 3: reg_we = 1; reg_re = 1; alu_op = 1;
        mem_we = 0; mem_re = 0;
        branch = 0; lui = 0; auipc = 0;
        break;
        //jalr
    case 4: reg_we = 1; reg_re = 1; alu_op = 1;
        mem_we = 0; mem_re = 0;
        branch = 0; lui = 0; auipc = 0;
        break;
    }
}

void controlSignalStype() {
    //sb, sh, sw, sbd
    reg_we = 0; reg_re = 1; alu_op = 1;
    mem_we = 1; mem_re = 0;
    branch = 0; lui = 0; auipc = 0;
}

void controlSignalBtype() {
    //beq, bne, blt, bge, bltu, bgeu
    reg_we = 0; reg_re = 1; alu_op = 1;
    mem_we = 0; mem_re = 0;
    branch = 1; lui = 0; auipc = 0;
}

void controlSignalUtype() {


    if (opcodeN == "lui") {
        //lui
        reg_we = 0; reg_re = 1; alu_op = 0;
        mem_we = 0; mem_re = 0;
        branch = 0; lui = 0; auipc = 1;
    }
    else {
        //auipc
        reg_we = 0; reg_re = 1; alu_op = 0;
        mem_we = 0; mem_re = 0;
        branch = 0; lui = 1; auipc = 0;
    }
}

void controlSignalJtype() {
    //jal
    reg_we = 1; reg_re = 0; alu_op = 1;
    mem_we = 0; mem_re = 0;
    branch = 0; lui = 0; auipc = 0;
}

void setControl() {
    const static unordered_map<string, int> stringToNum{
        {"Rtype",1},
        {"Itype",2},
        {"Stype",3},
        {"Btype",4},
        {"Utype",5},
        {"Jtype",6},
    };
    switch (stringToNum.at(check_type(opcodeN))) {
    case 1: controlSignalRtype();
        break;
    case 2: controlSignalItype(opcodeN);
        break;
    case 3: controlSignalStype();
        break;
    case 4: controlSignalBtype();
        break;
    case 5: controlSignalUtype();
        break;
    case 6: controlSignalJtype();
        break;
    }

}

void printList(uint32_t inst) {
    cout << "32 bits Instruction: " << bitset<32>(inst) << "\n" << check_type(opcodeN);

    if (opcodeN == "jalr" || opcodeN == "lui" || opcodeN == "auipc") {
        cout << "\n DECODED Instruction: " << opcodeN << " x" << bitset<8>(getrd(inst)).to_ulong();
    }
    else {
        cout << "\nInstruction: " << opcodeN << " x" << bitset<8>(getrd(inst)).to_ulong() << " x" << bitset<8>(getrs1(inst)).to_ulong() <<
            " x" << bitset<8>(getrs2(inst)).to_ulong();
    }
    cout << "\nreg_we:" << reg_we << " reg_re:" << reg_re << " alu_op: " << alu_op << "\nbranch:" << branch << " lui:" << lui << " auipc:" << auipc << "\n";
}

void runDecoder(uint32_t inst) {
    uint32_t instBit = inst;
    checkOpcode(instBit);
    setControl();
    printList(instBit);

}
/*
int main() {
    //example 32-bit instruction
    uint32_t inst[] = { 0b0000000000000010010001100000111,0b0000000011001000000010001010011
   
    };
    for (int i = 0; i < (sizeof(inst)/4); i++) {
        std::cout << checkOpcode(inst[i]);
        runDecoder(inst[i]);
        std::cout << checkOpcode(inst[i]);
    }
}
*/

