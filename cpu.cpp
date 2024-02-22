#include <cstdint>
#include <iostream>
#include "cpu.hpp"

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
        std::cout << "status: "
        <<(int)(cpuReg.reg[R_SR]>>7) 
        <<(int)((cpuReg.reg[R_SR]>>6)&1)
        <<(int)((cpuReg.reg[R_SR]>>5)&1)
        <<(int)((cpuReg.reg[R_SR]>>4)&1)
        <<(int)((cpuReg.reg[R_SR]>>3)&1)
        <<(int)((cpuReg.reg[R_SR]>>2)&1)
        <<(int)((cpuReg.reg[R_SR]>>1)&1)
        <<(int)((cpuReg.reg[R_SR]>>0)&1)
        << std::endl;
        std::cout << "Val1: " << (int)val1 <<std::endl;
        std::cout << "Val2: " << (int)val2 <<std::endl;
        std::cout << "Result: " << (int)result <<std::endl;

}
//1111 1111 1111 1111
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
        std::cout << "status: "
        <<(int)(cpuReg.reg[R_SR]>>7) 
        <<(int)((cpuReg.reg[R_SR]>>6)&1)
        <<(int)((cpuReg.reg[R_SR]>>5)&1)
        <<(int)((cpuReg.reg[R_SR]>>4)&1)
        <<(int)((cpuReg.reg[R_SR]>>3)&1)
        <<(int)((cpuReg.reg[R_SR]>>2)&1)
        <<(int)((cpuReg.reg[R_SR]>>1)&1)
        <<(int)((cpuReg.reg[R_SR]>>0)&1)
        <<" ZSVPHXXX"
        << std::endl;
        std::cout << "Val1: " << (int)val1 <<std::endl;
        std::cout << "Val2: " << (int)val2 <<std::endl;
        std::cout << "Result: " << (int)result <<std::endl;

}
void AND(uint16_t ins, registers& cpuReg, memory& cpuMem);
void ANDI(uint16_t ins, registers& cpuReg, memory& cpuMem);
void NOT(uint16_t ins, registers& cpuReg, memory& cpuMem);
void BEQA(uint16_t ins, registers& cpuReg, memory& cpuMem);
void BEQR(uint16_t ins, registers& cpuReg, memory& cpuMem);
void HLT(uint16_t ins, registers& cpuReg, memory& cpuMem);
void LB(uint16_t ins, registers& cpuReg, memory& cpuMem);
void SB(uint16_t ins, registers& cpuReg, memory& cpuMem);
void LSR(uint16_t ins, registers& cpuReg, memory& cpuMem);
void LSL(uint16_t ins, registers& cpuReg, memory& cpuMem);
void INC(uint16_t ins, registers& cpuReg, memory& cpuMem);
void DEC(uint16_t ins, registers& cpuReg, memory& cpuMem);
