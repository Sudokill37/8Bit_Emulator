#include <cstdint>
#include <iostream>
#include "cpu.hpp"

int cycles = 0;

struct registers{
    uint8_t reg[0b1010]; // for clarity use cpu.hpp macros when accessing these
};
struct memory{
    uint8_t stack[265]; //stack, nuff said.
    uint16_t ins[2048];  //program data goes here
    uint8_t data[61184]; //peripherals will be in here.
};

void initializeCPU(registers& cpuReg, memory& cpuMem);
uint16_t fetchIns(registers& cpuReg, memory& cpuMem);
void execute(registers& cpuReg, memory& cpuMem);

int main(){
    memory cpuMem;
    registers cpuReg;

    initializeCPU(cpuReg, cpuMem);
    for(int i = 0; i < 16; i++){
            execute(cpuReg, cpuMem);
    }
    
    std::cout << "FINISHED!" << std::endl;
    return 0;
}

void initializeCPU(registers& cpuReg, memory& cpuMem) {
    
    // Initialize CPU registers
    for (int i = 0; i < 10; i++) {
        cpuReg.reg[i] = 0;
    }
    
    // Initialize CPU memory
    for (int i = 0; i < 265; ++i) {
        cpuMem.stack[i] = 0;
    }
    for (int i = 0; i < 2048; ++i) {
        cpuMem.ins[i] = 0;
    }
    for (int i = 0; i < 61184; ++i) {
        cpuMem.data[i] = 0;
    }

    cpuMem.ins[0]   =   0b0000101100000111;
    cpuMem.ins[1]   =   0b0001101100000111;
    cpuMem.ins[2]   =   0b0010101100000111;
    cpuMem.ins[3]   =   0b0011101100000111;
    cpuMem.ins[4]   =   0b0100101100000111;
    cpuMem.ins[5]   =   0b0101101100000111;
    cpuMem.ins[6]   =   0b0110101100000111;
    cpuMem.ins[7]   =   0b0111101100000111;
    cpuMem.ins[8]   =   0b1000101100000111;
    cpuMem.ins[9]   =   0b1001101100000111;
    cpuMem.ins[10]  =   0b1010101100000111;
    cpuMem.ins[11]  =   0b1011101100000111;
    cpuMem.ins[12]  =   0b1100101100000111;
    cpuMem.ins[13]  =   0b1101101100000111;
    cpuMem.ins[14]  =   0b1110101100000111;
    cpuMem.ins[15]  =   0b1111101100000111;
    


}

void execute(registers& cpuReg, memory& cpuMem){
    uint16_t ins = fetchIns(cpuReg, cpuMem);
    uint8_t opcode = ins >> 12;

    switch (opcode)
    {
    // case 0b1000:
    //     std::cout <<"added!"<<std::endl;
    //     if(mode == 0b1){
    //         uint8_t immediate = ins & 0xFF;
    //         cpuReg.gReg[operand1] =
    //         std::cout <<(int)operand1<<std::endl;
    //     }
    //     break;
    case 0b0000:    //NOP
        std::cout << "NOP" << std::endl;
        break;
    case 0b0001:    //ADD
        std::cout << "ADD" << std::endl;
        break;
    case 0b0010:    //ADDI
        std::cout << "ADDI" << std::endl;
        break;
    case 0b0011:    //AND
        std::cout << "AND" << std::endl;
        break;
    case 0b0100:    //ANDI
        std::cout << "ANDI" << std::endl;
        break;
    case 0b0101:    //NOT
        std::cout << "NOT" << std::endl;
        break;
    case 0b0110:    //BEQA
        std::cout << "BEQA" << std::endl;
        break;
    case 0b0111:    //BEQR
        std::cout << "BEQR" << std::endl;
        break;
    case 0b1000:    //HLT
        std::cout << "HLT" << std::endl;
        break;
    case 0b1001:    //LB
        std::cout << "LB" << std::endl;
        break;
    case 0b1010:    //SB
        std::cout << "SB" << std::endl;
        break;
    case 0b1011:    //LSR
        std::cout << "LSR" << std::endl;
        break;
    case 0b1100:    //LSL
        std::cout << "LSL" << std::endl;
        break;
    case 0b1101:    //INC
        std::cout << "INC" << std::endl;
        break;
    case 0b1110:    //DEC
        std::cout << "DEC" << std::endl;
        break;
    case 0b1111:    //not used (treated as NOP)
        std::cout << "extra" << std::endl;
        break;
    default:
        std::cout << "invalid opcode" << std::endl;
        break;
    }
    cycles++;

}

uint16_t fetchIns(registers& cpuReg, memory& cpuMem){
    
    uint16_t addr = cpuReg.reg[R_PC] | ((uint16_t)cpuReg.reg[R_PCU] << 8);
    uint16_t ins = cpuMem.ins[addr];
    addr++; 
    cpuReg.reg[R_PC] = (uint8_t)(addr & 0xff);
    cpuReg.reg[R_PCU] = (uint8_t)((addr>>8) & 0xff);
    return ins;

}