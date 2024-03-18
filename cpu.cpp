#include <cstdint>
#include <iostream>
#include <bitset>
#include "cpu.hpp"



int cycles = 0;

memory::memory() : rstVector((uint16_t*)mem), stack(mem+2), ins(mem+258), data(mem+4354){

    *rstVector = 0x0000;

    for (int i = 0; i < 256; ++i) {
        stack[i] = 0;
    }
    for (int i = 0; i < 4096; ++i) {
        ins[i] = 0;
    }
    for (int i = 0; i < 61184; ++i) {
        data[i] = 0;
    }

}
registers::registers(){

    for (int i = 0; i < 10; i++) {
        reg[i] = 0;
    }
}



uint16_t fetchIns(registers& cpuReg, memory& cpuMem){
    
    uint16_t addr = (cpuReg.reg[R_PC] | ((uint16_t)cpuReg.reg[R_PCU] << 8))*2;
    uint16_t ins = cpuMem.ins[addr] | (cpuMem.ins[addr+1] << 8);
    addr = (addr + 2)/2; 
    cpuReg.reg[R_PC] = (uint8_t)(addr & 0xff);
    cpuReg.reg[R_PCU] = (uint8_t)((addr>>8) & 0xff);
    return ins;

}
void setIns(uint16_t addr, uint16_t ins, memory& cpuMem){
    uint8_t Lins = ins;
    uint8_t Uins = ins >> 8;
    cpuMem.ins[2*addr] = Lins;
    cpuMem.ins[2*addr+1] = Uins;
}

void setIns(uint16_t addr, uint16_t *insAr, int16_t size, memory &cpuMem)
{
    uint8_t Lins;
    uint8_t Uins;

    if(size*2+addr > 4096){
        std::cerr << "Not Enough Program Memory!"<<std::endl;
    }

    for(uint16_t i; i < size; i++){
        Lins = insAr[i];
        Uins = insAr[i] >> 8;
        cpuMem.ins[addr+2*i] = Lins;
        cpuMem.ins[addr+2*i+1] = Uins;
    }
}

void execute(registers& cpuReg, memory& cpuMem){
    if((cpuReg.reg[R_SR]>>2)&0b1){
        cpuReg.reg[R_PC] = 0;
        cpuReg.reg[R_PCU] = 0;
        cpuReg.reg[R_SP] = 0;
        cpuReg.reg[R_SR] = 0;
        cpuReg.reg[R_AR] = 0;
        cpuReg.reg[R_ARU] = 0;
    }
    uint16_t ins = fetchIns(cpuReg, cpuMem);
    uint8_t opcode = ins >> 12;

    switch (opcode)
    {
    case 0b0000:    //NOP
        std::cout << "NOP: " << (int)(cpuReg.reg[R_PC] | cpuReg.reg[R_PCU]<<8)-1 << std::endl;
        break;
    case 0b0001:    //ADD
        ADD(ins, cpuReg, cpuMem);
        break;
    case 0b0010:    //ADDI
        ADDI(ins, cpuReg, cpuMem);
        break;
    case 0b0011:    //SUB
        SUB(ins, cpuReg, cpuMem);
        break;
    case 0b0100:    //SUBI
        SUBI(ins, cpuReg, cpuMem);
        break;
    case 0b0101:    //AND
        AND(ins, cpuReg, cpuMem);
        break;
    case 0b0110:    //ANDI
        ANDI(ins, cpuReg, cpuMem);
        std::cout << "BEQA" << std::endl;
        break;
    case 0b0111:    //NOT
        NOT(ins, cpuReg, cpuMem);
        std::cout << "BEQR" << std::endl;
        break;
    case 0b1000:    //LSL
        LSL(ins, cpuReg, cpuMem);
        break;
    case 0b1001:    //LSR
        LSR(ins, cpuReg, cpuMem);
        break;
    case 0b1010:    //BRF
        BRF(ins, cpuReg, cpuMem);
        break;
    case 0b1011:    //BNF
        BNF(ins, cpuReg, cpuMem);
        break;
    case 0b1100:    //JMP
        JMP(ins, cpuReg, cpuMem);
        break;
    case 0b1101:    //LB
        LB(ins, cpuReg, cpuMem);
        break;
    case 0b1110:    //SB
        SB(ins, cpuReg, cpuMem);
        break;
    case 0b1111:    //RST
        RST(ins, cpuReg, cpuMem);
        break;
    default:
        std::cout << "invalid opcode" << std::endl;
        break;
    }
    cycles++;
}

