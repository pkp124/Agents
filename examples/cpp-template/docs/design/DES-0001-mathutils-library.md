# Design: MathUtils Library

## Overview

MathUtils is a C++17 library providing basic arithmetic and statistical operations.
It emphasizes type safety, clear error handling, and modern C++ idioms.

## Goals / Non-goals

### Goals
- Provide reliable, tested mathematical operations
- Use modern C++17 features (optional, nodiscard, noexcept)
- Clear error handling with exceptions and optional types
- Easy integration via CMake

### Non-goals
- High-performance numerical computing (use Eigen, BLAS for that)
- Complex statistical analysis (use specialized libraries)
- Support for C++11/14 (requires C++17)

## Traces to

- Requirements: REQ-0001, REQ-0002, REQ-0003, REQ-0004, REQ-0005
- Use cases: (none defined)

## Architecture

```
┌─────────────────────────────────────────────────────┐
│                   MathUtils Library                  │
├─────────────────────────────────────────────────────┤
│                                                      │
│  ┌─────────────────┐      ┌─────────────────────┐  │
│  │   Calculator    │      │     Statistics      │  │
│  ├─────────────────┤      ├─────────────────────┤  │
│  │ + add()         │      │ + mean()            │  │
│  │ + subtract()    │      │ + sum()             │  │
│  │ + multiply()    │      │ + min()             │  │
│  │ + divide()      │      │ + max()             │  │
│  │ + abs()         │      │ + range()           │  │
│  └─────────────────┘      └─────────────────────┘  │
│                                                      │
└─────────────────────────────────────────────────────┘
```

### Components

1. **Calculator** (`calculator.hpp`, `calculator.cpp`)
   - Static class providing arithmetic operations
   - Satisfies: REQ-0001, REQ-0002, REQ-0003

2. **Statistics** (`statistics.hpp`, `statistics.cpp`)
   - Static class providing statistical operations
   - Satisfies: REQ-0004, REQ-0005

## Data Model / Invariants

### Type Choices
- All numeric values use `double` (IEEE 754 double precision)
- Collections use `std::vector<double>`
- Optional results use `std::optional<double>`

### Invariants
- Calculator operations are pure functions (no state)
- Statistics operations do not modify input data
- All operations are thread-safe (no shared state)

## Algorithms

### Calculator
- **add, subtract, multiply**: Direct arithmetic operators, O(1)
- **divide**: Checks for zero divisor, throws on zero, O(1)
- **abs**: Uses std::fabs, O(1)

### Statistics
- **sum**: std::accumulate, O(n)
- **mean**: sum / count, O(n)
- **min/max**: std::min_element / std::max_element, O(n)
- **range**: max - min, O(n) with two passes

### Complexity Summary
| Operation | Time | Space |
|-----------|------|-------|
| All Calculator ops | O(1) | O(1) |
| All Statistics ops | O(n) | O(1) |

## Failure Modes

| Failure | Handling | Requirement |
|---------|----------|-------------|
| Division by zero | Throw std::invalid_argument | REQ-0002 |
| Empty dataset (mean, min, max, range) | Return std::nullopt | REQ-0005 |
| Numeric overflow | Undefined (IEEE 754 behavior) | N/A |

## Security / Safety Considerations

- No dynamic memory allocation in Calculator
- Statistics uses only read-only access to input
- No external dependencies
- All inputs validated before use

## Test Strategy

### Unit Tests
- `test_calculator.cpp`: Tests all Calculator operations
  - Maps to: REQ-0001, REQ-0002, REQ-0003
  - Coverage: normal values, edge cases (zero, negative), boundary values

- `test_statistics.cpp`: Tests all Statistics operations
  - Maps to: REQ-0004, REQ-0005
  - Coverage: normal datasets, single element, empty datasets

### Test Execution
```bash
# Using CMake presets
cmake --workflow --preset dev

# Or manually
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

## Alternatives Considered

### Alternative 1: Template-based design
- **Approach**: Template all operations on numeric type
- **Rejected because**: Adds complexity, doubles not sufficient for this use case

### Alternative 2: Instance methods instead of static
- **Approach**: Create Calculator/Statistics instances
- **Rejected because**: No state needed, static methods are simpler

### Alternative 3: Return error codes instead of exceptions
- **Approach**: Return std::expected or error codes
- **Rejected because**: std::optional handles "no value" case, exceptions for errors is idiomatic C++

## Open Questions / Risks

1. **Floating-point precision**: Users must understand IEEE 754 limitations
2. **Large datasets**: No streaming interface for very large datasets
3. **NaN/Inf handling**: Currently undefined, may need explicit requirements
