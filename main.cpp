#include <cstdint>
#include <iostream>
#include "cpu.hpp"

int main(){
    memory cpuMem;
    registers cpuReg;

    initializeCPU(cpuReg, cpuMem);


    cpuReg.reg[0b0000] = 0x00;
    cpuReg.reg[0b0001] = 0b11110111;
    cpuReg.reg[0b0010] = 0b01111111;

    cpuMem.ins[0]   =   0b0101000000010000;
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


    for(int i = 0; i < 200; i++){
            if(HALT_FLAG == 1){ // check if program halted
                break;
            }
            execute(cpuReg, cpuMem);
    }
    
    std::cout << "FINISHED!" << std::endl;
    return 0;
}





