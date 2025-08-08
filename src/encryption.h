#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdint.h>
#include <stdio.h>

uint8_t encrypt_byte(uint8_t byte, int key);

int encrypt_file(const char* input_filename, const char* output_filename, int key);

#endif // ENCRYPTION_H
