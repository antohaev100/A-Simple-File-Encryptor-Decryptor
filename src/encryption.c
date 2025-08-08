#include "encryption.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t encrypt_byte(uint8_t byte, int key) {
    // Normalize key to positive range and apply modulo 256
    // This ensures the key works correctly even if negative or large
    int normalized_key = ((key % 256) + 256) % 256;
    
    // Perform Caesar cipher encryption
    return (uint8_t)((byte + normalized_key) % 256);
}

int encrypt_file(const char* input_filename, const char* output_filename, int key) {
    // Validate input parameters
    if (!input_filename || !output_filename) {
        fprintf(stderr, "Error: Invalid filename parameters\n");
        return -1;
    }
    
    // Open input file for reading in binary mode
    FILE* input_file = fopen(input_filename, "rb");
    if (!input_file) {
        fprintf(stderr, "Error: Could not open input file '%s' for reading\n", input_filename);
        return -1;
    }
    
    // Open output file for writing in binary mode
    FILE* output_file = fopen(output_filename, "wb");
    if (!output_file) {
        fprintf(stderr, "Error: Could not open output file '%s' for writing\n", output_filename);
        fclose(input_file);
        return -1;
    }
    
    // Process file byte by byte
    int byte;
    size_t bytes_processed = 0;
    
    printf("Encrypting file '%s' to '%s' with key %d...\n", input_filename, output_filename, key);
    
    while ((byte = fgetc(input_file)) != EOF) {
        // Encrypt the byte
        uint8_t encrypted_byte = encrypt_byte((uint8_t)byte, key);
        
        // Write encrypted byte to output file
        if (fputc(encrypted_byte, output_file) == EOF) {
            fprintf(stderr, "Error: Failed to write to output file\n");
            fclose(input_file);
            fclose(output_file);
            return -1;
        }
        
        bytes_processed++;
    }
    
    // Close files
    fclose(input_file);
    fclose(output_file);
    
    printf("Encryption completed successfully. Processed %zu bytes.\n", bytes_processed);
    return 0;
}
