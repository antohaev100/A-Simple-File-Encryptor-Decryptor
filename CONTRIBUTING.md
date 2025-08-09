# Contributing to File Encryptor/Decryptor

Thank you for your interest in contributing to this educational project! This document provides essential guidelines for contributors.

## 📋 Table of Contents

- [Getting Started](#getting-started)
- [Development Workflow](#development-workflow)
- [Basic Code Guidelines](#basic-code-guidelines)
- [Testing Requirements](#testing-requirements)
- [Pull Request Process](#pull-request-process)
- [Issue Reporting](#issue-reporting)

## 🚀 Getting Started

### Prerequisites

- **C Compiler**: GCC 15.1.0 or compatible (C11 support required)
- **CMake**: Version 3.10 or higher
- **CMocka**: For running tests
- **Git**: For version control

### Setup Development Environment

```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/A-Simple-File-Encryptor-Decryptor.git
cd A-Simple-File-Encryptor-Decryptor

# Build and test
mkdir build && cd build
cmake ..
cmake --build .
ctest --verbose
```

## 🔄 Development Workflow

This project follows an **agile, issue-driven workflow**:

## Issue-First Development
- Start with a GitHub issue describing the work
- Create a feature branch: `feature/issue-number-description`
- Implement, test, and create a pull request

## 📝 Basic Code Guidelines

**Key principles:**
- Use clear, descriptive function and variable names
- Comment complex algorithms and edge cases
- Follow the existing code style in the project
- Keep functions focused and reasonably sized

## 🧪 Testing Requirements

- **New functions** should have basic unit tests
- **Test edge cases** like empty files and invalid inputs
- **Verify file integrity** for encryption/decryption cycles

Example test structure:
```c
static void test_encrypt_decrypt_cycle(void **state) {
    (void)state;
    
    // Create test data
    // Encrypt and decrypt
    // Verify integrity
    
    assert_memory_equal(original, decrypted, size);
}
```

## 🔀 Pull Request Process

### Before Creating PR:
- [ ] Tests pass locally: `ctest --verbose`
- [ ] Code builds without warnings
- [ ] Manual testing completed
- [ ] Documentation updated if needed

### PR Description Template:
```markdown
## Summary
Brief description of changes.

## Changes Made
- [ ] Feature/fix implemented
- [ ] Tests added
- [ ] Documentation updated

## Testing
How the changes were tested.

Closes #issue-number
```

## 🐛 Issue Reporting

### Bug Reports
```markdown
**Bug Description**: What's wrong?

**Steps to Reproduce**: How to trigger the bug?

**Expected vs Actual**: What should happen vs what happens?

**Environment**: OS, compiler version, file type
```

### Feature Requests
```markdown
**Feature Description**: What should be added?

**Use Case**: Why is this useful?

**Implementation Ideas**: Any thoughts on how to implement?
```

## 📝 Commit Messages

Use clear, descriptive commit messages:

```bash
# Good examples:
git commit -m "feat: add XOR encryption algorithm"
git commit -m "fix: handle empty files correctly"
git commit -m "test: add edge case coverage for large files"
git commit -m "docs: update README with new features"

# Include issue reference:
git commit -m "feat: add batch processing

Implement batch mode for processing multiple files
with single command and shared encryption key.

Closes #25"
```

## 🔄 Keeping Updated

```bash
# Update your fork
git checkout main
git pull upstream main
git push origin main
```

---

This is an educational project focused on learning C programming, CMake, testing, and Git workflows. Contributions should maintain the project's educational value while demonstrating good software development practices.

**Questions?** Create a GitHub issue or check the existing documentation.