void NOP(uint16_t ins, registers& cpuReg, memory& cpuMem){
    //Nothing happens here! its a NO OP instruction! will probably get deleted.
}

void ADD(uint16_t ins, registers& cpuReg, memory& cpuMem){
        
    cpuReg.reg[R_SR]  =  0;
    uint8_t destReg = (uint8_t)(ins >> 8)&0x0f;
    uint8_t srcReg1 = (uint8_t)(ins >> 4)&0x0f;
    uint8_t srcReg2 = (uint8_t)(ins >> 0)&0x0f;
    
    uint8_t val1 = cpuReg.reg[srcReg1];
    uint8_t val2 = cpuReg.reg[srcReg2];
    uint8_t result = val1 + val2;

    uint8_t parity = calculateParity(result)<<4;
    uint8_t overflow = ((val1 ^ result) & (val2 ^ result)) >> 2;
    uint8_t sign = (result >> 1)&0x40;
    uint8_t zero = (result == 0) << 7;
    cpuReg.reg[R_SR] = parity | overflow | sign | zero;
    cpuReg.reg[destReg] = result;

}

void ADDI(uint16_t ins, registers& cpuReg, memory& cpuMem){
        
    cpuReg.reg[R_SR]  =  0;
    uint8_t destReg = (uint8_t)(ins >> 10) & 0x03;
    uint8_t srcReg  = (uint8_t)(ins >> 8)  & 0x03;
   
    uint8_t val1 = cpuReg.reg[srcReg];
    uint8_t val2 = ins & 0xff;                              //load the immediate value from the instruction
    uint8_t result = val1 + val2;
   
    uint8_t parity = calculateParity(result)<<4;
    uint8_t overflow = ((val1 ^ result) & (val2 ^ result)) >> 2;
    uint8_t sign = (result >> 1)&0x40;
    uint8_t zero = (result == 0) << 7;
   
    cpuReg.reg[R_SR] = parity | overflow | sign | zero;
    cpuReg.reg[destReg] = result;

}

void SUB(uint16_t ins, registers& cpuReg, memory& cpuMem){

    cpuReg.reg[R_SR]  =  0;
    uint8_t destReg = (uint8_t)(ins >> 8)&0x0f;
    uint8_t srcReg1 = (uint8_t)(ins >> 4)&0x0f;
    uint8_t srcReg2 = (uint8_t)(ins >> 0)&0x0f;
    
    uint8_t val1 = cpuReg.reg[srcReg1];
    uint8_t val2 = ~cpuReg.reg[srcReg2] + 1;
    uint8_t result = val1 + val2;

    uint8_t parity = calculateParity(result)<<4;
    uint8_t overflow = ((val1 ^ result) & (val2 ^ result)) >> 2;
    uint8_t sign = (result >> 1)&0x40;
    uint8_t zero = (result == 0) << 7;
    cpuReg.reg[R_SR] = parity | overflow | sign | zero;
    cpuReg.reg[destReg] = result;

}

void SUBI(uint16_t ins, registers& cpuReg, memory& cpuMem){
    
    cpuReg.reg[R_SR]  =  0;
    uint8_t destReg = (uint8_t)(ins >> 10) & 0x03;
    uint8_t srcReg  = (uint8_t)(ins >> 8)  & 0x03;
   
    uint8_t val1 = cpuReg.reg[srcReg];
    uint8_t val2 = ~(ins & 0xff) + 1;                              //load the immediate value from the instruction
    uint8_t result = val1 + val2;
   
    uint8_t parity = calculateParity(result)<<4;
    uint8_t overflow = ((val1 ^ result) & (val2 ^ result)) >> 2;
    uint8_t sign = (result >> 1)&0x40;
    uint8_t zero = (result == 0) << 7;
   
    cpuReg.reg[R_SR] = parity | overflow | sign | zero;
    cpuReg.reg[destReg] = result;

}

void AND(uint16_t ins, registers& cpuReg, memory& cpuMem){
       
        cpuReg.reg[R_SR]  =  0;

        uint8_t destReg = (uint8_t)(ins >> 8)&0x0f;
        uint8_t srcReg1 = (uint8_t)(ins >> 4)&0x0f;
        uint8_t srcReg2 = (uint8_t)(ins >> 0)&0x0f;

        uint8_t val1 = cpuReg.reg[srcReg1];
        uint8_t val2 = cpuReg.reg[srcReg2];                       //load the immediate value from the instruction
        uint8_t result = val1 & val2;

        uint8_t parity = calculateParity(result)<<4;
        
        uint8_t sign = (result >> 1)&0x40;
        uint8_t zero = (result == 0) << 7;

        cpuReg.reg[R_SR] = parity | sign | zero;
        cpuReg.reg[destReg] = result;
}

