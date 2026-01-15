#pragma once

/**
 * @file calculator.hpp
 * @brief Basic arithmetic operations
 * 
 * Implements REQ-0001: Basic Arithmetic Operations
 */

namespace mathutils {

/**
 * @class Calculator
 * @brief Provides basic arithmetic operations
 * 
 * REQ-0001: The system shall provide basic arithmetic operations
 */
class Calculator {
public:
    /**
     * @brief Add two numbers
     * @param a First operand
     * @param b Second operand
     * @return Sum of a and b
     * 
     * REQ-0001: Addition operation
     */
    [[nodiscard]] static double add(double a, double b) noexcept;

    /**
     * @brief Subtract two numbers
     * @param a First operand
     * @param b Second operand
     * @return Difference (a - b)
     * 
     * REQ-0001: Subtraction operation
     */
    [[nodiscard]] static double subtract(double a, double b) noexcept;

    /**
     * @brief Multiply two numbers
     * @param a First operand
     * @param b Second operand
     * @return Product of a and b
     * 
     * REQ-0001: Multiplication operation
     */
    [[nodiscard]] static double multiply(double a, double b) noexcept;

    /**
     * @brief Divide two numbers
     * @param a Dividend
     * @param b Divisor
     * @return Quotient (a / b)
     * @throws std::invalid_argument if b is zero
     * 
     * REQ-0001: Division operation
     * REQ-0002: Division by zero shall throw an exception
     */
    [[nodiscard]] static double divide(double a, double b);

    /**
     * @brief Calculate the absolute value
     * @param value Input value
     * @return Absolute value
     * 
     * REQ-0003: Absolute value operation
     */
    [[nodiscard]] static double abs(double value) noexcept;
};

} // namespace mathutils
