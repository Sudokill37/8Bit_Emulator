#include <iostream>
#include <fstream>
#include <string>

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
    std::ifstream input_file(input_file_name, std::ios::binary);
    if (!input_file) {
        std::cerr << "Error: Unable to open input file: " << input_file_name << "\n";
        return 1;
    }

    // Determine the size of the input file in bytes
    input_file.seekg(0, std::ios::end);
    std::streampos file_size = input_file.tellg();
    input_file.seekg(0, std::ios::beg);

    // Open the output file for writing
    std::ofstream output_file(output_file_name);
    if (!output_file) {
        std::cerr << "Error: Unable to open output file: " << output_file_name << "\n";
        return 1;
    }

    // Write the size of the input file to the output file
    output_file << "Input file size: " << file_size << " bytes\n";

    std::cout << "Input file size: " << file_size << " bytes\n";
    std::cout << "File size written to '" << output_file_name << "' successfully.\n";

    // Close files
    input_file.close();
    output_file.close();

    return 0;
}
