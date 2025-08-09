#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "encryption.h"
#include "decryption.h"

// Test byte-level encryption/decryption
static void test_byte_encryption_basic(void **state) {
    (void)state; // Suppress unused parameter warning
    
    uint8_t original = 65; // 'A'
    int key = 10;
    
    uint8_t encrypted = encrypt_byte(original, key);
    uint8_t decrypted = decrypt_byte(encrypted, key);
    
    assert_int_equal(decrypted, original);
}

static void test_byte_encryption_edge_cases(void **state) {
    (void)state; // Suppress unused parameter warning
    
    // Test with 0
    uint8_t original = 0;
    int key = 100;
    uint8_t encrypted = encrypt_byte(original, key);
    uint8_t decrypted = decrypt_byte(encrypted, key);
    assert_int_equal(decrypted, original);
    
    // Test with 255
    original = 255;
    key = 200;
    encrypted = encrypt_byte(original, key);
    decrypted = decrypt_byte(encrypted, key);
    assert_int_equal(decrypted, original);
}

static void test_byte_encryption_negative_key(void **state) {
    (void)state; // Suppress unused parameter warning

    uint8_t original = 100;
    int key = -50;
    
    uint8_t encrypted = encrypt_byte(original, key);
    uint8_t decrypted = decrypt_byte(encrypted, key);
    
    assert_int_equal(decrypted, original);
}

static void test_byte_encryption_large_key(void **state) {
    (void)state; // Suppress unused parameter warning

    uint8_t original = 150;
    int key = 1000; // Should be normalized to key % 256
    
    uint8_t encrypted = encrypt_byte(original, key);
    uint8_t decrypted = decrypt_byte(encrypted, key);
    
    assert_int_equal(decrypted, original);
}

// Helper function to create test files
static void create_test_file(const char* filename, const char* content, size_t size) {
    FILE* file = fopen(filename, "wb");
    assert_non_null(file);
    
    size_t written = fwrite(content, 1, size, file);
    assert_int_equal(written, size);
    
    fclose(file);
}

// Helper function to read file content
static char* read_test_file(const char* filename, size_t* size) {
    FILE* file = fopen(filename, "rb");
    assert_non_null(file);
    
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = malloc(*size);
    assert_non_null(content);
    
    size_t read_size = fread(content, 1, *size, file);
    assert_int_equal(read_size, *size);
    
    fclose(file);
    return content;
}

// Test text file encryption/decryption
static void test_text_file_encryption(void **state) {
    (void)state; // Suppress unused parameter warning

    const char* input_file = "test_input.txt";
    const char* encrypted_file = "test_encrypted.bin";
    const char* decrypted_file = "test_decrypted.txt";
    const char* test_content = "Hello, World! This is a test file with various characters: 123 !@#$%";
    int key = 42;
    
    // Create test file
    create_test_file(input_file, test_content, strlen(test_content));
    
    // Encrypt
    int result = encrypt_file(input_file, encrypted_file, key);
    assert_int_equal(result, 0);
    
    // Decrypt
    result = decrypt_file(encrypted_file, decrypted_file, key);
    assert_int_equal(result, 0);
    
    // Compare original and decrypted content
    size_t original_size, decrypted_size;
    char* original_content = read_test_file(input_file, &original_size);
    char* decrypted_content = read_test_file(decrypted_file, &decrypted_size);
    
    assert_int_equal(original_size, decrypted_size);
    assert_memory_equal(original_content, decrypted_content, original_size);
    
    // Cleanup
    free(original_content);
    free(decrypted_content);
    unlink(input_file);
    unlink(encrypted_file);
    unlink(decrypted_file);
}

