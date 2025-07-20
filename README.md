# UART Transmission Simulator

## Overview

A C console application that simulates UART (Universal Asynchronous Receiver/Transmitter) serial transmission using bitwise operations and buffer handling. This educational simulator demonstrates serial protocol concepts and provides an interactive console interface for testing transmission and reception.

## User Preferences

Preferred communication style: Simple, everyday language.

## System Architecture

### Technology Stack
- Language: C (C99 standard)
- Compiler: GCC with strict warnings enabled
- Build System: Makefile with multiple targets
- No external dependencies (uses only standard C library)

### Core Components
- **uart_sim.h**: Header file with all type definitions and function prototypes
- **uart_sim.c**: Core UART simulation logic and buffer management
- **main.c**: User interface and main program loop
- **Makefile**: Build configuration with debug, release, and utility targets

## Key Features

### UART Protocol Implementation
- 8N1 frame format (8 data bits, no parity, 1 stop bit)
- Start bit (always 0) and stop bit (always 1)
- LSB-first transmission (UART standard)
- Frame validation with error detection

### Buffer Management
- Circular buffer implementation for TX/RX operations
- 256-byte buffer capacity per channel
- Full/empty status checking
- Thread-safe buffer operations

### Bitwise Operations
- Bit shifting for data extraction
- Bitwise AND for bit masking
- Binary representation display
- Frame encoding/decoding

## Data Flow

1. User inputs text string via console
2. Each character is encoded into UART frame (start + 8 data bits + stop)
3. Frame is stored in TX buffer
4. Bit-by-bit transmission simulation with visual output
5. Reception simulation validates frame integrity
6. Decoded data is stored in RX buffer
7. User can view received data and buffer status

## Interactive Features

- Menu-driven interface with 6 options
- Real-time transmission visualization
- Buffer status monitoring
- Educational UART protocol information
- Step-by-step transmission demonstration

## Build Targets

- `make all`: Standard build
- `make run`: Build and execute
- `make debug`: Debug build with symbols
- `make release`: Optimized release build
- `make clean`: Remove build artifacts
- `make memcheck`: Valgrind memory analysis

## Recent Changes

- ✓ Complete UART simulator implementation 
- ✓ Interactive console interface with menu system
- ✓ Bitwise transmission logic with LSB-first ordering
- ✓ Circular buffer management for TX/RX operations
- ✓ Educational help system explaining UART protocol
- ✓ Visual frame representation and error detection
- ✓ Comprehensive build system with multiple targets

### Deployment Commands
- Primary: ./uart_simulator
- Build: gcc -Wall -Wextra -std=c99 -pedantic -g -o uart_simulator main.c uart_sim.c