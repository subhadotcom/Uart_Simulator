#include "uart_sim.h"

/**
 * Display UART protocol information
 */
void show_uart_info(void) {
    printf("\n===============================================================================\n");
    printf("                            UART PROTOCOL INFORMATION                         \n");
    printf("===============================================================================\n");
    printf("                                                                               \n");
    printf(" UART (Universal Asynchronous Receiver/Transmitter) is a serial              \n");
    printf(" communication protocol used for transmitting data between devices.          \n");
    printf("                                                                               \n");
    printf(" Frame Structure (8N1 format):                                                \n");
    printf(" +-----+----------------------------------------+-----+                     \n");
    printf(" |START| D0  D1  D2  D3  D4  D5  D6  D7         |STOP |                     \n");
    printf(" | 0   |       8 Data Bits (LSB first)          | 1   |                     \n");
    printf(" +-----+----------------------------------------+-----+                     \n");
    printf("                                                                               \n");
    printf(" Key Features:                                                                \n");
    printf(" * Asynchronous: No shared clock signal                                      \n");
    printf(" * Start Bit: Always 0 (signals beginning of frame)                          \n");
    printf(" * Data Bits: 8 bits transmitted LSB (Least Significant Bit) first          \n");
    printf(" * Stop Bit: Always 1 (signals end of frame)                                 \n");
    printf(" * No Parity: No error checking bit in 8N1 format                            \n");
    printf("                                                                               \n");
    printf(" Bitwise Operations Used:                                                     \n");
    printf(" * Bit shifting (>>, <<): Extract individual bits                            \n");
    printf(" * Bitwise AND (&): Mask specific bits                                       \n");
    printf(" * Bitwise OR (|): Set specific bits                                         \n");
    printf("                                                                               \n");
    printf(" Buffer Management:                                                           \n");
    printf(" * Circular buffer implementation                                             \n");
    printf(" * TX Buffer: Holds data to be transmitted                                   \n");
    printf(" * RX Buffer: Holds received data                                            \n");
    printf("                                                                               \n");
    printf("===============================================================================\n");
}

/**
 * Main program entry point
 */
int main(void) {
    uart_buffer_t tx_buffer, rx_buffer;
    int choice;
    
    // Initialize buffers
    init_uart_buffer(&tx_buffer);
    init_uart_buffer(&rx_buffer);
    
    printf("===============================================================================\n");
    printf("                        UART TRANSMISSION SIMULATOR                           \n");
    printf("===============================================================================\n");
    printf("                                                                               \n");
    printf(" This program simulates UART (Universal Asynchronous Receiver/Transmitter)   \n");
    printf(" serial communication using bitwise operations and buffer management.        \n");
    printf("                                                                               \n");
    printf(" Features:                                                                     \n");
    printf(" * 8N1 UART frame format (8 data bits, no parity, 1 stop bit)                \n");
    printf(" * Bit-level data encoding and decoding                                       \n");
    printf(" * Circular buffer implementation for TX/RX                                   \n");
    printf(" * Visual representation of bit transmission                                  \n");
    printf(" * Error detection for invalid frames                                         \n");
    printf("===============================================================================\n");
    
    while (1) {
        display_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        
        // Clear input buffer
        getchar();
        
        switch (choice) {
            case 1:
                transmit_data(&tx_buffer, &rx_buffer);
                break;
                
            case 2:
                receive_data(&rx_buffer);
                break;
                
            case 3:
                show_buffer_status(&tx_buffer, &rx_buffer);
                break;
                
            case 4:
                clear_buffers(&tx_buffer, &rx_buffer);
                break;
                
            case 5:
                show_uart_info();
                break;
                
            case 6:
                printf("\nThank you for using UART Simulator!\n");
                printf("Educational simulation complete.\n");
                return 0;
                
            default:
                printf("Invalid choice! Please select 1-6.\n");
                break;
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }
    
    return 0;
}
