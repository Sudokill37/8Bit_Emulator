#include <cstdint>
#include <iostream>
#include "cpu.hpp"

int cycles = 0;


void initializeCPU(registers& cpuReg, memory& cpuMem);
uint16_t fetchIns(registers& cpuReg, memory& cpuMem);
void execute(registers& cpuReg, memory& cpuMem);

int main(){
    memory cpuMem;
    registers cpuReg;

    initializeCPU(cpuReg, cpuMem);
    for(int i = 0; i < 200; i++){
            if(HALT_FLAG == 1){ // check if program halted
                break;
            }
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

    cpuReg.reg[0b0000] = 0x00;
    cpuReg.reg[0b0001] = 0b00000010;
    cpuReg.reg[0b0010] = 0b01111111;

    cpuMem.ins[0]   =   0b0010000101111111;
    cpuMem.ins[1]   =   0x8000;
    cpuMem.ins[2]   =   0b0010101100000111;
    cpuMem.ins[3]   =   0b0011101100000111;
    cpuMem.ins[4]   =   0b0100101100000111;
    cpuMem.ins[5]   =   0b0101101100000111;
    cpuMem.ins[6]   =   0b0110101100000111;
    cpuMem.ins[7]   =   0b0111101100000111;
    cpuMem.ins[8]   =   0b1010101100000111;
    cpuMem.ins[9]   =   0b1001101100000111;
    cpuMem.ins[10]  =   0b1010101100000111;
    cpuMem.ins[11]  =   0b1011101100000111;
    cpuMem.ins[12]  =   0b1100101100000111;
    cpuMem.ins[13]  =   0b1101101100000111;
    cpuMem.ins[14]  =   0b1110101100000111;
    cpuMem.ins[15]  =   0b1111101100000111;
    cpuMem.ins[64]  =   0x8000;
     


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
        ADD(ins, cpuReg, cpuMem);
        break;
    case 0b0010:    //ADDI
        ADDI(ins, cpuReg, cpuMem);
        break;
    case 0b0011:    //AND
        cpuReg.reg[R_SR]  = 0;
        std::cout << "AND" << std::endl;
        break;
    case 0b0100:    //ANDI
        cpuReg.reg[R_SR]  = 0;
        std::cout << "ANDI" << std::endl;
        break;
    case 0b0101:    //NOT
        cpuReg.reg[R_SR]  = 0;
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
        cpuReg.reg[R_SR] |= 0b00001000;
        break;
    case 0b1001:    //LB
        cpuReg.reg[R_SR]  = 0;
        std::cout << "LB" << std::endl;
        break;
    case 0b1010:    //SB
        std::cout << "SB" << std::endl;
        break;
    case 0b1011:    //LSR
        cpuReg.reg[R_SR]  = 0;
        std::cout << "LSR" << std::endl;
        break;
    case 0b1100:    //LSL
        cpuReg.reg[R_SR]  = 0;
        std::cout << "LSL" << std::endl;
        break;
    case 0b1101:    //INC
        cpuReg.reg[R_SR]  = 0;
        std::cout << "INC" << std::endl;
        break;
    case 0b1110:    //DEC
        cpuReg.reg[R_SR]  = 0;
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
