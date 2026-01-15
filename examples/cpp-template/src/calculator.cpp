#include "mathutils/calculator.hpp"
#include <stdexcept>
#include <cmath>

namespace mathutils {

double Calculator::add(double a, double b) noexcept {
    return a + b;
}

double Calculator::subtract(double a, double b) noexcept {
    return a - b;
}

double Calculator::multiply(double a, double b) noexcept {
    return a * b;
}

double Calculator::divide(double a, double b) {
    // REQ-0002: Division by zero shall throw an exception
    if (b == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

double Calculator::abs(double value) noexcept {
    return std::fabs(value);
}

} // namespace mathutils