void ANDI(uint16_t ins, registers& cpuReg, memory& cpuMem){

        cpuReg.reg[R_SR]  =  0;
        uint8_t destReg = (uint8_t)(ins >> 10) & 0x03;
        uint8_t srcReg  = (uint8_t)(ins >> 8)  & 0x03;

        uint8_t val1 = cpuReg.reg[srcReg];
        uint8_t val2 = ins & 0xff;                              //load the immediate value from the instruction
        uint8_t result = val1 & val2;


        uint8_t parity = calculateParity(result)<<4;
        
        uint8_t sign = (result >> 1)&0x40;
        uint8_t zero = (result == 0) << 7;

        cpuReg.reg[R_SR] = parity | sign | zero;
        cpuReg.reg[destReg] = result;

}

void NOT(uint16_t ins, registers& cpuReg, memory& cpuMem){

    //the not instruction cannot be used with immediate

    cpuReg.reg[R_SR]  =  0;     
    

    uint8_t destReg = (uint8_t)(ins >> 8)&0x0f;
    uint8_t srcReg1 = (uint8_t)(ins >> 4)&0x0f;
        
    uint8_t val1 = cpuReg.reg[srcReg1]; 
    uint8_t result = ~val1;

    uint8_t parity = calculateParity(result)<<4;

    uint8_t sign = (result >> 1)&0x40;
    uint8_t zero = (result == 0) << 7;

    cpuReg.reg[R_SR] = parity | sign | zero;
    cpuReg.reg[destReg] = result;
        
}

void LSL(uint16_t ins, registers& cpuReg, memory& cpuMem){
    
    cpuReg.reg[R_SR]  =  0;

    uint8_t destReg = (uint8_t)(ins >> 8)&0x0f;
    uint8_t srcReg1 = (uint8_t)(ins >> 4)&0x0f;
    uint8_t srcReg2 = (uint8_t)(ins >> 0)&0x0f;

    uint8_t val1 = cpuReg.reg[srcReg1];
    uint8_t result = 0;
    
    if(srcReg2>>3){
        result = val1 << (srcReg2&7);
    }else{
        result = val1 << cpuReg.reg[srcReg2];
    }

    uint8_t parity = calculateParity(result)<<4;
       
    uint8_t sign = (result >> 1)&0x40;
    uint8_t zero = (result == 0) << 7;

    cpuReg.reg[R_SR] = parity | sign | zero;
    cpuReg.reg[destReg] = result;

}

void LSR(uint16_t ins, registers& cpuReg, memory& cpuMem){

    cpuReg.reg[R_SR]  =  0;

    uint8_t destReg = (uint8_t)(ins >> 8)&0x0f;
    uint8_t srcReg1 = (uint8_t)(ins >> 4)&0x0f;
    uint8_t srcReg2 = (uint8_t)(ins >> 0)&0x0f;

    uint8_t val1 = cpuReg.reg[srcReg1];
    uint8_t result = 0;
    
    if(srcReg2>>3){
        result = val1 >> (srcReg2&7);
    }else{
        result = val1 >> cpuReg.reg[srcReg2];
    }

    uint8_t parity = calculateParity(result)<<4;
       
    uint8_t sign = (result >> 1)&0x40;
    uint8_t zero = (result == 0) << 7;

    cpuReg.reg[R_SR] = parity | sign | zero;
    cpuReg.reg[destReg] = result;

}

void BRF(uint16_t ins, registers& cpuReg, memory& cpuMem){
    bool mode = (ins >> 11)&1;
    uint8_t flag = (ins >> 9 )&3;
    bool condition = (cpuReg.reg[R_SR] >> (flag+4))&1;
    uint16_t offset = ins&0x01ff;
    int relativeAddress;
    
    if(offset>>8){
        relativeAddress = -((~(offset-1))&0x01ff);
    }else{
        relativeAddress = ((offset))&0x01ff;
    }

    uint16_t absoluteAddress = ((cpuReg.reg[R_PCU] << 8) | cpuReg.reg[R_PC])+relativeAddress;
    if(condition){
        if(mode){
            cpuReg.reg[R_PC] = absoluteAddress&0x00ff;
            cpuReg.reg[R_PCU] = (absoluteAddress>>8)&0x00ff;
        }else{
            uint16_t addr = ((uint16_t)cpuReg.reg[R_ARU] << 8) | cpuReg.reg[R_AR];
            cpuReg.reg[R_PC] = (addr/2)&0xff;
            cpuReg.reg[R_PCU] = ((addr/2)>>8)&0xff;
        }
    }

    cpuReg.reg[R_SR]  =  0;
}

