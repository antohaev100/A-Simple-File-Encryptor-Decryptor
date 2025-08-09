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

# Optional testing - only if CMocka is available
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(CMOCKA cmocka)
    if(CMOCKA_FOUND)
        enable_testing()
        add_subdirectory(tests)
        message(STATUS "CMocka found - tests enabled")
    else()
        message(STATUS "CMocka not found - tests disabled")
    endif()
else()
    message(STATUS "pkg-config not found - tests disabled")
endif()

# Optional: Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)