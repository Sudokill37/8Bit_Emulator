#include <cstdint>
#include <iostream>
#include "cpu.hpp"

int main(){
    memory cpuMem;
    registers cpuReg;


    uint16_t data[] = {
        18538, 57879, 43732,  1325, 42719, 26981, 54238, 25617, 40191, 21421,
        54937,  7421, 26041, 50880, 46190, 58387, 30844, 15011, 41868,  8719,
        10308, 25098, 23441, 54860, 11282, 12525, 26979, 11825, 48081, 32954, 
        52477, 42538, 39831, 65402, 44666, 46819, 37690, 25866, 64052,  2002, 
        36520, 46903,  2627,  6416, 18861, 20688, 26540, 60349, 45473,  1454, 
        8121, 59036,  9159, 46144, 56430, 36156, 36514,  9016,  2890, 44994, 
        64033, 40975, 54888, 39758,  5920, 33566, 11634,  3082, 63008, 36871, 
        25926, 28898, 63171, 50444,  7864, 54252,  3444, 44173, 30354, 20416, 
        6281,  6969, 56360, 23705, 64840, 28264, 47181, 55173,  2552,  2926, 
        58243, 16139, 21145, 39779, 30321, 65045, 16715, 16951, 41296, 27526,
        1172, 21207, 21516, 53935, 10988, 53177,  6046, 39469, 29941, 27048,
        58465, 10807, 35993, 54480,  8463, 37271, 35867, 12252, 25327, 10969,
        4089, 57741, 31221, 53264,  2521, 16018, 62008, 61397, 64920, 27403,
        15005,  3844, 31895, 51009, 13264, 34075, 63703, 54469, 12304, 15497,
        26529, 49864, 35370, 27297, 45495, 23692, 58934, 21774, 29924, 34467, 
        9500, 52454,  4502, 38861,  4160, 20054, 25760, 58050, 18947, 22409, 
        44799, 39651, 14449, 63536, 42960,  1994,  3224, 25775, 53726, 51917, 
        64864,  8400, 52781,  7461, 30961, 62145, 33418, 28481, 41007, 20246, 
        31911, 11726, 27440, 51665, 26482, 37362, 43193, 13685, 63005, 40524, 
        40638, 59413, 10041, 20355,  8580, 33859, 62531, 39298, 19199, 50471, 
        8827, 60761, 33549, 28477, 20546, 32471, 15487, 62805, 22817, 33087, 
        9669,  6594, 52372, 46298, 13012, 10149, 60931, 52587, 60550, 44071, 
        12846, 23835, 64109, 42248,  5099, 38411, 45754,  8582, 55694, 19955, 
        58631, 57820, 53925, 41831, 61947, 13623, 18318, 35184,  7940, 25334,
        50970, 16970, 11576, 48065, 59561, 54491, 22338, 49116, 36560, 5674
    };

    uint16_t program[] = {
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x8000,
        0xf000,
        0xf000,
        0xf000,
        0xf000,
        0xf000
    };

    for(int i = 0; i < 250; i++){
        cpuMem.data[2*i] = data[i];
        cpuMem.data[2*i+1] = data[i]>>8;
    }

    setIns(0,program,10,cpuMem);
    setIns(5,0x1000,cpuMem);
    setIns(6,0x8000,cpuMem);
    
    //std::cout << (int)(cpuMem.data[0]|cpuMem.data[1]<<8) << std::endl;


    cpuReg.reg[0b0000] = 0x00;
    cpuReg.reg[0b0001] = 0b11110111;
    cpuReg.reg[0b0010] = 0b01111111;

    

    // for(int i = 0; i < 8; i++){
    //         if(HALT_FLAG == 1){ // check if program halted
    //             break;
    //         }
    //         execute(cpuReg, cpuMem);
    // }
    
    for (int a = 0; a < 250; a++){
        
        int num = (int)(cpuMem.data[2*a] | (cpuMem.data[2*a+1]<<8));
        std::cout << num << std::endl;    
    
    }
    return 0;
}





