#include "uart_sim.h"

/**
 * Initialize UART buffer with default values
 */
void init_uart_buffer(uart_buffer_t *buffer) {
    if (!buffer) return;

    memset(buffer->data, 0, sizeof(buffer->data));
    buffer->head = 0;
    buffer->tail = 0;
    buffer->count = 0;
    buffer->capacity = MAX_BUFFER_SIZE;
}

/**
 * Write data to UART buffer (circular buffer implementation)
 */
bool buffer_write(uart_buffer_t *buffer, uint8_t data) {
    if (!buffer || buffer_is_full(buffer)) {
        return false;
    }

    buffer->data[buffer->head] = data;
    buffer->head = (buffer->head + 1) % buffer->capacity;
    buffer->count++;

    return true;
}

/**
 * Read data from UART buffer
 */
bool buffer_read(uart_buffer_t *buffer, uint8_t *data) {
    if (!buffer || !data || buffer_is_empty(buffer)) {
        return false;
    }

    *data = buffer->data[buffer->tail];
    buffer->tail = (buffer->tail + 1) % buffer->capacity;
    buffer->count--;

    return true;
}

/**
 * Check if buffer is empty
 */
bool buffer_is_empty(uart_buffer_t *buffer) {
    return buffer ? (buffer->count == 0) : true;
}

/**
 * Check if buffer is full
 */
bool buffer_is_full(uart_buffer_t *buffer) {
    return buffer ? (buffer->count >= buffer->capacity) : true;
}

/**
 * Get current buffer count
 */
size_t buffer_count(uart_buffer_t *buffer) {
    return buffer ? buffer->count : 0;
}

/**
 * Encode data byte into UART frame with start and stop bits
 */
uart_frame_t encode_uart_frame(uint8_t data) {
    uart_frame_t frame;

    frame.start_bit = UART_START_BIT;   // Start bit is always 0
    frame.data_bits = data;             // 8 data bits
    frame.stop_bit = UART_STOP_BIT;     // Stop bit is always 1

    return frame;
}

/**
 * Decode UART frame to extract data byte
 */
uint8_t decode_uart_frame(uart_frame_t frame) {
    // In real UART, we would validate start and stop bits
    // For simulation, we just return the data bits
    return frame.data_bits;
}

/**
 * Print binary representation of a value
 */
void print_binary(uint8_t value, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
}

/**
 * Print UART frame in detail showing all bits
 */
void print_uart_frame(uart_frame_t frame) {
    printf("UART Frame: ");

    // Start bit
    printf("[START:%d] ", frame.start_bit);

    // Data bits (MSB first for display, but UART typically sends LSB first)
    printf("[DATA:");
    print_binary(frame.data_bits, UART_DATA_BITS);
    printf("] ");

    // Stop bit
    printf("[STOP:%d]", frame.stop_bit);

    printf("\n");
}

/**
 * Simulate bit-by-bit UART transmission
 */
void simulate_transmission(uint8_t data) {
    uart_frame_t frame = encode_uart_frame(data);

    printf("\n+=========================================================+\n");
    printf("|            UART TRANSMISSION SIMULATION                |\n");
    printf("+=========================================================+\n");
    printf("| Transmitting: 0x%02X (%3d) '%c'                        |\n", data, data, 
           (data >= 32 && data <= 126) ? data : '.');
    printf("+=========================================================+\n");

    print_uart_frame(frame);

    printf("\nBit-by-bit transmission (LSB first - UART standard):\n");
    printf("Sequence: ");

    // Start bit
    printf("[S:%d] ", frame.start_bit);

    // Data bits (LSB first - UART standard)
    for (int i = 0; i < UART_DATA_BITS; i++) {
        int bit = (frame.data_bits >> i) & 1;
        printf("[%d] ", bit);
    }

    // Stop bit
    printf("[E:%d]", frame.stop_bit);

    printf("\nTotal bits transmitted: %d\n", UART_FRAME_SIZE);
    printf("=========================================\n");
}

/**
 * Simulate UART reception and decoding
 */
void simulate_reception(uart_frame_t frame) {
    printf("\n+=========================================================+\n");
    printf("|             UART RECEPTION SIMULATION                  |\n");
    printf("+=========================================================+\n");

    print_uart_frame(frame);

    // Validate frame
    if (frame.start_bit != UART_START_BIT) {
        printf("ERROR: Invalid start bit! Expected %d, got %d\n", 
               UART_START_BIT, frame.start_bit);
        return;
    }

    if (frame.stop_bit != UART_STOP_BIT) {
        printf("ERROR: Invalid stop bit! Expected %d, got %d\n", 
               UART_STOP_BIT, frame.stop_bit);
        return;
    }

    uint8_t decoded_data = decode_uart_frame(frame);
    printf("SUCCESS: Decoded byte: 0x%02X (%d) '%c'\n", 
           decoded_data, decoded_data, 
           (decoded_data >= 32 && decoded_data <= 126) ? decoded_data : '.');

    printf("=========================================\n");
}

