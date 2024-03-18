#pragma once

#define     R_W     0b0000
#define     R_X     0b0001
#define     R_Y     0b0010
#define     R_Z     0b0011
#define     R_PC    0b0100
#define     R_PCU   0b0101
#define     R_AR    0b0110
#define     R_ARU   0b0111
#define     R_SP    0b1000
#define     R_SR    0b1001

#define     HALT_FLAG       ((cpuReg.reg[R_SR] >> 0x03) & 0x01)
#define     Parity_FLAG     ((cpuReg.reg[R_SR] >> 0x04) & 0x01)
#define     OVERFLOW_FLAG   ((cpuReg.reg[R_SR] >> 0x05) & 0x01)
#define     SIGN_FLAG       ((cpuReg.reg[R_SR] >> 0x06) & 0x01)
#define     ZERO_FLAG       ((cpuReg.reg[R_SR] >> 0x07) & 0x01)



struct registers{
    uint8_t reg[0b1010];// for clarity use cpu.hpp macros when accessing these
    registers(); 
};
struct memory{
    uint8_t mem[65536];
    uint16_t* rstVector;
    uint8_t* stack; //stack, nuff said.
    uint8_t* ins;  //program data goes here
    uint8_t* data;//[61184]; //peripherals will be in here.
    memory();
};

uint16_t fetchIns(registers& cpuReg, memory& cpuMem);
void execute(registers& cpuReg, memory& cpuMem);
void setIns(uint16_t addr, uint16_t ins, memory& cpuMem);
void setIns(uint16_t addr, uint16_t* insAr, int16_t size, memory& cpuMem);



void ADD(uint16_t ins, registers& cpuReg, memory& cpuMem);
void ADDI(uint16_t ins, registers& cpuReg, memory& cpuMem);
void SUB(uint16_t ins, registers& cpuReg, memory& cpuMem);
void SUBI(uint16_t ins, registers& cpuReg, memory& cpuMem);
void AND(uint16_t ins, registers& cpuReg, memory& cpuMem);
void ANDI(uint16_t ins, registers& cpuReg, memory& cpuMem);
void NOT(uint16_t ins, registers& cpuReg, memory& cpuMem);
void LSL(uint16_t ins, registers& cpuReg, memory& cpuMem);
void LSR(uint16_t ins, registers& cpuReg, memory& cpuMem);
void BRF(uint16_t ins, registers& cpuReg, memory& cpuMem);
void BNF(uint16_t ins, registers& cpuReg, memory& cpuMem);
void JMP(uint16_t ins, registers& cpuReg, memory& cpuMem);
void LB(uint16_t ins, registers& cpuReg, memory& cpuMem);
void SB(uint16_t ins, registers& cpuReg, memory& cpuMem);
void RST(uint16_t ins, registers& cpuReg, memory& cpuMem);

uint8_t calculateParity(uint8_t);

