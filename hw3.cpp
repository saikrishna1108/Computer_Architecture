#include <iostream>
#include <bitset>
#include <string>
    

int main() {
    std::string binaryInput;
    std::cout << "Enter a 32-bit binary input: ";
    std::cin >> binaryInput;

   uint32_t input = std::bitset<32>(binaryInput).to_ulong();

    uint32_t opcode = (input >> 0) & 0x7F;


// R-type Instruction decoder
if (opcode == 0b0110011) {
        if(func1 == 0b000){
            if(func2==0b0000000){
                std::cout << "ADD R0 R1 R2" <<"\n" ;
            }
            else if (func2==0b0100000){
                std::cout <<"SUB rd rs1 rs2" <<"\n" ;
            }
               else if (func2==0b0000001){
                std::cout <<"MUL rd rs1 rs2" <<"\n" ;
            }
        }
        else if (func1 == 0b001){
            if(func2==0b0000000){
                std::cout << "SLL R0 R1 R2" <<"\n" ;

            }
            else if (func2==0b0000001){
                std::cout <<"MULH rd rs1 rs2" <<"\n" ;
            }
        }
         else if (func1 == 0b010){
            if(func2==0b0000000){
                std::cout <<"SLT rd rs1 rs2" <<"\n" ;
            }
            else if (func2==0b0000001){
                std::cout <<"MULHSU rd rs1 rs2" <<"\n";
            }
            
        }
        else if (func1 == 0b011){
            if(func2==0b0000000){
                std::cout <<"SLTU rd rs1 rs2" <<"\n" ;
            }
            else if (func2==0b0000001){
                std::cout <<"MULHU rd rs1 rs2" <<"\n" ;
            }
            
        }
        else if (func1 == 0b100){
             if(func2==0b0000000){
                std::cout <<"XOR rd rs1 rs2" <<"\n" ;
            }
            else if (func2==0b0000001){
                std::cout <<"DIV rd rs1 rs2" <<"\n" ;
            }
            
        }
         else if (func1 == 0b110){
            if(func2==0b0000000){
                std::cout <<"OR rd rs1 rs2" <<"\n" ;
            }
            else if (func2==0b0000001){
                std::cout <<" REM rd rs1 rs2" <<"\n" ;
            }
            
        }
         else if (func1 == 0b111){
            if(func2==0b0000000){
                std::cout <<"AND rd rs1 rs2" <<"\n" ;
            }
            else if (func2==0b0000001){
                std::cout <<"REMU rd rs1 rs2" <<"\n" ;
            }
        }
        else if (func1 == 0b101){
             if(func2==0b0000000){
                std::cout << "SRL R0 R1 R2" <<"\n" ;
            }
            else if (func2==0b0100000){
                std::cout <<"SRA rd rs1 rs2" <<"\n" ;
            }  
            else if (func2==0b0000001){
                std::cout <<"DIVU rd rs1 rs2" <<"\n" ;
            } 
        }
    }
else if (opcode == 0b0111011) {
        if(func1 == 0b000){
            if(func2==0b0000001){
                std::cout << "MULW R0 R1 R2" <<"\n" ;

            }
        }
        else if(func1 == 0b100 & func2==0b0000001){
             std::cout << "DIVW R0 R1 R2" <<"\n" ;
        }
        else if(func1 == 0b101 & func2==0b0000001){
             std::cout << "DIVUW R0 R1 R2" <<"\n";

        }
        else if(func1 == 0b110 & func2==0b0000001){
             std::cout << "REMW R0 R1 R2" <<"\n";

        }
        else if(func1 == 0b111 & func2==0b0000001){
             std::cout << "REMUW R0 R1 R2" <<"\n" ;

        }
         else if(func1 == 0b001 & func2==0b0000000){
             std::cout << "SLLW R0 R1 R2" <<"\n" ;
         }
         else if(func1 == 0b101 & func2==0b0000000){
             std::cout << "SLLW R0 R1 R2" <<"\n" ;

        }
         else if(func1 == 0b101 & func2==0b0100000){
             std::cout << "REMUW R0 R1 R2" <<"\n" ;

        }
         else if(func1 == 0b000 & func2==0b0000000){
             std::cout << "ADDW R0 R1 R2" <<"\n" ;

        }
         else if(func1 == 0b000 & func2==0b0100000){
             std::cout << "SUBW R0 R1 R2" <<"\n" ;

        }
         else if(func1 == 0b101 & func2==0b0000000){
             std::cout << "SRLW R0 R1 R2" <<"\n" ;

        }
         else if(func1 == 0b101 & func2==0b0100001){
             std::cout << "SRAW R0 R1 R2" <<"\n" ;

        }
}
// I-type instruction decoder

else if(opcode == 0b0010011) {
    if (func1 == 0b000){
            std::cout <<"ADDI rd, rs1, I " <<"\n" ;
        }
    else if (func1 == 0b010){
            std::cout <<"SLTI rd,rs1,I " <<"\n" ;

        }
     else if (func1 == 0b011){
            std::cout <<"SLTIU rd, rs1, I " <<"\n" ;
     }
     else if (func1 == 0b100){
            std::cout <<"XORI rd, rs1, I " <<"\n" ;

        }
    else if (func1 == 0b110){
            std::cout <<"ORI rd, rs1, I " <<"\n";

        }
    else if (func1 == 0b111){
            std::cout <<"ANDI rd, rs1, I " <<"\n" ;

        }
    else if (func1 == 0b001){
            std::cout <<"SLLI rd, rs1, I " <<"\n" ;

        }
    else if (func1 == 0b101){
        uint32_t func2 = (input >> 25) & 0b1111111;
        if(func2==0b0000000){
            std::cout <<"SRLI rd, rs1, I " << "\n";

        }
        else if(func2==0b0100000){
            std::cout <<"SRAI rd, rs1, I " <<"\n" ;

        }
        }
        }


else if (opcode==0b0000011){
    if(func1==0b000){
        std::cout <<"LB rd, rs1" <<"\n" ;
    else if(func1==0b001){
        std::cout <<"LH rd, rs1" <<"\n" ;

    }
     else if(func1==0b010){
        std::cout <<"LW rd, rs1" <<"\n" ;
    }
     else if(func1==0b100){
        std::cout <<"LBU rd, rs1" <<"\n" ;

    }
     else if(func1==0b101){
        std::cout <<"LHU rd, rs1" <<"\n" ;

    }
    }
else if(opcode==0b0100011){
    if(func1==0b000){
        std::cout <<"SB rd, rs1" <<"\n" ;

    }
    else if(func1==0b001){
        std::cout <<"SH rd, rs1" <<"\n";
    }
     else if(func1==0b010){
        std::cout <<"SW rd, rs1" <<"\n" ;
    }

    }
else if(opcode==0b1100011){
    if(func1==0b000){
        std::cout <<"BEQ rs1, rs2" <<"\n";
    }
    else if(func1==0b001){
        std::cout <<"BNE rs1, rs2" <<"\n" ;
    }
     else if(func1==0b100){
        std::cout <<"BLT rs1, rs2" <<"\n" ;
    }
     else if(func1==0b101){
        std::cout <<"BGE rs1, rs2" <<"\n" ;
     }
     else if(func1==0b110){
        std::cout <<"BLTU rs1, rs2" <<"\n" ;
    }
     else if(func1==0b111){
        std::cout <<"BGEU rs1, rs2" <<"\n" ;
    }
    }
else if(opcode==0b1101111){
    if(func1==0b000){
        std::cout <<"JALR rd" <<"\n" ;
    }
    else{
         std::cout <<"JAL rd" <<"\n" ;
    }
     }
else if(opcode==0b0110111){
        
        std::cout <<"LUI rd, imm" <<"\n" ;
     }
else if(opcode==0b0010111){
         
        std::cout <<"AUIPC rd, imm" <<"\n" ;
     }

return 0;
}
    



