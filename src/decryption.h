#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <stdint.h>
#include <stdio.h>

uint8_t decrypt_byte(uint8_t encrypted_byte, int key);

int decrypt_file(const char* input_filename, const char* output_filename, int key);

#endif // DECRYPTION_H