// Test binary file encryption/decryption
static void test_binary_file_encryption(void **state) {
    (void)state; // Suppress unused parameter warning
    
    const char* input_file = "test_binary.bin";
    const char* encrypted_file = "test_binary_encrypted.bin";
    const char* decrypted_file = "test_binary_decrypted.bin";
    int key = 123;
    
    // Create binary test data
    uint8_t binary_data[256];
    for (int i = 0; i < 256; i++) {
        binary_data[i] = (uint8_t)i;
    }
    
    create_test_file(input_file, (char*)binary_data, 256);
    
    // Encrypt
    int result = encrypt_file(input_file, encrypted_file, key);
    assert_int_equal(result, 0);
    
    // Decrypt
    result = decrypt_file(encrypted_file, decrypted_file, key);
    assert_int_equal(result, 0);
    
    // Compare original and decrypted content
    size_t original_size, decrypted_size;
    char* original_content = read_test_file(input_file, &original_size);
    char* decrypted_content = read_test_file(decrypted_file, &decrypted_size);
    
    assert_int_equal(original_size, decrypted_size);
    assert_memory_equal(original_content, decrypted_content, original_size);
    
    // Cleanup
    free(original_content);
    free(decrypted_content);
    unlink(input_file);
    unlink(encrypted_file);
    unlink(decrypted_file);
}

// Test empty file
static void test_empty_file_encryption(void **state) {
    (void)state; // Suppress unused parameter warning
    
    const char* input_file = "test_empty.txt";
    const char* encrypted_file = "test_empty_encrypted.bin";
    const char* decrypted_file = "test_empty_decrypted.txt";
    int key = 50;
    
    // Create empty file
    create_test_file(input_file, "", 0);
    
    // Encrypt
    int result = encrypt_file(input_file, encrypted_file, key);
    assert_int_equal(result, 0);
    
    // Decrypt
    result = decrypt_file(encrypted_file, decrypted_file, key);
    assert_int_equal(result, 0);
    
    // Check that all files are empty
    size_t encrypted_size, decrypted_size;
    char* encrypted_content = read_test_file(encrypted_file, &encrypted_size);
    char* decrypted_content = read_test_file(decrypted_file, &decrypted_size);
    
    assert_int_equal(encrypted_size, 0);
    assert_int_equal(decrypted_size, 0);
    
    // Cleanup
    free(encrypted_content);
    free(decrypted_content);
    unlink(input_file);
    unlink(encrypted_file);
    unlink(decrypted_file);
}

// Test large file encryption/decryption
static void test_large_file_encryption(void **state) {
    (void)state; // Suppress unused parameter warning
    
    const char* input_file = "test_large.bin";
    const char* encrypted_file = "test_large_encrypted.bin";
    const char* decrypted_file = "test_large_decrypted.bin";
    int key = 200;
    size_t file_size = 10000; // 10KB
    
    // Create large test data
    char* large_data = malloc(file_size);
    assert_non_null(large_data);
    
    for (size_t i = 0; i < file_size; i++) {
        large_data[i] = (char)(i % 256);
    }
    
    create_test_file(input_file, large_data, file_size);
    
    // Encrypt
    int result = encrypt_file(input_file, encrypted_file, key);
    assert_int_equal(result, 0);
    
    // Decrypt
    result = decrypt_file(encrypted_file, decrypted_file, key);
    assert_int_equal(result, 0);
    
    // Compare original and decrypted content
    size_t original_size, decrypted_size;
    char* original_content = read_test_file(input_file, &original_size);
    char* decrypted_content = read_test_file(decrypted_file, &decrypted_size);
    
    assert_int_equal(original_size, decrypted_size);
    assert_int_equal(original_size, file_size);
    assert_memory_equal(original_content, decrypted_content, original_size);
    
    // Cleanup
    free(large_data);
    free(original_content);
    free(decrypted_content);
    unlink(input_file);
    unlink(encrypted_file);
    unlink(decrypted_file);
}

// Test error conditions
static void test_invalid_input_file(void **state) {
    (void)state; // Suppress unused parameter warning
    
    const char* nonexistent_file = "nonexistent.txt";
    const char* output_file = "output.bin";
    int key = 42;
    
    int result = encrypt_file(nonexistent_file, output_file, key);
    assert_int_equal(result, -1);
}

static void test_null_parameters(void **state) {
    (void)state; // Suppress unused parameter warning
    
    int result = encrypt_file(NULL, "output.bin", 42);
    assert_int_equal(result, -1);
    
    result = encrypt_file("input.txt", NULL, 42);
    assert_int_equal(result, -1);
    
    result = decrypt_file(NULL, "output.txt", 42);
    assert_int_equal(result, -1);
    
    result = decrypt_file("input.bin", NULL, 42);
    assert_int_equal(result, -1);
}

