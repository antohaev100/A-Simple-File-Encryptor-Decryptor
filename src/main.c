#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "encryption.h"
#include "decryption.h"

void display_help(const char* program_name) {
    printf("=== File Encryptor/Decryptor ===\n");
    printf("A simple Caesar cipher-based file encryption/decryption tool\n\n");
    
    printf("USAGE:\n");
    printf("  %s <mode> <input_file> <output_file> <key>\n\n", program_name);
    
    printf("MODES:\n");
    printf("  -e, --encrypt    Encrypt the input file\n");
    printf("  -d, --decrypt    Decrypt the input file\n");
    printf("  -h, --help       Display this help message\n\n");
    
    printf("ARGUMENTS:\n");
    printf("  input_file       Path to the input file to process\n");
    printf("  output_file      Path to the output file to create\n");
    printf("  key              Integer key for encryption/decryption (0-255)\n\n");
    
    printf("EXAMPLES:\n");
    printf("  # Encrypt a file with key 42\n");
    printf("  %s --encrypt document.txt encrypted.bin 42\n\n", program_name);
    
    printf("  # Decrypt the encrypted file\n");
    printf("  %s --decrypt encrypted.bin decrypted.txt 42\n\n", program_name);
    
    printf("  # Display help\n");
    printf("  %s --help\n\n", program_name);
    
    printf("NOTES:\n");
    printf("  - The same key must be used for both encryption and decryption\n");
    printf("  - Input and output files can be text or binary files\n");
    printf("  - The program uses Caesar cipher with byte-level operations\n");
    printf("  - Key values outside 0-255 will be normalized automatically\n\n");
}

bool is_valid_integer(const char* str) {
    if (!str || *str == '\0') {
        return false;
    }
    
    // Allow negative numbers
    if (*str == '-') {
        str++;
        if (*str == '\0') {
            return false;
        }
    }
    
    // Check if all remaining characters are digits
    while (*str) {
        if (*str < '0' || *str > '9') {
            return false;
        }
        str++;
    }
    
    return true;
}

int main(int argc, char* argv[]) {
    // Check for minimum number of arguments
    if (argc < 2) {
        fprintf(stderr, "Error: Insufficient arguments\n\n");
        display_help(argv[0]);
        return 1;
    }
    
    // Handle help request
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        display_help(argv[0]);
        return 0;
    }
    
    // Check for correct number of arguments for encrypt/decrypt operations
    if (argc != 5) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        fprintf(stderr, "Expected: %s <mode> <input_file> <output_file> <key>\n", argv[0]);
        fprintf(stderr, "Use '%s --help' for detailed usage information\n", argv[0]);
        return 1;
    }
    
    // Parse arguments
    const char* mode = argv[1];
    const char* input_file = argv[2];
    const char* output_file = argv[3];
    const char* key_str = argv[4];
    
    // Validate key argument
    if (!is_valid_integer(key_str)) {
        fprintf(stderr, "Error: Invalid key '%s'. Key must be a valid integer.\n", key_str);
        return 1;
    }
    
    int key = atoi(key_str);
    
    // Validate file names
    if (strlen(input_file) == 0) {
        fprintf(stderr, "Error: Input filename cannot be empty\n");
        return 1;
    }
    
    if (strlen(output_file) == 0) {
        fprintf(stderr, "Error: Output filename cannot be empty\n");
        return 1;
    }
    
    // Check if input and output files are the same
    if (strcmp(input_file, output_file) == 0) {
        fprintf(stderr, "Error: Input and output files cannot be the same\n");
        return 1;
    }
    
    // Process based on mode
    int result = -1;
    
    if (strcmp(mode, "-e") == 0 || strcmp(mode, "--encrypt") == 0) {
        printf("Mode: Encryption\n");
        printf("Input file: %s\n", input_file);
        printf("Output file: %s\n", output_file);
        printf("Key: %d\n\n", key);
        
        result = encrypt_file(input_file, output_file, key);
        
    } else if (strcmp(mode, "-d") == 0 || strcmp(mode, "--decrypt") == 0) {
        printf("Mode: Decryption\n");
        printf("Input file: %s\n", input_file);
        printf("Output file: %s\n", output_file);
        printf("Key: %d\n\n", key);
        
        result = decrypt_file(input_file, output_file, key);
        
    } else {
        fprintf(stderr, "Error: Invalid mode '%s'\n", mode);
        fprintf(stderr, "Valid modes: -e, --encrypt, -d, --decrypt, -h, --help\n");
        fprintf(stderr, "Use '%s --help' for detailed usage information\n", argv[0]);
        return 1;
    }
    
    // Check operation result
    if (result == 0) {
        printf("\nOperation completed successfully!\n");
        return 0;
    } else {
        fprintf(stderr, "\nOperation failed. Please check the error messages above.\n");
        return 1;
    }
}
