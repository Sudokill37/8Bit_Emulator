# Simple 8-Bit CPU Documentation

## Introduction
This document provides an overview of the architecture and features of the Simple 8-Bit CPU, a basic 8-bit processor designed for educational purposes and small-scale embedded systems.

## CPU Architecture
The Simple 8-Bit CPU is based on a minimalist architecture optimized for simplicity and ease of understanding. It features the following key components:

- **ALU (Arithmetic Logic Unit)**: Performs arithmetic and logical operations on data.
- **Control Unit**: Decodes instructions and controls the flow of data within the CPU.
- **Registers**: Small, fast storage locations within the CPU used for temporary data storage and holding operands.
- **Memory Interface**: Allows the CPU to interact with external memory to fetch instructions and data.

## Instruction Set
The Simple 8-Bit CPU supports a simple and compact instruction set designed to perform basic arithmetic, logical, memory access, and control flow operations. Instructions are encoded as 16-bit values and executed in a single cycle. The instruction set includes the following operations:

- **NOP**: No operation
- **ADD**: Add two operands
- **ADDI**: Add immediate value to a register
- **SUB**: Subtract one operand from another
- **SUBI**: Subtract imeediate value from a register
- **AND**: Perform bitwise AND operation
- **ANDI**: Perform bitwise AND operation with immediate value
- **NOT**: Perform bitwise NOT operation
- **LSR**: Logical shift right
- **LSL**: Logical shift left
- **BRF**: Branch if selected flag is set
- **BNF**: Branch if selected flag is not set
- **JMP**: Unconditional Jump
- **LB**: Load byte from memory
- **SB**: Store byte to memory
- **RST**: Reset Execution

## Memory Organization
The Simple 8-Bit CPU features a 16-bit addressable memory, allowing access to 64KB of memory space. Memory is divided into three main regions, each serving different purposes:

- **Instruction Memory**: Stores program instructions.
  - Size: 2048 bytes (2KB)

- **Data Memory**: Stores program data and peripheral data. This region is used for general-purpose data storage.
  - Size: 61184 bytes (59.75KB)

- **Stack**: Used for storing temporary data and return addresses during subroutine calls.
  - Size: 256 bytes

The memory organization provides flexibility for storing program code, data, and stack frames, accommodating the needs of various applications and algorithms running on the Simple 8-Bit CPU.

## Register Set
The Simple 8-Bit CPU includes a set of registers for storing temporary data and managing program flow. The register set includes the following registers:

- **W, X, Y, Z**: General-purpose registers (compatible with I-type instructions).
- **PC**: Program counter register (R-type only).
- **PCU**: Program counter upper register (R-type only).
- **SP**: Stack pointer register (R-type only).
- **SR**: Status register (R-type only). Flags: Zero, Sign, Overflow, Parity, Reset. (Format: ZSVPRXXX)
- **AR**: Address register (R-type only).
- **ARU**: Address register upper register (R-type only).

## Conclusion
The Simple 8-Bit CPU is a basic yet versatile processor designed for educational purposes and simple embedded systems. Its minimalist architecture and instruction set make it easy to understand and implement, making it an ideal platform for learning about computer architecture and digital design.
