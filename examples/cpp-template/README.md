# MathUtils - C++ Template Project

A template C++ project demonstrating TDD + V-model development practices with full traceability.

## Features

- **CMake** build system with presets
- **CTest** for test execution
- **GitLab CI** pipeline with traceability checks
- **Requirements → Design → Tests** traceability
- Modern C++17 with best practices

## Project Structure

```
cpp-template/
├── CMakeLists.txt           # Root CMake configuration
├── CMakePresets.json        # CMake presets for build configurations
├── .gitlab-ci.yml           # GitLab CI pipeline
├── include/
│   └── mathutils/
│       ├── calculator.hpp   # Arithmetic operations
│       └── statistics.hpp   # Statistical operations
├── src/
│   ├── CMakeLists.txt
│   ├── calculator.cpp
│   └── statistics.cpp
├── tests/
│   ├── CMakeLists.txt
│   ├── test_calculator.cpp  # REQ-0001, REQ-0002, REQ-0003
│   └── test_statistics.cpp  # REQ-0004, REQ-0005
└── docs/
    ├── requirements/
    │   └── REQ-0001-math-operations.yaml
    └── design/
        └── DES-0001-mathutils-library.md
```

## Requirements Traceability

| REQ ID | Title | Design | Tests |
|--------|-------|--------|-------|
| REQ-0001 | Basic Arithmetic Operations | DES-0001 | test_calculator.cpp |
| REQ-0002 | Division by Zero Handling | DES-0001 | test_calculator.cpp |
| REQ-0003 | Absolute Value Operation | DES-0001 | test_calculator.cpp |
| REQ-0004 | Statistical Operations | DES-0001 | test_statistics.cpp |
| REQ-0005 | Empty Dataset Handling | DES-0001 | test_statistics.cpp |

## Quick Start

### Prerequisites
- CMake 3.20+
- C++17 compatible compiler (GCC 9+, Clang 10+, MSVC 2019+)

### Build and Test

```bash
# Using CMake presets (recommended)
cmake --workflow --preset dev

# Or step by step
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

### Available Presets

| Preset | Description |
|--------|-------------|
| `debug` | Debug build with tests |
| `release` | Optimized release build |
| `coverage` | Debug build with code coverage |
| `ci` | Configuration for CI pipeline |

### Workflow Presets

```bash
# Development workflow (configure + build + test)
cmake --workflow --preset dev

# CI workflow
cmake --workflow --preset ci
```

## TDD + V-Model Workflow

This project follows the TDD + V-model approach:

### 1. Requirements Phase
- Define requirements in `docs/requirements/*.yaml`
- Each requirement has a unique ID (REQ-xxxx)
- Requirements specify verification method

### 2. Design Phase
- Create design docs in `docs/design/*.md`
- Include "Traces to:" section with REQ references
- Document architecture, algorithms, failure modes

### 3. Implementation Phase (TDD)
1. **Red**: Write failing test with REQ-xxxx reference
2. **Green**: Implement minimal code to pass
3. **Refactor**: Improve code, keep tests green

### 4. Verification Phase
- Run tests: `ctest --preset debug`
- Check traceability in CI pipeline
- All REQ-xxxx must have design and test coverage

## CI Pipeline

The GitLab CI pipeline includes:

1. **Lint Stage**: clang-format, cppcheck
2. **Build Stage**: GCC and Clang builds
3. **Test Stage**: CTest execution
4. **Traceability Stage**: REQ↔DES↔TEST verification
5. **Package Stage**: Create release artifacts

### Traceability Check

The CI pipeline verifies:
- Every REQ-xxxx is referenced in design docs
- Every REQ-xxxx is referenced in test files
- No orphan references to undefined requirements

## Usage Example

```cpp
#include <mathutils/calculator.hpp>
#include <mathutils/statistics.hpp>
#include <iostream>

int main() {
    // Calculator operations
    double sum = mathutils::Calculator::add(2.0, 3.0);
    std::cout << "2 + 3 = " << sum << std::endl;
    
    // Statistics operations
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto mean = mathutils::Statistics::mean(data);
    if (mean) {
        std::cout << "Mean: " << *mean << std::endl;
    }
    
    return 0;
}
```

## Documentation

| Document | Description |
|----------|-------------|
| [Getting Started](docs/user/getting-started.md) | Quick start guide with examples |
| [API Reference](docs/api/reference.md) | Complete API documentation |
| [Troubleshooting](docs/user/troubleshooting.md) | Common issues and solutions |
| [Development Workflows](docs/WORKFLOWS.md) | How to add features, fix bugs, write docs |

## Agent Workflow Example

This project can be developed using the agent orchestration:

| Task | Agent | Output |
|------|-------|--------|
| New requirement | `requirements-author.md` | REQ-xxxx in YAML |
| Design | `design-author.md` | DES-xxxx document |
| Design review | `cdr-reviewer.md` | CDR approval |
| TDD | `tdd-coach.md` | Failing test → passing test |
| Code quality | `cpp-quality-enforcer.md` | Code review |
| Test generation | `test-generator.md` | Test cases |
| Test review | `test-reviewer.md` | Test quality check |
| Traceability | `traceability-manager.md` | Gap report |
| User docs | `doc-change-manager.md` | Updated docs |
| API docs | `cpp-quality-enforcer.md` | Doxygen comments |

See [docs/WORKFLOWS.md](docs/WORKFLOWS.md) for detailed workflows.
