# Troubleshooting Guide

## Common Issues and Solutions

### Build Issues

#### Error: "CMake 3.20 or higher is required"

**Problem**: Your CMake version is too old.

**Solution**:
```bash
# Check current version
cmake --version

# Update CMake
# Ubuntu/Debian
sudo apt update && sudo apt install cmake

# macOS
brew upgrade cmake

# Or download from cmake.org
```

#### Error: "Could not find C++17 compiler"

**Problem**: Your compiler doesn't support C++17.

**Solution**:
- Update GCC to 9+ or Clang to 10+
- Or specify a different compiler:
```bash
cmake -B build -DCMAKE_CXX_COMPILER=/usr/bin/g++-11
```

#### Error: "mathutils/calculator.hpp: No such file"

**Problem**: Include paths not configured correctly.

**Solution**:
1. Ensure you're linking to the target:
   ```cmake
   target_link_libraries(your_app PRIVATE MathUtils::mathutils)
   ```
2. If building standalone, ensure include path:
   ```cmake
   target_include_directories(your_app PRIVATE /path/to/mathutils/include)
   ```

### Runtime Issues

#### Exception: "Division by zero"

**Problem**: Calling `Calculator::divide()` with zero divisor.

**Cause**: REQ-0002 specifies that division by zero throws an exception.

**Solution**:
```cpp
// Option 1: Check before dividing
if (divisor != 0.0) {
    result = Calculator::divide(dividend, divisor);
}

// Option 2: Catch the exception
try {
    result = Calculator::divide(dividend, divisor);
} catch (const std::invalid_argument& e) {
    // Handle the error
}
```

**Traces to**: REQ-0002

#### Statistics functions return empty optional

**Problem**: `mean()`, `min()`, `max()`, `range()` return `std::nullopt`.

**Cause**: REQ-0005 specifies empty datasets return nullopt.

**Solution**:
```cpp
// Always check before using the value
if (auto result = Statistics::mean(data)) {
    use_value(*result);
} else {
    handle_empty_dataset();
}

// Or with value_or for a default
double mean = Statistics::mean(data).value_or(0.0);
```

**Traces to**: REQ-0005

### Precision Issues

#### Floating-point comparison failures

**Problem**: Comparisons like `result == expected` fail unexpectedly.

**Cause**: IEEE 754 floating-point representation has limited precision.

**Solution**:
```cpp
// Instead of exact comparison
if (result == 0.333333) { ... }

// Use approximate comparison
bool approximately_equal(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}

if (approximately_equal(result, 0.333333)) { ... }
```

### Test Issues

#### Tests fail with "TEST_ASSERT" errors

**Problem**: Test assertions failing.

**Solution**:
1. Read the error message for expected vs actual values
2. Check your inputs match the test expectations
3. Verify the implementation matches the requirement

#### CTest reports "No tests found"

**Problem**: `ctest` doesn't find any tests.

**Solution**:
1. Ensure `BUILD_TESTS=ON`:
   ```bash
   cmake --preset debug  # Uses BUILD_TESTS=ON by default
   ```
2. Build the test targets:
   ```bash
   cmake --build --preset debug
   ```
3. Verify test executables exist:
   ```bash
   ls build/debug/tests/
   ```

### CI Pipeline Issues

#### Traceability check fails

**Problem**: CI reports missing requirement coverage.

**Cause**: A requirement lacks design or test references.

**Solution**:
1. Check which requirement is missing:
   ```bash
   # Show the gap
   grep -rhoP 'REQ-\d{4}' docs/requirements/ | sort -u > reqs.txt
   grep -rhoP 'REQ-\d{4}' docs/design/ | sort -u > design.txt
   grep -rhoP 'REQ-\d{4}' tests/ | sort -u > tests.txt
   
   comm -23 reqs.txt design.txt  # Missing from design
   comm -23 reqs.txt tests.txt   # Missing from tests
   ```

2. Add the missing references:
   - Design: Add to "Traces to:" section
   - Tests: Add REQ-xxxx in comments

**Traces to**: Traceability requirements

## Getting Help

1. Check the [API Reference](../api/reference.md)
2. Review the [Examples](examples.md)
3. Open an issue on GitHub
4. Check existing issues for similar problems

## Diagnostic Commands

```bash
# Check CMake configuration
cmake --preset debug --fresh

# Verbose build
cmake --build --preset debug --verbose

# Run tests with output
ctest --preset debug --output-on-failure

# Check traceability
./scripts/check-traceability.sh
```
