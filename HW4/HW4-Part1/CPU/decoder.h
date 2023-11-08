// decoder.h

#ifndef DECODER_H
#define DECODER_H

#include <cstdint>
uint8_t getOpcode(uint32_t inst);
uint8_t getimm20(uint32_t inst) ;
uint8_t getimm11_J(uint32_t inst);
uint8_t getimm11_5(uint32_t inst);
uint8_t getimm4_0(uint32_t inst);
uint16_t getimm11_0(uint32_t inst);
uint8_t getfun7(uint32_t inst);
uint8_t getrs2(uint32_t inst);
uint8_t getrs1(uint32_t inst);
uint8_t getfun3(uint32_t inst);
uint8_t getrd(uint32_t inst) ;
uint8_t getimm11_B(uint32_t inst);
uint8_t getimm19_12(uint32_t inst);
uint8_t getimm31_12(uint32_t inst);
uint8_t getimm10_5(uint32_t inst);
uint8_t getimm4_1(uint32_t inst) ;
uint8_t getimm12(uint32_t inst);
uint8_t getimm10_1(uint32_t inst);
std::string checkOpcode(uint32_t inst);
std::string check_type(std::string opcode);
void runDecoder(uint32_t inst);

#endif
