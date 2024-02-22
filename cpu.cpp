#include <cstdint>
#include <iostream>
#include <bitset>
#include "cpu.hpp"

int cycles;

uint16_t fetchIns(registers& cpuReg, memory& cpuMem){
    
    uint16_t addr = cpuReg.reg[R_PC] | ((uint16_t)cpuReg.reg[R_PCU] << 8);
    uint16_t ins = cpuMem.ins[addr];
    addr++; 
    cpuReg.reg[R_PC] = (uint8_t)(addr & 0xff);
    cpuReg.reg[R_PCU] = (uint8_t)((addr>>8) & 0xff);
    return ins;

}

void initializeCPU(registers& cpuReg, memory& cpuMem) {
    
    cycles = 0;

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

}

void execute(registers& cpuReg, memory& cpuMem){
    uint16_t ins = fetchIns(cpuReg, cpuMem);
    uint8_t opcode = ins >> 12;

    switch (opcode)
    {
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
        AND(ins, cpuReg, cpuMem);
        break;
    case 0b0100:    //ANDI
        ANDI(ins, cpuReg, cpuMem);
        break;
    case 0b0101:    //NOT
        NOT(ins, cpuReg, cpuMem);
        break;
    case 0b0110:    //BEQA

        std::cout << "BEQA" << std::endl;
        break;
    case 0b0111:    //BEQR

        std::cout << "BEQR" << std::endl;
        break;
    case 0b1000:    //HLT
        HLT(ins, cpuReg, cpuMem);
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

void NOP(uint16_t ins, registers& cpuReg, memory& cpuMem){

}

void ADD(uint16_t ins, registers& cpuReg, memory& cpuMem){
        
        cpuReg.reg[R_SR]  =  0;
        uint8_t destReg = (uint8_t)(ins >> 8)&0x0f;
        uint8_t srcReg1 = (uint8_t)(ins >> 4)&0x0f;
        uint8_t srcReg2 = (uint8_t)(ins >> 0)&0x0f;

        uint8_t val1 = cpuReg.reg[srcReg1];
        uint8_t val2 = cpuReg.reg[srcReg2];
        uint8_t result = val1 + val2;

        uint8_t parity = (((result)&1)^((result>>1)&1)^((result>>2)&1)^((result>>3)&1)^((result>>4)&1)^((result>>5)&1)^((result>>6)&1)^((result>>7)&1))<<4;
        uint8_t overflow = (int)(((!(val1>>7))&&(!(val2>>7))&&((result>>7)))|(((val1>>7))&&((val2>>7))&&(!(result>>7)))) << 5;
        uint8_t sign = (result >> 1)&0x40;
        uint8_t zero = (result == 0) << 7;
        cpuReg.reg[R_SR] = parity | overflow | sign | zero;
        cpuReg.reg[destReg] = result;

        std::cout << "ADD" << std::endl;
        std::cout << "status: " << std::bitset<8>(cpuReg.reg[R_SR])<<" ZSVPHXXX" << std::endl;
        std::cout << "Val1: " << (int)val1 <<std::endl;
        std::cout << "Val2: " << (int)val2 <<std::endl;
        std::cout << "Result: " << (int)result <<std::endl;

}

void ADDI(uint16_t ins, registers& cpuReg, memory& cpuMem){
        
        cpuReg.reg[R_SR]  =  0;
        uint8_t destReg = (uint8_t)(ins >> 10) & 0x03;
        uint8_t srcReg  = (uint8_t)(ins >> 8)  & 0x03;

        uint8_t val1 = cpuReg.reg[srcReg];
        uint8_t val2 = ins & 0xff;                              //load the immediate value from the instruction
        uint8_t result = val1 + val2;

        uint8_t parity = (((result)&1)^((result>>1)&1)^((result>>2)&1)^((result>>3)&1)^((result>>4)&1)^((result>>5)&1)^((result>>6)&1)^((result>>7)&1))<<4;
        uint8_t overflow = (int)(((!(val1>>7))&&(!(val2>>7))&&((result>>7)))|(((val1>>7))&&((val2>>7))&&(!(result>>7)))) << 5;
        uint8_t sign = (result >> 1)&0x40;
        uint8_t zero = (result == 0) << 7;
        cpuReg.reg[R_SR] = parity | overflow | sign | zero;
        cpuReg.reg[destReg] = result;

        std::cout << "ADDI" << std::endl;
        std::cout << "status: " << std::bitset<8>(cpuReg.reg[R_SR])<<" ZSVPHXXX" << std::endl;
        std::cout << "Val1: " << (int)val1 <<std::endl;
        std::cout << "Val2: " << (int)val2 <<std::endl;
        std::cout << "Result: " << (int)result <<std::endl;

}

void AND(uint16_t ins, registers& cpuReg, memory& cpuMem){
       
        cpuReg.reg[R_SR]  =  0;

        uint8_t destReg = (uint8_t)(ins >> 8)&0x0f;
        uint8_t srcReg1 = (uint8_t)(ins >> 4)&0x0f;
        uint8_t srcReg2 = (uint8_t)(ins >> 0)&0x0f;

        uint8_t val1 = cpuReg.reg[srcReg1];
        uint8_t val2 = cpuReg.reg[srcReg2];                       //load the immediate value from the instruction
        uint8_t result = val1 & val2;

        uint8_t parity = (((result)&1)^((result>>1)&1)^((result>>2)&1)^((result>>3)&1)^((result>>4)&1)^((result>>5)&1)^((result>>6)&1)^((result>>7)&1))<<4;
        
        uint8_t sign = (result >> 1)&0x40;
        uint8_t zero = (result == 0) << 7;

        cpuReg.reg[R_SR] = parity | sign | zero;
        cpuReg.reg[destReg] = result;

        std::cout << "AND" << std::endl;
        std::cout << "status: " << std::bitset<8>(cpuReg.reg[R_SR])<<" ZSVPHXXX" << std::endl;
        std::cout << "Val1: " << (int)val1 <<std::endl;
        std::cout << "Val2: " << (int)val2 <<std::endl;
        std::cout << "Result: " << (int)result <<std::endl;
}

void ANDI(uint16_t ins, registers& cpuReg, memory& cpuMem){

        cpuReg.reg[R_SR]  =  0;
        uint8_t destReg = (uint8_t)(ins >> 10) & 0x03;
        uint8_t srcReg  = (uint8_t)(ins >> 8)  & 0x03;

        uint8_t val1 = cpuReg.reg[srcReg];
        uint8_t val2 = ins & 0xff;                              //load the immediate value from the instruction
        uint8_t result = val1 & val2;


        uint8_t parity = (((result)&1)^((result>>1)&1)^((result>>2)&1)^((result>>3)&1)^((result>>4)&1)^((result>>5)&1)^((result>>6)&1)^((result>>7)&1))<<4;
        
        uint8_t sign = (result >> 1)&0x40;
        uint8_t zero = (result == 0) << 7;

        cpuReg.reg[R_SR] = parity | sign | zero;
        cpuReg.reg[destReg] = result;

        std::cout << "ANDI" << std::endl;
        std::cout << "status: " << std::bitset<8>(cpuReg.reg[R_SR])<<" ZSVPHXXX" << std::endl;
        std::cout << "Val1: " << (int)val1 <<std::endl;
        std::cout << "Val2: " << (int)val2 <<std::endl;
        std::cout << "Result: " << (int)result <<std::endl;

}

void NOT(uint16_t ins, registers& cpuReg, memory& cpuMem){
        //the not instruction cannot be used with immediate

        // |4 bit opcode| |4 bit destination reg| |4 bit source register| |4 bits unused|

        cpuReg.reg[R_SR]  =  0;

        uint8_t destReg = (uint8_t)(ins >> 8)&0x0f;
        uint8_t srcReg1 = (uint8_t)(ins >> 4)&0x0f;
        
        uint8_t val1 = cpuReg.reg[srcReg1];
                             //load the immediate value from the instruction
        uint8_t result = ~val1;

        uint8_t parity = (((result)&1)^((result>>1)&1)^((result>>2)&1)^((result>>3)&1)^((result>>4)&1)^((result>>5)&1)^((result>>6)&1)^((result>>7)&1))<<4;
        
        uint8_t sign = (result >> 1)&0x40;
        uint8_t zero = (result == 0) << 7;

        cpuReg.reg[R_SR] = parity | sign | zero;
        cpuReg.reg[destReg] = result;

        std::cout << "NOT" << std::endl;
        std::cout << "status: " << std::bitset<8>(cpuReg.reg[R_SR])<<" ZSVPHXXX" << std::endl;
        std::cout << "Val1: " << std::bitset<8>(val1) <<std::endl;
        std::cout << "Result: " << std::bitset<8>(result) <<std::endl;
        
        
}

void BEQA(uint16_t ins, registers& cpuReg, memory& cpuMem);
void BEQR(uint16_t ins, registers& cpuReg, memory& cpuMem);

void HLT(uint16_t ins, registers& cpuReg, memory& cpuMem){
        
        cpuReg.reg[R_SR] |= 0b00001000;
        std::cout << "HLT" <<std::endl;

}

void LB(uint16_t ins, registers& cpuReg, memory& cpuMem);
void SB(uint16_t ins, registers& cpuReg, memory& cpuMem);
void LSR(uint16_t ins, registers& cpuReg, memory& cpuMem){

}
void LSL(uint16_t ins, registers& cpuReg, memory& cpuMem);
void INC(uint16_t ins, registers& cpuReg, memory& cpuMem);
void DEC(uint16_t ins, registers& cpuReg, memory& cpuMem);

