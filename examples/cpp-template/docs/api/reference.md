# API Reference

## Overview

MathUtils provides two main classes:
- `Calculator` - Basic arithmetic operations
- `Statistics` - Statistical operations on datasets

All classes are in the `mathutils` namespace.

---

## Calculator Class

**Header**: `<mathutils/calculator.hpp>`
**Namespace**: `mathutils`

Provides static methods for basic arithmetic operations.

### Methods

---

#### `add`

```cpp
[[nodiscard]] static double add(double a, double b) noexcept;
```

Adds two numbers.

| Parameter | Type | Description |
|-----------|------|-------------|
| `a` | `double` | First operand |
| `b` | `double` | Second operand |
| **Returns** | `double` | Sum (a + b) |

**Guarantees**: `noexcept` - never throws

**Example**:
```cpp
double sum = mathutils::Calculator::add(2.5, 3.5);  // Returns 6.0
```

**Traces to**: REQ-0001

---

#### `subtract`

```cpp
[[nodiscard]] static double subtract(double a, double b) noexcept;
```

Subtracts b from a.

| Parameter | Type | Description |
|-----------|------|-------------|
| `a` | `double` | Minuend |
| `b` | `double` | Subtrahend |
| **Returns** | `double` | Difference (a - b) |

**Guarantees**: `noexcept` - never throws

**Example**:
```cpp
double diff = mathutils::Calculator::subtract(10.0, 4.0);  // Returns 6.0
```

**Traces to**: REQ-0001

---

#### `multiply`

```cpp
[[nodiscard]] static double multiply(double a, double b) noexcept;
```

Multiplies two numbers.

| Parameter | Type | Description |
|-----------|------|-------------|
| `a` | `double` | First factor |
| `b` | `double` | Second factor |
| **Returns** | `double` | Product (a × b) |

**Guarantees**: `noexcept` - never throws

**Example**:
```cpp
double product = mathutils::Calculator::multiply(3.0, 4.0);  // Returns 12.0
```

**Traces to**: REQ-0001

---

#### `divide`

```cpp
[[nodiscard]] static double divide(double a, double b);
```

Divides a by b.

| Parameter | Type | Description |
|-----------|------|-------------|
| `a` | `double` | Dividend |
| `b` | `double` | Divisor |
| **Returns** | `double` | Quotient (a / b) |
| **Throws** | `std::invalid_argument` | If `b == 0.0` |

**Example**:
```cpp
try {
    double quotient = mathutils::Calculator::divide(10.0, 4.0);  // Returns 2.5
} catch (const std::invalid_argument& e) {
    std::cerr << "Division by zero: " << e.what() << std::endl;
}
```

**Traces to**: REQ-0001, REQ-0002

---

#### `abs`

```cpp
[[nodiscard]] static double abs(double value) noexcept;
```

Computes the absolute value.

| Parameter | Type | Description |
|-----------|------|-------------|
| `value` | `double` | Input value |
| **Returns** | `double` | Absolute value (\|value\|) |

**Guarantees**: `noexcept` - never throws

**Example**:
```cpp
double absolute = mathutils::Calculator::abs(-7.5);  // Returns 7.5
```

**Traces to**: REQ-0003

---

## Statistics Class

**Header**: `<mathutils/statistics.hpp>`
**Namespace**: `mathutils`

Provides static methods for statistical operations on numeric datasets.

### Methods

---

#### `mean`

```cpp
[[nodiscard]] static std::optional<double> mean(const std::vector<double>& data);
```

Calculates the arithmetic mean (average).

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const std::vector<double>&` | Input dataset |
| **Returns** | `std::optional<double>` | Mean value, or `std::nullopt` if empty |

**Example**:
```cpp
std::vector<double> values = {1.0, 2.0, 3.0, 4.0, 5.0};
if (auto m = mathutils::Statistics::mean(values)) {
    std::cout << "Mean: " << *m << std::endl;  // Mean: 3
}

std::vector<double> empty;
auto result = mathutils::Statistics::mean(empty);  // Returns std::nullopt
```

**Complexity**: O(n)

**Traces to**: REQ-0004, REQ-0005

---

#### `sum`

```cpp
[[nodiscard]] static double sum(const std::vector<double>& data) noexcept;
```

Calculates the sum of all elements.

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const std::vector<double>&` | Input dataset |
| **Returns** | `double` | Sum of all elements (0.0 if empty) |

**Guarantees**: `noexcept` - never throws

