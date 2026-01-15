/**
 * @file test_calculator.cpp
 * @brief Tests for Calculator class
 * 
 * Traces to: REQ-0001, REQ-0002, REQ-0003
 */

#include "mathutils/calculator.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cassert>

using namespace mathutils;

// Test helper macros
#define TEST_ASSERT(condition, message) \
    if (!(condition)) { \
        std::cerr << "FAILED: " << message << std::endl; \
        return 1; \
    }

#define TEST_ASSERT_NEAR(a, b, epsilon, message) \
    if (std::fabs((a) - (b)) > (epsilon)) { \
        std::cerr << "FAILED: " << message << " (got " << (a) << ", expected " << (b) << ")" << std::endl; \
        return 1; \
    }

/**
 * Test addition operation
 * REQ-0001: The system shall provide basic arithmetic operations
 */
int test_add() {
    // Basic addition
    TEST_ASSERT_NEAR(Calculator::add(2.0, 3.0), 5.0, 1e-9, "2 + 3 = 5");
    
    // Negative numbers
    TEST_ASSERT_NEAR(Calculator::add(-2.0, 3.0), 1.0, 1e-9, "-2 + 3 = 1");
    TEST_ASSERT_NEAR(Calculator::add(-2.0, -3.0), -5.0, 1e-9, "-2 + -3 = -5");
    
    // Zero
    TEST_ASSERT_NEAR(Calculator::add(0.0, 5.0), 5.0, 1e-9, "0 + 5 = 5");
    TEST_ASSERT_NEAR(Calculator::add(5.0, 0.0), 5.0, 1e-9, "5 + 0 = 5");
    
    // Floating point
    TEST_ASSERT_NEAR(Calculator::add(1.5, 2.5), 4.0, 1e-9, "1.5 + 2.5 = 4.0");
    
    std::cout << "test_add: PASSED" << std::endl;
    return 0;
}

/**
 * Test subtraction operation
 * REQ-0001: The system shall provide basic arithmetic operations
 */
int test_subtract() {
    TEST_ASSERT_NEAR(Calculator::subtract(5.0, 3.0), 2.0, 1e-9, "5 - 3 = 2");
    TEST_ASSERT_NEAR(Calculator::subtract(3.0, 5.0), -2.0, 1e-9, "3 - 5 = -2");
    TEST_ASSERT_NEAR(Calculator::subtract(-2.0, -3.0), 1.0, 1e-9, "-2 - -3 = 1");
    TEST_ASSERT_NEAR(Calculator::subtract(0.0, 0.0), 0.0, 1e-9, "0 - 0 = 0");
    
    std::cout << "test_subtract: PASSED" << std::endl;
    return 0;
}

/**
 * Test multiplication operation
 * REQ-0001: The system shall provide basic arithmetic operations
 */
int test_multiply() {
    TEST_ASSERT_NEAR(Calculator::multiply(2.0, 3.0), 6.0, 1e-9, "2 * 3 = 6");
    TEST_ASSERT_NEAR(Calculator::multiply(-2.0, 3.0), -6.0, 1e-9, "-2 * 3 = -6");
    TEST_ASSERT_NEAR(Calculator::multiply(-2.0, -3.0), 6.0, 1e-9, "-2 * -3 = 6");
    TEST_ASSERT_NEAR(Calculator::multiply(0.0, 100.0), 0.0, 1e-9, "0 * 100 = 0");
    TEST_ASSERT_NEAR(Calculator::multiply(1.0, 42.0), 42.0, 1e-9, "1 * 42 = 42");
    
    std::cout << "test_multiply: PASSED" << std::endl;
    return 0;
}

/**
 * Test division operation
 * REQ-0001: The system shall provide basic arithmetic operations
 * REQ-0002: Division by zero shall throw an exception
 */
int test_divide() {
    // Normal division
    TEST_ASSERT_NEAR(Calculator::divide(6.0, 2.0), 3.0, 1e-9, "6 / 2 = 3");
    TEST_ASSERT_NEAR(Calculator::divide(7.0, 2.0), 3.5, 1e-9, "7 / 2 = 3.5");
    TEST_ASSERT_NEAR(Calculator::divide(-6.0, 2.0), -3.0, 1e-9, "-6 / 2 = -3");
    TEST_ASSERT_NEAR(Calculator::divide(0.0, 5.0), 0.0, 1e-9, "0 / 5 = 0");
    
    // REQ-0002: Division by zero shall throw an exception
    bool threw_exception = false;
    try {
        Calculator::divide(5.0, 0.0);
    } catch (const std::invalid_argument& e) {
        threw_exception = true;
    }
    TEST_ASSERT(threw_exception, "Division by zero should throw std::invalid_argument");
    
    std::cout << "test_divide: PASSED" << std::endl;
    return 0;
}

/**
 * Test absolute value operation
 * REQ-0003: The system shall provide absolute value operation
 */
int test_abs() {
    TEST_ASSERT_NEAR(Calculator::abs(5.0), 5.0, 1e-9, "abs(5) = 5");
    TEST_ASSERT_NEAR(Calculator::abs(-5.0), 5.0, 1e-9, "abs(-5) = 5");
    TEST_ASSERT_NEAR(Calculator::abs(0.0), 0.0, 1e-9, "abs(0) = 0");
    TEST_ASSERT_NEAR(Calculator::abs(-0.0), 0.0, 1e-9, "abs(-0) = 0");
    
    std::cout << "test_abs: PASSED" << std::endl;
    return 0;
}

int main() {
    std::cout << "Running Calculator tests..." << std::endl;
    std::cout << "Traces to: REQ-0001, REQ-0002, REQ-0003" << std::endl;
    std::cout << std::endl;
    
    int result = 0;
    
    result += test_add();
    result += test_subtract();
    result += test_multiply();
    result += test_divide();
    result += test_abs();
    
    std::cout << std::endl;
    if (result == 0) {
        std::cout << "All Calculator tests PASSED!" << std::endl;
    } else {
        std::cout << "Some tests FAILED!" << std::endl;
    }
    
    return result;
}
