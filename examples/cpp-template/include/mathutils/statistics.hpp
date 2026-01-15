#pragma once

#include <vector>
#include <optional>

/**
 * @file statistics.hpp
 * @brief Statistical operations
 * 
 * Implements REQ-0004: Statistical Operations
 */

namespace mathutils {

/**
 * @class Statistics
 * @brief Provides statistical operations on numeric data
 * 
 * REQ-0004: The system shall provide basic statistical operations
 */
class Statistics {
public:
    /**
     * @brief Calculate the mean (average) of a dataset
     * @param data Vector of numeric values
     * @return Mean value, or std::nullopt if data is empty
     * 
     * REQ-0004: Mean calculation
     * REQ-0005: Empty dataset shall return nullopt
     */
    [[nodiscard]] static std::optional<double> mean(const std::vector<double>& data);

    /**
     * @brief Calculate the sum of a dataset
     * @param data Vector of numeric values
     * @return Sum of all values (0 if empty)
     * 
     * REQ-0004: Sum calculation
     */
    [[nodiscard]] static double sum(const std::vector<double>& data) noexcept;

    /**
     * @brief Find the minimum value in a dataset
     * @param data Vector of numeric values
     * @return Minimum value, or std::nullopt if data is empty
     * 
     * REQ-0004: Minimum value
     * REQ-0005: Empty dataset shall return nullopt
     */
    [[nodiscard]] static std::optional<double> min(const std::vector<double>& data);

    /**
     * @brief Find the maximum value in a dataset
     * @param data Vector of numeric values
     * @return Maximum value, or std::nullopt if data is empty
     * 
     * REQ-0004: Maximum value
     * REQ-0005: Empty dataset shall return nullopt
     */
    [[nodiscard]] static std::optional<double> max(const std::vector<double>& data);

    /**
     * @brief Calculate the range (max - min) of a dataset
     * @param data Vector of numeric values
     * @return Range, or std::nullopt if data is empty
     * 
     * REQ-0004: Range calculation
     * REQ-0005: Empty dataset shall return nullopt
     */
    [[nodiscard]] static std::optional<double> range(const std::vector<double>& data);
};

} // namespace mathutils
