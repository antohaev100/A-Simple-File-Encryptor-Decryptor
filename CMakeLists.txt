cmake_minimum_required(VERSION 3.10)
project(FileEncryptor VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")

# Include directories
include_directories(src)

# Source files
set(SOURCES
    src/main.c
    src/encryption.c
    src/decryption.c
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Enable testing
enable_testing()
add_subdirectory(tests)

# Optional: Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)