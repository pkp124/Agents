# Development Workflows

This guide documents how to perform common development tasks following TDD + V-model practices with agent orchestration.

## Table of Contents

1. [Adding a New Feature](#adding-a-new-feature)
2. [Adding a New Test](#adding-a-new-test)
3. [Fixing a Bug](#fixing-a-bug)
4. [Writing User Documentation](#writing-user-documentation)
5. [Writing API Documentation](#writing-api-documentation)
6. [Refactoring Code](#refactoring-code)
7. [Conducting Reviews](#conducting-reviews)

---

## Adding a New Feature

### Overview
New features follow the complete V-model: Requirements → Design → Implementation (TDD) → Verification.

### Step-by-Step Workflow

#### Step 1: Create Requirement
**Agent**: `requirements-author.md`

1. Determine the next requirement ID:
   ```bash
   # Find highest existing REQ ID
   grep -rhoP 'REQ-\d{4}' docs/requirements/ | sort -u | tail -1
   ```

2. Add requirement to `docs/requirements/REQ-0001-math-operations.yaml`:
   ```yaml
   - id: "REQ-0006"
     title: "Median Calculation"
     statement: "The system shall calculate the median value of a numeric dataset, returning the middle value when sorted."
     rationale: "Median is a common statistical measure needed for data analysis."
     verification_method: "Test"
     priority: "Should"
     derived_from: ["REQ-0004"]
     depends_on: ["REQ-0005"]
     notes: "For even-sized datasets, return average of two middle values."
   ```

3. Review with `requirements-reviewer.md`:
   - Is it verifiable?
   - Is it unambiguous?
   - Is it atomic?

#### Step 2: Update Design Document
**Agent**: `design-author.md`

1. Edit `docs/design/DES-0001-mathutils-library.md`:

   ```markdown
   ## Traces to
   - Requirements: REQ-0001, REQ-0002, REQ-0003, REQ-0004, REQ-0005, REQ-0006
   ```

2. Add design details:
   ```markdown
   ### Median Algorithm
   - **Approach**: Copy, sort, select middle element(s)
   - **Complexity**: O(n log n) due to sorting
   - **Edge cases**: Empty dataset returns nullopt, single element returns that element
   - **Even-sized datasets**: Average of two middle values
   ```

3. Review with `cdr-reviewer.md` for significant features.

#### Step 3: Write Failing Test (TDD Red Phase)
**Agent**: `tdd-coach.md`

1. Add test to `tests/test_statistics.cpp`:
   ```cpp
   /**
    * Test median calculation
    * REQ-0006: The system shall calculate the median value
    */
   int test_median() {
       // Odd number of elements
       std::vector<double> odd = {3.0, 1.0, 4.0, 1.0, 5.0};
       auto result_odd = Statistics::median(odd);
       TEST_ASSERT(result_odd.has_value(), "median should return value");
       TEST_ASSERT_NEAR(*result_odd, 3.0, 1e-9, "median of {3,1,4,1,5} = 3");
       
       // Even number of elements
       std::vector<double> even = {1.0, 2.0, 3.0, 4.0};
       auto result_even = Statistics::median(even);
       TEST_ASSERT(result_even.has_value(), "median should return value");
       TEST_ASSERT_NEAR(*result_even, 2.5, 1e-9, "median of {1,2,3,4} = 2.5");
       
       // Single element
       std::vector<double> single = {42.0};
       auto result_single = Statistics::median(single);
       TEST_ASSERT_NEAR(*result_single, 42.0, 1e-9, "median of {42} = 42");
       
       // Empty dataset - REQ-0005
       std::vector<double> empty;
       TEST_ASSERT(!Statistics::median(empty).has_value(), "median of empty = nullopt");
       
       std::cout << "test_median: PASSED" << std::endl;
       return 0;
   }
   ```

2. Add to main():
   ```cpp
   result += test_median();
   ```

3. Build and verify test fails:
   ```bash
   cmake --build --preset debug
   ctest --preset debug  # Should fail - median not implemented
   ```

#### Step 4: Implement Feature (TDD Green Phase)
**Agent**: `cpp-quality-enforcer.md`

1. Add declaration to `include/mathutils/statistics.hpp`:
   ```cpp
   /**
    * @brief Calculate the median of a dataset
    * @param data Vector of numeric values
    * @return Median value, or std::nullopt if data is empty
    * 
    * REQ-0006: Median calculation
    * REQ-0005: Empty dataset shall return nullopt
    */
   [[nodiscard]] static std::optional<double> median(const std::vector<double>& data);
   ```

2. Add implementation to `src/statistics.cpp`:
   ```cpp
   std::optional<double> Statistics::median(const std::vector<double>& data) {
       // REQ-0005: Empty dataset shall return nullopt
       if (data.empty()) {
           return std::nullopt;
       }
       
       // REQ-0006: Calculate median
       std::vector<double> sorted = data;
       std::sort(sorted.begin(), sorted.end());
       
       size_t n = sorted.size();
       size_t mid = n / 2;
       
       if (n % 2 == 0) {
           // Even: average of two middle values
           return (sorted[mid - 1] + sorted[mid]) / 2.0;
       } else {
           // Odd: middle value
           return sorted[mid];
       }
   }
   ```

3. Build and run tests:
   ```bash
   cmake --build --preset debug
   ctest --preset debug  # Should pass now
   ```

#### Step 5: Refactor (TDD Refactor Phase)
**Agent**: `cpp-quality-enforcer.md`

1. Review code for improvements
2. Ensure tests still pass after each change
3. Consider extracting helper functions if needed

#### Step 6: Verify Traceability
**Agent**: `traceability-manager.md`

```bash
# Check all requirements have coverage
grep -rhoP 'REQ-\d{4}' docs/requirements/ | sort -u > /tmp/reqs.txt
grep -rhoP 'REQ-\d{4}' docs/design/ | sort -u > /tmp/design.txt
grep -rhoP 'REQ-\d{4}' tests/ | sort -u > /tmp/tests.txt

# Verify REQ-0006 appears in all
grep "REQ-0006" /tmp/reqs.txt /tmp/design.txt /tmp/tests.txt
```

#### Step 7: Update Documentation
**Agent**: `doc-change-manager.md`

1. Update README.md with new feature
2. Update API documentation
3. Add usage examples

---

## Adding a New Test

### Overview
Tests can be added for various reasons: new requirement coverage, edge cases, regression tests, or improved coverage.

### Workflow

#### Step 1: Identify What to Test
**Agent**: `test-coverage-analyst.md`

Determine the reason for the test:
- [ ] New requirement coverage (REQ-xxxx)
- [ ] Missing edge case
- [ ] Bug regression test
- [ ] Increased coverage for existing requirement

#### Step 2: Determine Requirement Link
Every test must reference at least one REQ-xxxx.

```bash
# Find relevant requirement
grep -r "keyword" docs/requirements/
```

#### Step 3: Write the Test
**Agent**: `test-generator.md`

1. Choose the appropriate test file or create new one
2. Follow the test structure:

```cpp
/**
 * Test description
 * REQ-xxxx: Requirement being verified
 * 
 * Given: [preconditions]
 * When: [action]
 * Then: [expected result]
 */
int test_descriptive_name() {
    // Arrange
    // ... setup
    
    // Act
    auto result = function_under_test(input);
    
    // Assert
    TEST_ASSERT(condition, "failure message");
    
    std::cout << "test_descriptive_name: PASSED" << std::endl;
    return 0;
}
```

3. Add to test main():
```cpp
result += test_descriptive_name();
```

#### Step 4: Run and Verify
```bash
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

#### Step 5: Review Test Quality
**Agent**: `test-reviewer.md`

Checklist:
- [ ] Test is deterministic (no random, no timing dependencies)
- [ ] Test has clear assertion messages
- [ ] Test covers one specific behavior
- [ ] Test references REQ-xxxx
- [ ] Test name describes the scenario

### Example: Adding Edge Case Test

```cpp
/**
 * Test division with very small divisor
 * REQ-0001: Basic arithmetic operations
 * REQ-0002: Division edge cases
 * 
 * Given: A normal dividend and very small divisor
 * When: Division is performed
 * Then: Result should be large but valid
 */
int test_divide_small_divisor() {
    double result = Calculator::divide(1.0, 1e-10);
    TEST_ASSERT(std::isfinite(result), "Result should be finite");
    TEST_ASSERT(result > 1e9, "Result should be very large");
    
    std::cout << "test_divide_small_divisor: PASSED" << std::endl;
    return 0;
}
```

---

## Fixing a Bug

### Overview
Bug fixes follow TDD: write a failing test that reproduces the bug, fix it, verify all tests pass.

### Workflow

#### Step 1: Identify Affected Requirement
**Agent**: `traceability-manager.md`

```bash
# Find requirements related to the buggy behavior
grep -r "keyword" docs/requirements/
```

Document:
- Bug description
- Affected REQ-xxxx
- Steps to reproduce

#### Step 2: Write Failing Test (Regression Test)
**Agent**: `tdd-coach.md`

```cpp
/**
 * Regression test for Issue #123: Division precision loss
 * REQ-0001: Basic arithmetic operations
 * 
 * Bug: Division of 1.0 by 3.0 was returning 0 due to integer truncation
 * Fix: Ensure floating-point division is used
 */
int test_bug_123_division_precision() {
    // This test should fail before the fix
    double result = Calculator::divide(1.0, 3.0);
    
    // Should be approximately 0.333..., not 0
    TEST_ASSERT(result > 0.3, "Division should not truncate to 0");
    TEST_ASSERT_NEAR(result, 0.333333, 1e-5, "1/3 ≈ 0.333");
    
    std::cout << "test_bug_123_division_precision: PASSED" << std::endl;
    return 0;
}
```

#### Step 3: Verify Test Fails
```bash
cmake --build --preset debug
ctest --preset debug  # Should fail, confirming the bug
```

#### Step 4: Implement Fix
Make the minimal change needed to fix the bug.

```cpp
// Before (buggy)
double Calculator::divide(double a, double b) {
    return (int)a / (int)b;  // Bug: integer division
}

// After (fixed)
double Calculator::divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;  // Correct: floating-point division
}
```

#### Step 5: Verify All Tests Pass
```bash
ctest --preset debug  # All tests should pass, including the new one
```

#### Step 6: Perform Impact Analysis
**Agent**: `traceability-manager.md`

Check if the fix affects other areas:
```bash
# Find all code using the fixed function
grep -rn "divide" src/ tests/ include/
```

#### Step 7: Update Documentation if Needed
If the bug revealed unclear documentation, update it.

### Bug Fix Checklist
- [ ] Bug reproduced with failing test
- [ ] Test references affected REQ-xxxx
- [ ] Fix is minimal and focused
- [ ] All existing tests still pass
- [ ] New regression test passes
- [ ] Impact analysis completed
- [ ] Documentation updated if needed

---

## Writing User Documentation

### Overview
User documentation explains how to use the library from an end-user perspective.

### Workflow

#### Step 1: Identify Documentation Need
**Agent**: `doc-change-manager.md`

Types of user documentation:
- Getting Started / Quick Start
- Installation Guide
- Usage Examples
- Tutorial / How-to Guides
- Troubleshooting

#### Step 2: Create Documentation Structure
Create `docs/user/` directory:

```
docs/user/
├── getting-started.md
├── installation.md
├── examples/
│   ├── calculator-example.md
│   └── statistics-example.md
└── troubleshooting.md
```

#### Step 3: Write Documentation
**Agent**: `user-doc-reviewer.md` (for review)

##### Getting Started Example (`docs/user/getting-started.md`):

```markdown
# Getting Started with MathUtils

## Overview
MathUtils is a C++17 library providing arithmetic and statistical operations.

## Prerequisites
- CMake 3.20 or later
- C++17 compatible compiler

## Quick Installation

### Using CMake FetchContent
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

### Building from Source
```bash
git clone https://github.com/example/mathutils.git
cd mathutils
cmake --preset release
cmake --build --preset release
cmake --install build/release --prefix /usr/local
```

## Basic Usage

### Calculator Operations
```cpp
#include <mathutils/calculator.hpp>
#include <iostream>

int main() {
    using namespace mathutils;
    
    std::cout << "2 + 3 = " << Calculator::add(2.0, 3.0) << std::endl;
    std::cout << "10 / 4 = " << Calculator::divide(10.0, 4.0) << std::endl;
    std::cout << "|-5| = " << Calculator::abs(-5.0) << std::endl;
    
    return 0;
}
```

### Statistics Operations
```cpp
#include <mathutils/statistics.hpp>
#include <iostream>
#include <vector>

int main() {
    using namespace mathutils;
    
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    if (auto mean = Statistics::mean(data)) {
        std::cout << "Mean: " << *mean << std::endl;
    }
    
    std::cout << "Sum: " << Statistics::sum(data) << std::endl;
    
    if (auto range = Statistics::range(data)) {
        std::cout << "Range: " << *range << std::endl;
    }
    
    return 0;
}
```

## Error Handling

### Division by Zero
```cpp
try {
    double result = Calculator::divide(10.0, 0.0);
} catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

### Empty Datasets
Statistics functions return `std::nullopt` for empty datasets:
```cpp
std::vector<double> empty;
auto result = Statistics::mean(empty);
if (!result) {
    std::cout << "Cannot compute mean of empty dataset" << std::endl;
}
```

## Next Steps
- See [Examples](examples/) for more detailed use cases
- See [API Reference](../api/) for complete API documentation
- See [Troubleshooting](troubleshooting.md) for common issues
```

#### Step 4: Review Documentation
**Agent**: `user-doc-reviewer.md`

Checklist:
- [ ] Code examples compile and run
- [ ] Steps are clear and actionable
- [ ] Error cases are documented
- [ ] Terminology is defined
- [ ] Links work correctly

#### Step 5: Link to Requirements
Add traceability:
```markdown
---
Traces to: REQ-0001, REQ-0002, REQ-0004, REQ-0005
---
```

---

## Writing API Documentation

### Overview
API documentation describes the technical interface for developers integrating the library.

### Workflow

#### Step 1: Use Doxygen-Style Comments
**Agent**: `cpp-quality-enforcer.md`

Already in the code:
```cpp
/**
 * @brief Add two numbers
 * @param a First operand
 * @param b Second operand
 * @return Sum of a and b
 * 
 * @code
 * double sum = Calculator::add(2.0, 3.0);  // Returns 5.0
 * @endcode
 * 
 * REQ-0001: Addition operation
 */
[[nodiscard]] static double add(double a, double b) noexcept;
```

#### Step 2: Create Doxyfile (Optional)
For generated documentation:

```bash
# Create Doxyfile
doxygen -g

# Configure key settings:
PROJECT_NAME = "MathUtils"
OUTPUT_DIRECTORY = docs/api
INPUT = include src
RECURSIVE = YES
GENERATE_HTML = YES
GENERATE_LATEX = NO
EXTRACT_ALL = YES
```

#### Step 3: Create Manual API Reference
Create `docs/api/reference.md`:

```markdown
# API Reference

## Calculator Class

Namespace: `mathutils`
Header: `<mathutils/calculator.hpp>`

### Static Methods

#### `add(a, b) → double`
Add two numbers.

| Parameter | Type | Description |
|-----------|------|-------------|
| `a` | `double` | First operand |
| `b` | `double` | Second operand |
| **Returns** | `double` | Sum of a and b |

**Guarantees**: `noexcept`

**Example**:
```cpp
double sum = mathutils::Calculator::add(2.0, 3.0);  // 5.0
```

**Traces to**: REQ-0001

---

#### `subtract(a, b) → double`
Subtract b from a.

| Parameter | Type | Description |
|-----------|------|-------------|
| `a` | `double` | Minuend |
| `b` | `double` | Subtrahend |
| **Returns** | `double` | Difference (a - b) |

**Guarantees**: `noexcept`

**Traces to**: REQ-0001

---

#### `divide(a, b) → double`
Divide a by b.

| Parameter | Type | Description |
|-----------|------|-------------|
| `a` | `double` | Dividend |
| `b` | `double` | Divisor |
| **Returns** | `double` | Quotient (a / b) |
| **Throws** | `std::invalid_argument` | If b is zero |

**Example**:
```cpp
try {
    double result = mathutils::Calculator::divide(10.0, 2.0);  // 5.0
} catch (const std::invalid_argument& e) {
    // Handle division by zero
}
```

**Traces to**: REQ-0001, REQ-0002

---

## Statistics Class

Namespace: `mathutils`
Header: `<mathutils/statistics.hpp>`

### Static Methods

#### `mean(data) → std::optional<double>`
Calculate the arithmetic mean.

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const std::vector<double>&` | Input dataset |
| **Returns** | `std::optional<double>` | Mean value, or `nullopt` if empty |

**Example**:
```cpp
std::vector<double> data = {1.0, 2.0, 3.0};
if (auto m = mathutils::Statistics::mean(data)) {
    std::cout << "Mean: " << *m << std::endl;  // 2.0
}
```

**Traces to**: REQ-0004, REQ-0005

---

#### `sum(data) → double`
Calculate the sum of all elements.

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const std::vector<double>&` | Input dataset |
| **Returns** | `double` | Sum (0.0 if empty) |

**Guarantees**: `noexcept`

**Traces to**: REQ-0004

---

## Error Handling Summary

| Function | Error Condition | Behavior |
|----------|-----------------|----------|
| `Calculator::divide` | Divisor is zero | Throws `std::invalid_argument` |
| `Statistics::mean` | Empty dataset | Returns `std::nullopt` |
| `Statistics::min` | Empty dataset | Returns `std::nullopt` |
| `Statistics::max` | Empty dataset | Returns `std::nullopt` |
| `Statistics::range` | Empty dataset | Returns `std::nullopt` |

## Thread Safety

All methods in `Calculator` and `Statistics` are thread-safe:
- No shared mutable state
- Input data is accessed read-only
- Pure functions with no side effects
```

#### Step 4: Add to Build (Optional)
Add Doxygen to CMake:

```cmake
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/api)
    doxygen_add_docs(docs include src)
endif()
```

---

## Refactoring Code

### Overview
Refactoring improves code structure without changing behavior. Tests must pass before, during, and after.

### Workflow

#### Step 1: Ensure Test Coverage
**Agent**: `test-coverage-analyst.md`

```bash
# Verify tests exist for code being refactored
ctest --preset debug
```

#### Step 2: Add Tests for Uncovered Code
**Agent**: `test-generator.md`

If coverage gaps exist, add tests before refactoring.

#### Step 3: Refactor in Small Steps
**Agent**: `cpp-quality-enforcer.md`

For each refactoring step:
1. Make one small change
2. Build: `cmake --build --preset debug`
3. Test: `ctest --preset debug`
4. If tests pass, commit
5. If tests fail, revert

#### Step 4: Common Refactorings

##### Extract Function
```cpp
// Before
double Statistics::range(const std::vector<double>& data) {
    if (data.empty()) return std::nullopt;
    auto min_val = *std::min_element(data.begin(), data.end());
    auto max_val = *std::max_element(data.begin(), data.end());
    return max_val - min_val;
}

// After
double Statistics::range(const std::vector<double>& data) {
    auto min_val = min(data);
    auto max_val = max(data);
    if (!min_val || !max_val) return std::nullopt;
    return *max_val - *min_val;
}
```

##### Rename
Use IDE refactoring tools to rename consistently.

##### Simplify Conditionals
```cpp
// Before
if (data.size() == 0) {
    return std::nullopt;
}

// After
if (data.empty()) {
    return std::nullopt;
}
```

---

## Conducting Reviews

### Overview
Reviews ensure quality at each development phase.

### Types of Reviews

#### Requirements Review
**Agent**: `requirements-reviewer.md`

Checklist:
- [ ] Verifiable with test or other method
- [ ] Unambiguous - single interpretation
- [ ] Complete - covers all cases
- [ ] Consistent - no contradictions
- [ ] Atomic - one idea per requirement
- [ ] Prioritized - Must/Should/Could

#### Design Review (CDR)
**Agent**: `cdr-reviewer.md` + `senior-architect.md`

Checklist:
- [ ] Traces to requirements
- [ ] Clear interfaces
- [ ] Failure modes documented
- [ ] Test strategy defined
- [ ] Alternatives considered

#### Code Review
**Agent**: `cpp-quality-enforcer.md`

Checklist:
- [ ] Follows coding standards
- [ ] REQ-xxxx references in comments
- [ ] Error handling complete
- [ ] No obvious bugs
- [ ] Tests included

#### Test Review
**Agent**: `test-reviewer.md`

Checklist:
- [ ] Deterministic
- [ ] References REQ-xxxx
- [ ] Covers behavior, not implementation
- [ ] Clear assertions
- [ ] Edge cases included

### Review Process
**Agent**: `review-coordinator.md`

1. Author prepares artifacts
2. Author self-reviews
3. Request review with scope
4. Reviewer uses appropriate agent
5. Findings documented
6. Author addresses findings
7. Final approval

---

## Quick Reference

| Task | Agents | Key Steps |
|------|--------|-----------|
| New Feature | `requirements-author` → `design-author` → `tdd-coach` → `cpp-quality-enforcer` | REQ → DES → Test → Code |
| New Test | `test-generator` → `test-reviewer` | Identify REQ → Write test → Review |
| Bug Fix | `tdd-coach` → `traceability-manager` | Failing test → Fix → Verify |
| User Docs | `doc-change-manager` → `user-doc-reviewer` | Structure → Write → Review |
| API Docs | `cpp-quality-enforcer` | Doxygen comments → Generate |
| Refactor | `test-coverage-analyst` → `cpp-quality-enforcer` | Coverage → Small steps → Test |
| Review | `review-coordinator` → specific reviewer | Plan → Execute → Approve |
