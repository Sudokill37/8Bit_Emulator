cmake_minimum_required(VERSION 3.0)
project(emul)

# Add the executable
add_executable(emul main.cpp cpu.cpp)

add_subdirectory(assembler)

# Specify that building the main project depends on building the CLI tool
add_dependencies(emul assemble)