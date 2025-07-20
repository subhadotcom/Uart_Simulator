#ifndef UART_SIM_H
#define UART_SIM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// UART Configuration Constants
#define UART_DATA_BITS 8
#define UART_START_BIT 0
#define UART_STOP_BIT 1
#define UART_FRAME_SIZE (1 + UART_DATA_BITS + 1)  // Start + Data + Stop
#define MAX_BUFFER_SIZE 256
#define MAX_INPUT_SIZE 100

// UART Frame Structure
typedef struct {
    uint8_t start_bit;      // Always 0
    uint8_t data_bits;      // 8 data bits
    uint8_t stop_bit;       // Always 1
} uart_frame_t;

// UART Buffer Structure
typedef struct {
    uint8_t data[MAX_BUFFER_SIZE];
    size_t head;            // Write position
    size_t tail;            // Read position
    size_t count;           // Number of elements in buffer
    size_t capacity;        // Maximum capacity
} uart_buffer_t;

// Function prototypes
void init_uart_buffer(uart_buffer_t *buffer);
bool buffer_write(uart_buffer_t *buffer, uint8_t data);
bool buffer_read(uart_buffer_t *buffer, uint8_t *data);
bool buffer_is_empty(uart_buffer_t *buffer);
bool buffer_is_full(uart_buffer_t *buffer);
size_t buffer_count(uart_buffer_t *buffer);

uart_frame_t encode_uart_frame(uint8_t data);
uint8_t decode_uart_frame(uart_frame_t frame);
void print_binary(uint8_t value, int bits);
void print_uart_frame(uart_frame_t frame);
void simulate_transmission(uint8_t data);
void simulate_reception(uart_frame_t frame);

void display_menu(void);
void transmit_data(uart_buffer_t *tx_buffer, uart_buffer_t *rx_buffer);
void receive_data(uart_buffer_t *rx_buffer);
void show_buffer_status(uart_buffer_t *tx_buffer, uart_buffer_t *rx_buffer);
void clear_buffers(uart_buffer_t *tx_buffer, uart_buffer_t *rx_buffer);

#endif // UART_SIM_H