// Test with a small image file
static void test_image_file_encryption(void **state) {
    (void)state;
    
    const char* input_file = "test_image.bmp";
    const char* encrypted_file = "test_image_encrypted.bin";
    const char* decrypted_file = "test_image_decrypted.bmp";
    int key = 75;
    
    // Create a minimal BMP file (54-byte header + 4x4 pixel data)
    uint8_t bmp_data[] = {
        // BMP Header (14 bytes)
        0x42, 0x4D,             // "BM" signature
        0x7A, 0x00, 0x00, 0x00, // File size (122 bytes)
        0x00, 0x00, 0x00, 0x00, // Reserved
        0x36, 0x00, 0x00, 0x00, // Offset to pixel data
        
        // DIB Header (40 bytes)
        0x28, 0x00, 0x00, 0x00, // Header size
        0x04, 0x00, 0x00, 0x00, // Width (4 pixels)
        0x04, 0x00, 0x00, 0x00, // Height (4 pixels)
        0x01, 0x00,             // Planes
        0x18, 0x00,             // Bits per pixel (24)
        0x00, 0x00, 0x00, 0x00, // Compression
        0x30, 0x00, 0x00, 0x00, // Image size
        0x13, 0x0B, 0x00, 0x00, // X pixels per meter
        0x13, 0x0B, 0x00, 0x00, // Y pixels per meter
        0x00, 0x00, 0x00, 0x00, // Colors used
        0x00, 0x00, 0x00, 0x00, // Important colors
        
        // Pixel data (48 bytes for 4x4 24-bit image)
        0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
        0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10,
        0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
        0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11, 0x22
    };
    
    create_test_file(input_file, (char*)bmp_data, sizeof(bmp_data));
    
    // Encrypt
    int result = encrypt_file(input_file, encrypted_file, key);
    assert_int_equal(result, 0);
    
    // Decrypt
    result = decrypt_file(encrypted_file, decrypted_file, key);
    assert_int_equal(result, 0);
    
    // Verify integrity
    size_t original_size, decrypted_size;
    char* original_content = read_test_file(input_file, &original_size);
    char* decrypted_content = read_test_file(decrypted_file, &decrypted_size);
    
    assert_int_equal(original_size, decrypted_size);
    assert_int_equal(original_size, sizeof(bmp_data));
    assert_memory_equal(original_content, decrypted_content, original_size);
    
    // Cleanup
    free(original_content);
    free(decrypted_content);
    unlink(input_file);
    unlink(encrypted_file);
    unlink(decrypted_file);
}

// Test with a JPEG-like file structure
static void test_jpeg_like_file_encryption(void **state) {
    (void)state;
    
    const char* input_file = "test_image.jpg";
    const char* encrypted_file = "test_image_encrypted.bin";
    const char* decrypted_file = "test_image_decrypted.jpg";
    int key = 150;
    
    // Create minimal JPEG-like data with markers
    uint8_t jpeg_data[] = {
        // JPEG markers and data
        0xFF, 0xD8,             // SOI (Start of Image)
        0xFF, 0xE0,             // APP0 marker
        0x00, 0x10,             // Length
        0x4A, 0x46, 0x49, 0x46, // "JFIF"
        0x00, 0x01, 0x01,       // Version
        0x01, 0x00, 0x48,       // Density info
        0x00, 0x48, 0x00, 0x00,
        
        // Fake compressed data
        0xFF, 0xC0,             // SOF0 marker
        0x00, 0x11,             // Length
        0x08, 0x00, 0x10, 0x00, 0x10, // Sample precision, height, width
        0x01, 0x01, 0x11, 0x00, // Component info
        0x02, 0x11, 0x01, 0x03, 0x11, 0x01,
        
        // More fake data with various byte patterns
        0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0,
        0x00, 0xFF, 0x80, 0x7F, 0x40, 0xBF, 0x20, 0xDF,
        
        0xFF, 0xD9              // EOI (End of Image)
    };
    
    create_test_file(input_file, (char*)jpeg_data, sizeof(jpeg_data));
    
    // Encrypt
    int result = encrypt_file(input_file, encrypted_file, key);
    assert_int_equal(result, 0);
    
    // Decrypt
    result = decrypt_file(encrypted_file, decrypted_file, key);
    assert_int_equal(result, 0);
    
    // Verify integrity
    size_t original_size, decrypted_size;
    char* original_content = read_test_file(input_file, &original_size);
    char* decrypted_content = read_test_file(decrypted_file, &decrypted_size);
    
    assert_int_equal(original_size, decrypted_size);
    assert_memory_equal(original_content, decrypted_content, original_size);
    
    // Cleanup
    free(original_content);
    free(decrypted_content);
    unlink(input_file);
    unlink(encrypted_file);
    unlink(decrypted_file);
}

