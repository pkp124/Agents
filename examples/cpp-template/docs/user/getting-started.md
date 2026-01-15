# Getting Started with MathUtils

## Overview

MathUtils is a modern C++17 library providing reliable arithmetic and statistical operations. It emphasizes type safety, clear error handling, and testability.

**Traces to**: REQ-0001, REQ-0004

## Prerequisites

- **CMake**: 3.20 or later
- **Compiler**: C++17 compatible
  - GCC 9+
  - Clang 10+
  - MSVC 2019+

## Installation

### Option 1: CMake FetchContent (Recommended)

Add to your `CMakeLists.txt`:

```cmake
include(FetchContent)
FetchContent_Declare(
    mathutils
    GIT_REPOSITORY https://github.com/example/mathutils.git
    GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(mathutils)

target_link_libraries(your_target PRIVATE MathUtils::mathutils)
```

### Option 2: Build from Source

```bash
# Clone
git clone https://github.com/example/mathutils.git
cd mathutils

# Build
cmake --preset release
cmake --build --preset release

# Install
cmake --install build/release --prefix /usr/local
```

### Option 3: Header-Only (Copy Headers)

Copy `include/mathutils/` to your project and compile `src/*.cpp` with your code.

## Quick Start

### Calculator Operations

```cpp
#include <mathutils/calculator.hpp>
#include <iostream>

int main() {
    using mathutils::Calculator;
    
    // Basic arithmetic
    std::cout << "5 + 3 = " << Calculator::add(5.0, 3.0) << std::endl;
    std::cout << "5 - 3 = " << Calculator::subtract(5.0, 3.0) << std::endl;
    std::cout << "5 * 3 = " << Calculator::multiply(5.0, 3.0) << std::endl;
    std::cout << "5 / 3 = " << Calculator::divide(5.0, 3.0) << std::endl;
    
    // Absolute value
    std::cout << "|-7| = " << Calculator::abs(-7.0) << std::endl;
    
    return 0;
}
```

**Output**:
```
5 + 3 = 8
5 - 3 = 2
5 * 3 = 15
5 / 3 = 1.66667
|-7| = 7
```

### Statistics Operations

```cpp
#include <mathutils/statistics.hpp>
#include <iostream>
#include <vector>

int main() {
    using mathutils::Statistics;
    
    std::vector<double> data = {10.0, 20.0, 30.0, 40.0, 50.0};
    
    // Sum
    std::cout << "Sum: " << Statistics::sum(data) << std::endl;
    
    // Mean (returns optional)
    if (auto mean = Statistics::mean(data)) {
        std::cout << "Mean: " << *mean << std::endl;
    }
    
    // Min/Max (return optional)
    if (auto min = Statistics::min(data)) {
        std::cout << "Min: " << *min << std::endl;
    }
    if (auto max = Statistics::max(data)) {
        std::cout << "Max: " << *max << std::endl;
    }
    
    // Range
    if (auto range = Statistics::range(data)) {
        std::cout << "Range: " << *range << std::endl;
    }
    
    return 0;
}
```

**Output**:
```
Sum: 150
Mean: 30
Min: 10
Max: 50
Range: 40
```

## Error Handling

### Division by Zero

Division by zero throws `std::invalid_argument`:

```cpp
#include <mathutils/calculator.hpp>
#include <iostream>
#include <stdexcept>

int main() {
    try {
        double result = mathutils::Calculator::divide(10.0, 0.0);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
```

**Output**:
```
Error: Division by zero
```

**Traces to**: REQ-0002

### Empty Datasets

Statistical functions return `std::nullopt` for empty datasets:

```cpp
#include <mathutils/statistics.hpp>
#include <iostream>
#include <vector>

int main() {
    std::vector<double> empty_data;
    
    auto mean = mathutils::Statistics::mean(empty_data);
    
    if (mean.has_value()) {
        std::cout << "Mean: " << *mean << std::endl;
    } else {
        std::cout << "Cannot compute mean of empty dataset" << std::endl;
    }
    
    return 0;
}
```

**Output**:
```
Cannot compute mean of empty dataset
```

**Traces to**: REQ-0005

## Building Your Project

### CMakeLists.txt Example

```cmake
cmake_minimum_required(VERSION 3.20)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add MathUtils
include(FetchContent)
FetchContent_Declare(
    mathutils
    GIT_REPOSITORY https://github.com/example/mathutils.git
    GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(mathutils)

# Your application
add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE MathUtils::mathutils)
```

### Build Commands

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/myapp
```

## Next Steps

- [API Reference](../api/reference.md) - Complete API documentation
- [Examples](examples.md) - More detailed examples
- [Troubleshooting](troubleshooting.md) - Common issues and solutions

## Requirements Traceability

This document covers:
- REQ-0001: Basic Arithmetic Operations
- REQ-0002: Division by Zero Handling
- REQ-0003: Absolute Value Operation
- REQ-0004: Statistical Operations
- REQ-0005: Empty Dataset Handling
