# File Encryptor/Decryptor

A professional-grade file encryption and decryption tool implemented in C using the Caesar cipher algorithm. This project demonstrates over-engineered software development practices with comprehensive testing, documentation, and agile workflow management.

## 🔐 Features

- **Universal File Support**: Encrypts and decrypts any file type (text, images, videos, executables, etc.)
- **Caesar Cipher Implementation**: Byte-level encryption with configurable key values
- **Command-Line Interface**: Professional CLI with help system and error handling
- **Cross-Platform**: Works on Windows, Linux, and macOS
- **Comprehensive Testing**: Full test suite using CMocka framework
- **Professional Build System**: CMake-based build configuration
- **Data Integrity**: Maintains perfect file integrity through encrypt/decrypt cycles

## 🚀 Quick Start

### Prerequisites

- **C Compiler**: GCC 15.1.0 or compatible (supports C11 standard)
- **CMake**: Version 3.10 or higher
- **CMocka**: For running tests *(optional - tests will be disabled if not available)*

### Platform-Specific Setup

#### Linux (Ubuntu/Debian):
```bash
sudo apt-get install build-essential cmake libcmocka-dev
```

#### macOS:
```bash
brew install cmake cmocka
```

#### Windows (MSYS2):
```bash
pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-cmocka
# pkg-config (pkgconf) is included by default in MSYS2
```

### Building the Project

```bash
# Clone the repository
git clone https://github.com/antohaev100/A-Simple-File-Encryptor-Decryptor.git
cd A-Simple-File-Encryptor-Decryptor

# Create build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build the executable
cmake --build .

# Run tests (only if CMocka is installed)
ctest --verbose
```

**Note**: If CMocka is not installed, the main program will still build successfully, but tests will be disabled.

### Basic Usage

```bash
# Display help information
./FileEncryptor --help

# Encrypt a file
./FileEncryptor --encrypt input.txt encrypted.bin 42

# Decrypt a file
./FileEncryptor --decrypt encrypted.bin decrypted.txt 42
```

## 📖 Detailed Usage

### Command-Line Options

| Option | Short | Description |
|--------|-------|-------------|
| `--encrypt` | `-e` | Encrypt the input file |
| `--decrypt` | `-d` | Decrypt the input file |
| `--help` | `-h` | Display help information |

### Arguments

1. **Mode**: Operation to perform (`--encrypt` or `--decrypt`)
2. **Input File**: Path to the file to process
3. **Output File**: Path where the result will be saved
4. **Key**: Integer encryption key (0-255 recommended, larger values are normalized)

### Examples

```bash
# Encrypt a text document
./FileEncryptor --encrypt "my-document.txt" "encrypted-document.bin" 123

# Encrypt an image
./FileEncryptor --encrypt "photo.jpg" "encrypted-photo.bin" 89

# Decrypt back to original
./FileEncryptor --decrypt "encrypted-photo.bin" "recovered-photo.jpg" 89

# Using different key values
./FileEncryptor --encrypt "data.bin" "encrypted.bin" -50   # Negative keys work
./FileEncryptor --encrypt "data.bin" "encrypted.bin" 1000  # Large keys are normalized
```

## 🏗️ Project Structure

```
├── src/                    # Source code
│   ├── main.c             # CLI interface and main function
│   ├── encryption.c       # Encryption implementation
│   ├── encryption.h       # Encryption header
│   ├── decryption.c       # Decryption implementation
│   └── decryption.h       # Decryption header
├── tests/                 # Test suite
│   ├── CMakeLists.txt     # Test build configuration
│   └── test_encryption.c  # Comprehensive test cases
├── build/                 # Build artifacts (generated)
├── CMakeLists.txt         # Main build configuration
├── README.md              # This file
├── SCOPE.md               # Project scope definition
├── CONTRIBUTING.md        # Contribution guidelines
└── LICENSE.md             # Project license
```

## 🔬 Algorithm Details

### Caesar Cipher Implementation

The project uses a **byte-level Caesar cipher** that:

- Operates on individual bytes (0-255 range)
- Supports any integer key value (normalized to 0-255 range)
- Maintains data integrity through proper modulo arithmetic
- Works with binary data, not just text

**Encryption Formula**: `encrypted_byte = (original_byte + key) % 256`

**Decryption Formula**: `decrypted_byte = (encrypted_byte - key + 256) % 256`

### Key Normalization

```c
// Keys are normalized to handle edge cases
int normalized_key = ((key % 256) + 256) % 256;
```

This ensures:
- Negative keys work correctly
- Large keys (>255) are reduced to valid range
- Consistent behavior across all platforms

## 🧪 Testing

The project includes comprehensive testing using the CMocka framework:

### Test Categories

- **Unit Tests**: Individual function testing
- **Integration Tests**: File operation testing
- **Edge Cases**: Empty files, large files, invalid inputs
- **File Format Tests**: Text, binary, image-like, video-like files
- **Error Handling**: Invalid parameters, missing files

### Running Tests

```bash
# Build and run all tests
cd build
ctest --verbose

# Run specific test executable
./tests/test_encryption
```

### Test Coverage

- ✅ Byte-level encryption/decryption
- ✅ Text file processing
- ✅ Binary file processing
- ✅ Image file structures (BMP, JPEG-like)
- ✅ Video file structures (MP4-like)
- ✅ Empty file handling
- ✅ Large file processing (10KB+)
- ✅ Error condition handling
- ✅ Memory management

## 🏗️ Build Configuration

### Build Types

| Type | Optimization | Debug Info | Use Case |
|------|-------------|------------|----------|
| `Debug` | None (`-O0`) | Full (`-g`) | Development |
| `Release` | Maximum (`-O3`) | None | Production |

```bash
# Debug build (default)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build (optimized)
cmake -DCMAKE_BUILD_TYPE=Release ..
```

### Compiler Requirements

- **C11 Standard**: Required for modern C features
- **Warning Flags**: `-Wall -Wextra` for code quality
- **Cross-Platform**: Works with GCC, Clang, MSVC

## 🤝 Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on:

- Code style and standards
- Git workflow and branching strategy
- Pull request process
- Testing requirements

## 📋 Project Scope

See [SCOPE.md](SCOPE.md) for detailed information about:

- What this project does and doesn't do
- Future enhancement possibilities
- Technical limitations and design decisions

## 📄 License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## 🏆 Project Goals

This project demonstrates "over-engineered" software development practices:

- ✅ **Professional Documentation**: Comprehensive README, scope definition, contribution guidelines
- ✅ **Agile Workflow**: GitHub Issues, feature branches, pull requests
- ✅ **Comprehensive Testing**: Unit tests, integration tests, edge cases
- ✅ **Modern Build System**: CMake with proper configuration
- ✅ **Code Quality**: Compiler warnings, consistent style, modular design
- ✅ **Git Best Practices**: Meaningful commits, proper branching, clean history

## 🚀 Getting Help

- **Issues**: Report bugs or request features via [GitHub Issues](https://github.com/antohaev100/A-Simple-File-Encryptor-Decryptor/issues)
- **Discussions**: Ask questions in [GitHub Discussions](https://github.com/antohaev100/A-Simple-File-Encryptor-Decryptor/discussions)
- **Documentation**: Check [SCOPE.md](SCOPE.md) and [CONTRIBUTING.md](CONTRIBUTING.md)

---

**Note**: This is an educational project demonstrating professional software development practices. While the Caesar cipher provides basic obfuscation, it should not be used for securing sensitive data in production environments.
