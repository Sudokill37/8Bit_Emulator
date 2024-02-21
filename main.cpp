#include <cstdint>
#include <iostream>

struct registers{
    uint8_t gReg[4];
    uint8_t SR;
    uint8_t SP;
    uint16_t PC;
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
    execute(cpuReg, cpuMem);
    std::cout << cpuReg.W << std::endl;
    return 0;
}

void initializeCPU(registers& cpuReg, memory& cpuMem) {
    // Initialize CPU registers
    for (int i = 0; i < 4; ++i) {
        cpuReg.gReg[i] = 0;
    }
    cpuReg.PC = 0;
    cpuReg.SP = 0;
    cpuReg.SR = 0;

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

    cpuMem.ins[0] = 0b1000101100000111;

}

void execute(registers& cpuReg, memory& cpuMem){
    uint16_t ins = fetchIns(cpuReg, cpuMem);
    uint8_t opcode = ins >> 12;
    uint8_t mode = ((ins>>11) & 0b1);
    uint8_t operand1 = (ins >> 8)& 0x03;

    switch (opcode)
    {
    case 0b1000:
        std::cout <<"added!"<<std::endl;
        if(mode == 0b1){
            uint8_t immediate = ins & 0xFF;
            cpuReg.gReg[operand1] =
            std::cout <<(int)operand1<<std::endl;
        }
        break;
    
    default:
        std::cout<<"failed"<<std::endl;
        break;
    }

}

uint16_t fetchIns(registers& cpuReg, memory& cpuMem){
    
    uint16_t ins = cpuMem.ins[cpuReg.PC++]; 
    return ins;

}