**Example**:
```cpp
std::vector<double> values = {1.0, 2.0, 3.0};
double total = mathutils::Statistics::sum(values);  // Returns 6.0

std::vector<double> empty;
double zero = mathutils::Statistics::sum(empty);  // Returns 0.0
```

**Complexity**: O(n)

**Traces to**: REQ-0004

---

#### `min`

```cpp
[[nodiscard]] static std::optional<double> min(const std::vector<double>& data);
```

Finds the minimum value.

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const std::vector<double>&` | Input dataset |
| **Returns** | `std::optional<double>` | Minimum value, or `std::nullopt` if empty |

**Example**:
```cpp
std::vector<double> values = {3.0, 1.0, 4.0, 1.0, 5.0};
if (auto minimum = mathutils::Statistics::min(values)) {
    std::cout << "Min: " << *minimum << std::endl;  // Min: 1
}
```

**Complexity**: O(n)

**Traces to**: REQ-0004, REQ-0005

---

#### `max`

```cpp
[[nodiscard]] static std::optional<double> max(const std::vector<double>& data);
```

Finds the maximum value.

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const std::vector<double>&` | Input dataset |
| **Returns** | `std::optional<double>` | Maximum value, or `std::nullopt` if empty |

**Example**:
```cpp
std::vector<double> values = {3.0, 1.0, 4.0, 1.0, 5.0};
if (auto maximum = mathutils::Statistics::max(values)) {
    std::cout << "Max: " << *maximum << std::endl;  // Max: 5
}
```

**Complexity**: O(n)

**Traces to**: REQ-0004, REQ-0005

---

#### `range`

```cpp
[[nodiscard]] static std::optional<double> range(const std::vector<double>& data);
```

Calculates the range (max - min).

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const std::vector<double>&` | Input dataset |
| **Returns** | `std::optional<double>` | Range value, or `std::nullopt` if empty |

**Example**:
```cpp
std::vector<double> values = {3.0, 1.0, 4.0, 1.0, 5.0};
if (auto r = mathutils::Statistics::range(values)) {
    std::cout << "Range: " << *r << std::endl;  // Range: 4 (5-1)
}
```

**Complexity**: O(n)

**Traces to**: REQ-0004, REQ-0005

---

## Error Handling Summary

| Function | Error Condition | Behavior |
|----------|-----------------|----------|
| `Calculator::divide` | `b == 0.0` | Throws `std::invalid_argument("Division by zero")` |
| `Statistics::mean` | Empty vector | Returns `std::nullopt` |
| `Statistics::min` | Empty vector | Returns `std::nullopt` |
| `Statistics::max` | Empty vector | Returns `std::nullopt` |
| `Statistics::range` | Empty vector | Returns `std::nullopt` |
| `Statistics::sum` | Empty vector | Returns `0.0` |

---

## Thread Safety

All methods are thread-safe:
- No shared mutable state
- Input containers accessed read-only
- Pure functions with no side effects

Multiple threads can safely call any method concurrently.

---

## Exception Safety

| Function | Exception Guarantee |
|----------|---------------------|
| All `Calculator` methods except `divide` | `noexcept` (no-throw) |
| `Calculator::divide` | Basic guarantee (may throw `std::invalid_argument`) |
| `Statistics::sum` | `noexcept` (no-throw) |
| Other `Statistics` methods | Basic guarantee (allocations may throw) |

---

## Complexity Summary

| Function | Time Complexity | Space Complexity |
|----------|-----------------|------------------|
| `Calculator::add` | O(1) | O(1) |
| `Calculator::subtract` | O(1) | O(1) |
| `Calculator::multiply` | O(1) | O(1) |
| `Calculator::divide` | O(1) | O(1) |
| `Calculator::abs` | O(1) | O(1) |
| `Statistics::sum` | O(n) | O(1) |
| `Statistics::mean` | O(n) | O(1) |
| `Statistics::min` | O(n) | O(1) |
| `Statistics::max` | O(n) | O(1) |
| `Statistics::range` | O(n) | O(1) |

---

## Requirements Traceability

| Requirement | Functions |
|-------------|-----------|
| REQ-0001 | `add`, `subtract`, `multiply`, `divide` |
| REQ-0002 | `divide` (exception on zero) |
| REQ-0003 | `abs` |
| REQ-0004 | `mean`, `sum`, `min`, `max`, `range` |
| REQ-0005 | `mean`, `min`, `max`, `range` (nullopt on empty) |
