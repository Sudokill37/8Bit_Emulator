#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <bitset>


std::vector<std::string> lines;
std::string line;
void parseLine(std::string& line, std::ofstream& output_file);
std::string makeLower(const std::string& input);


int main(int argc, char* argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    // Get the input and output file names from command-line arguments
    std::string input_file_name = argv[1];
    std::string output_file_name = argv[2];

    // Open the input file for reading
    std::ifstream input_file(input_file_name);
    if (!input_file) {
        std::cerr << "Error: Unable to open input file: " << input_file_name << "\n";
        return 1;
    }

    std::ofstream output_file(output_file_name);
    if (!output_file) {
        std::cerr << "Error: Unable to open output file: " << output_file_name << "\n";
        return 1;
    }

    while(std::getline(input_file, line)){
        lines.push_back(line);
        //std::cout << line << std::endl;
    }

    for( auto& line : lines){
        std::string low = makeLower(line);
        parseLine(low, output_file);
    }
    
    std::cout <<"test\n";


    input_file.close();
    output_file.close();

    return 0;
}

void parseLine(std::string& line, std::ofstream& output_file){



    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;

    uint8_t opcode = 0;
    
    std::vector<std::string> instructions = {"nop", "add", "addi", "and", "andi", "not", "beqa", "beqr", "hlt", "lb", "sb", "lsr", "lsl", "inc", "dec"};
    
    while(iss >> token){
        tokens.push_back(token);
        
    }

    if(tokens.size() <= 0){
        return;
    }

    for(int i = 0; i < instructions.size(); i++){
        if(tokens[0]==instructions[i]){
            opcode = i;
        }
    }

    output_file << std::bitset<4>(opcode);

    if(tokens.size() != 4) {
            std::cerr<<"invalid operands\n";
    }
    else{
           output_file << std::bitset<4>(std::stoi(tokens[1]))<<std::bitset<4>(std::stoi(tokens[2]))<<std::bitset<4>(std::stoi(tokens[3]))<<std::endl;
    }
    // switch (opcode){
    // case 0b0000:
    //     output_file << std::bitset<12>(0)<<std::endl;
    //     break;
    // case 0b0001:
    //     if(tokens.size() != 4) {
    //         std::cerr<<"invalid operands\n";
    //     }
    //     else{
    //         output_file << std::bitset<4>(std::stoi(tokens[1]))<<std::bitset<4>(std::stoi(tokens[2]))<<std::bitset<4>(std::stoi(tokens[3]))<<std::endl;
    //     }
    //     break;
    // case 0b0011:
    //     if(tokens.size() != 4) {
    //         std::cerr<<"invalid operands\n";
    //     }
    //     else{
    //         output_file << std::bitset<4>(std::stoi(tokens[1]))<<std::bitset<4>(std::stoi(tokens[2]))<<std::bitset<4>(std::stoi(tokens[3]))<<std::endl;
    //     }
    //     break;
    // case 0b1000:
    //     output_file << std::bitset<16>(0)<<std::endl;
    //     break;
    // default:
    //     std::cerr << "opcode not implemented" << std::endl;
    // }
    
    
}

 std::string makeLower(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (std::isupper(c)) {
            result += std::tolower(c);
        } else {
            result += c;
        }
    }
    return result;
}