/**
 * Display main menu options
 */
void display_menu(void) {
    printf("\n");
    printf("+=========================================================+\n");
    printf("|                 UART SIMULATOR                          |\n");
    printf("+=========================================================+\n");
    printf("|                                                         |\n");
    printf("| [TX] 1. Transmit Data      [STATUS] 3. Buffer Status    |\n");
    printf("| [RX] 2. Receive Data       [CLEAR]  4. Clear Buffers    |\n");
    printf("| [?]  5. Help & Info        [EXIT]   6. Exit Program     |\n");
    printf("|                                                         |\n");
    printf("+=========================================================+\n");
    printf("\n>> Choose an option (1-6): ");
}

/**
 * Handle data transmission
 */
void transmit_data(uart_buffer_t *tx_buffer, uart_buffer_t *rx_buffer) {
    char input[MAX_INPUT_SIZE];

    printf("\n>> Enter data to transmit: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("ERROR: Could not read input!\n");
        return;
    }

    // Remove newline character
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
        len--;
    }

    if (len == 0) {
        printf("ERROR: No data entered!\n");
        return;
    }

    printf("\n>> Transmitting %zu bytes...\n", len);

    for (size_t i = 0; i < len; i++) {
        uint8_t byte = (uint8_t)input[i];

        // Add to TX buffer
        if (!buffer_write(tx_buffer, byte)) {
            printf("ERROR: TX buffer full! Cannot add more data.\n");
            break;
        }

        // Simulate transmission
        simulate_transmission(byte);

        // Simulate reception (in real system, this would be on receiver side)
        uart_frame_t frame = encode_uart_frame(byte);
        simulate_reception(frame);

        // Add to RX buffer (simulating successful reception)
        if (!buffer_write(rx_buffer, byte)) {
            printf("ERROR: RX buffer full! Data lost.\n");
        }

        printf(">> Press Enter to continue to next byte...");
        getchar();
    }

    printf("SUCCESS: Transmission complete!\n");
}

/**
 * Handle data reception display
 */
void receive_data(uart_buffer_t *rx_buffer) {
    if (buffer_is_empty(rx_buffer)) {
        printf("\nNo data in receive buffer!\n");
        return;
    }

    printf("\nReceived data in buffer:\n");
    printf("=========================================\n");

    // Create temporary buffer to show data without consuming it
    uart_buffer_t temp_buffer = *rx_buffer;
    uint8_t data;
    int count = 0;

    while (buffer_read(&temp_buffer, &data)) {
        printf("Byte %d: 0x%02X (%3d) '%c'\n", count++, data, data,
               (data >= 32 && data <= 126) ? data : '.');
    }

    printf("=========================================\n");
    printf("Total bytes in RX buffer: %d\n", count);

    printf("\nClear the RX buffer? (y/N): ");
    char choice = getchar();
    if (choice == 'y' || choice == 'Y') {
        init_uart_buffer(rx_buffer);
        printf("SUCCESS: RX buffer cleared.\n");
    }
}

/**
 * Show buffer status
 */
void show_buffer_status(uart_buffer_t *tx_buffer, uart_buffer_t *rx_buffer) {
    printf("\n+=========================================================+\n");
    printf("|                   BUFFER STATUS                         |\n");
    printf("+=========================================================+\n");
    printf("|                                                         |\n");
    printf("| TX Buffer: %3zu / %3zu bytes                              |\n", 
           buffer_count(tx_buffer), tx_buffer->capacity);
    printf("| RX Buffer: %3zu / %3zu bytes                              |\n", 
           buffer_count(rx_buffer), rx_buffer->capacity);
    printf("|                                                         |\n");
    printf("| TX Status: %-10s   RX Status: %-10s                     |\n", 
           buffer_is_empty(tx_buffer) ? "Empty" : 
           buffer_is_full(tx_buffer) ? "Full" : "Partial",
           buffer_is_empty(rx_buffer) ? "Empty" : 
           buffer_is_full(rx_buffer) ? "Full" : "Partial");
    printf("|                                                         |\n");
    printf("+=========================================================+\n");
}

/**
 * Clear both buffers
 */
void clear_buffers(uart_buffer_t *tx_buffer, uart_buffer_t *rx_buffer) {
    init_uart_buffer(tx_buffer);
    init_uart_buffer(rx_buffer);
    printf("\nSUCCESS: Both TX and RX buffers cleared!\n");
}