void BNF(uint16_t ins, registers& cpuReg, memory& cpuMem){
    
    bool mode = (ins >> 11)&1;
    uint8_t flag = (ins >> 10)&3;
    bool condition = (cpuReg.reg[R_SR] >> (flag+4))&1;
    uint16_t offset = ins&0x01ff;
    int relativeAddress;
    
    if(offset>>8){
        relativeAddress = -((~(offset-1))&0x01ff);
    }else{
        relativeAddress = ((offset))&0x01ff;
    }

    uint16_t absoluteAddress = ((cpuReg.reg[R_PCU] << 8) | cpuReg.reg[R_PC])+relativeAddress;
    if(!condition){
        if(mode){
            cpuReg.reg[R_PC] = absoluteAddress&0x00ff;
            cpuReg.reg[R_PCU] = (absoluteAddress>>8)&0x00ff;
        }else{
            uint16_t addr = ((uint16_t)cpuReg.reg[R_ARU] << 8) | cpuReg.reg[R_AR];
            cpuReg.reg[R_PC] = (addr/2)&0xff;
            cpuReg.reg[R_PCU] = ((addr/2)>>8)&0xff;
        }
    }

    cpuReg.reg[R_SR]  =  0;
}

void JMP(u_int16_t ins, registers& cpuReg, memory& cpuMem){
    std::cout << "JMP ";
    bool mode = (ins >> 11)&1;
    //std::cout << std::bitset<16>(ins) << std::endl;

    uint16_t offset = ins&0x07ff;
    
    int relativeAddress;

    if(offset>>10){
        relativeAddress = -((~(offset-1))&0x07ff);
    }else{
        relativeAddress = ((offset))&0x07ff;
    }
    uint16_t absoluteAddress = ((cpuReg.reg[R_PCU] << 8) | cpuReg.reg[R_PC])+relativeAddress;
    
    if(mode){
        cpuReg.reg[R_PC] = absoluteAddress&0x00ff;
        cpuReg.reg[R_PCU] = (absoluteAddress>>8)&0x00ff;

    }else{
        uint16_t addr = ((uint16_t)cpuReg.reg[R_ARU] << 8) | cpuReg.reg[R_AR];
        cpuReg.reg[R_PC] = (addr/2)&0xff;
        cpuReg.reg[R_PCU] = ((addr/2)>>8)&0xff;
    }
}

void LB(uint16_t ins, registers& cpuReg, memory& cpuMem){
    uint8_t isImmediate = (ins >> 11)&0x01;
    uint8_t srcReg = (ins>>4)&0x07;
    uint8_t destReg  = (ins >> 8)&0x07;
    uint8_t data;

    uint16_t address = cpuReg.reg[srcReg] | (cpuReg.reg[srcReg+1]<<8);
    
    if(isImmediate){
        address = fetchIns(cpuReg, cpuMem);
    }

    data = cpuMem.mem[address];

    cpuReg.reg[destReg] = data;

}

void SB(uint16_t ins, registers& cpuReg, memory& cpuMem){
    
    uint8_t isImmediate = (ins >> 11)&0x01;
    uint8_t srcReg = (ins>>4)&0x07;
    uint8_t destReg  = (ins >> 8)&0x07;
    uint8_t data;

    uint16_t address = cpuReg.reg[srcReg] | (cpuReg.reg[srcReg+1]<<8);
    
    if(isImmediate){
        address = fetchIns(cpuReg, cpuMem);
    }

    data = cpuReg.reg[srcReg];

    cpuMem.mem[address] = data;

}

void RST(uint16_t ins, registers& cpuReg, memory& cpuMem){
    cpuReg.reg[R_SR] |= 4;
    std::cout << "RST: " << (int)(cpuReg.reg[R_PC] | cpuReg.reg[R_PCU]<<8)-1 << std::endl;
}

uint8_t calculateParity(uint8_t value) {
    value ^= value >> 4; // Reduce to 4 bits
    value ^= value >> 2; // Reduce to 2 bits
    value ^= value >> 1; // Reduce to 1 bit
    return value & 1;    // Get the parity
}

