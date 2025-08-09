# Find CMocka
find_package(PkgConfig REQUIRED)
pkg_check_modules(CMOCKA REQUIRED cmocka)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMOCKA_INCLUDE_DIRS})

# Library with core functions (without main.c)
add_library(FileEncryptorLib 
    ${CMAKE_SOURCE_DIR}/src/encryption.c
    ${CMAKE_SOURCE_DIR}/src/decryption.c
)

# Test executable
add_executable(test_encryption
    test_encryption.c
)

# Link libraries
target_link_libraries(test_encryption 
    FileEncryptorLib
    ${CMOCKA_LIBRARIES}
)

# Add compiler flags
target_compile_options(test_encryption PRIVATE ${CMOCKA_CFLAGS})

# Add test to CTest
add_test(NAME EncryptionTests COMMAND test_encryption)

# Set test properties
set_tests_properties(EncryptionTests PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)