// Test with video-like file (MP4 structure)
static void test_video_like_file_encryption(void **state) {
    (void)state;
    
    const char* input_file = "test_video.mp4";
    const char* encrypted_file = "test_video_encrypted.bin";
    const char* decrypted_file = "test_video_decrypted.mp4";
    int key = 88;
    
    // Create minimal MP4-like data with atoms
    uint8_t mp4_data[] = {
        // ftyp atom
        0x00, 0x00, 0x00, 0x20, // Size
        0x66, 0x74, 0x79, 0x70, // "ftyp"
        0x69, 0x73, 0x6F, 0x6D, // "isom"
        0x00, 0x00, 0x02, 0x00, // Minor version
        0x69, 0x73, 0x6F, 0x6D, // Compatible brands
        0x69, 0x73, 0x6F, 0x32,
        0x61, 0x76, 0x63, 0x31,
        0x6D, 0x70, 0x34, 0x31,
        
        // mdat atom with fake video data
        0x00, 0x00, 0x00, 0x40, // Size
        0x6D, 0x64, 0x61, 0x74, // "mdat"
        
        // Fake compressed video data with various patterns
        0x00, 0x00, 0x01, 0x67, // NAL unit start
        0x42, 0xE0, 0x1E, 0x9E, // SPS data
        0xE4, 0x8B, 0x8B, 0x22,
        0xC8, 0x48, 0x96, 0x58,
        
        0x00, 0x00, 0x01, 0x68, // Another NAL unit
        0xCE, 0x3C, 0x80, 0x00,
        0xFF, 0xEE, 0xDD, 0xCC,
        0xBB, 0xAA, 0x99, 0x88,
        
        // More diverse byte patterns
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
        0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
        0xF0, 0x0F, 0xAA, 0x55, 0xC3, 0x3C, 0x69, 0x96
    };
    
    create_test_file(input_file, (char*)mp4_data, sizeof(mp4_data));
    
    // Encrypt
    int result = encrypt_file(input_file, encrypted_file, key);
    assert_int_equal(result, 0);
    
    // Decrypt
    result = decrypt_file(encrypted_file, decrypted_file, key);
    assert_int_equal(result, 0);
    
    // Verify integrity
    size_t original_size, decrypted_size;
    char* original_content = read_test_file(input_file, &original_size);
    char* decrypted_content = read_test_file(decrypted_file, &decrypted_size);
    
    assert_int_equal(original_size, decrypted_size);
    assert_memory_equal(original_content, decrypted_content, original_size);
    
    // Cleanup
    free(original_content);
    free(decrypted_content);
    unlink(input_file);
    unlink(encrypted_file);
    unlink(decrypted_file);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_byte_encryption_basic),
        cmocka_unit_test(test_byte_encryption_edge_cases),
        cmocka_unit_test(test_byte_encryption_negative_key),
        cmocka_unit_test(test_byte_encryption_large_key),
        cmocka_unit_test(test_text_file_encryption),
        cmocka_unit_test(test_binary_file_encryption),
        cmocka_unit_test(test_empty_file_encryption),
        cmocka_unit_test(test_large_file_encryption),
        cmocka_unit_test(test_image_file_encryption),        
        cmocka_unit_test(test_jpeg_like_file_encryption),    
        cmocka_unit_test(test_video_like_file_encryption),   
        cmocka_unit_test(test_invalid_input_file),
        cmocka_unit_test(test_null_parameters),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}