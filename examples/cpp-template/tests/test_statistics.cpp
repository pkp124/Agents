/**
 * @file test_statistics.cpp
 * @brief Tests for Statistics class
 * 
 * Traces to: REQ-0004, REQ-0005
 */

#include "mathutils/statistics.hpp"
#include <iostream>
#include <cmath>
#include <vector>

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
 * Test mean calculation
 * REQ-0004: The system shall provide basic statistical operations
 * REQ-0005: Empty dataset shall return nullopt
 */
int test_mean() {
    // Normal case
    std::vector<double> data1 = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto result1 = Statistics::mean(data1);
    TEST_ASSERT(result1.has_value(), "mean should return value for non-empty data");
    TEST_ASSERT_NEAR(*result1, 3.0, 1e-9, "mean of {1,2,3,4,5} = 3");
    
    // Single element
    std::vector<double> data2 = {42.0};
    auto result2 = Statistics::mean(data2);
    TEST_ASSERT(result2.has_value(), "mean should return value for single element");
    TEST_ASSERT_NEAR(*result2, 42.0, 1e-9, "mean of {42} = 42");
    
    // REQ-0005: Empty dataset
    std::vector<double> empty;
    auto result_empty = Statistics::mean(empty);
    TEST_ASSERT(!result_empty.has_value(), "mean of empty dataset should be nullopt");
    
    std::cout << "test_mean: PASSED" << std::endl;
    return 0;
}

/**
 * Test sum calculation
 * REQ-0004: The system shall provide basic statistical operations
 */
int test_sum() {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    TEST_ASSERT_NEAR(Statistics::sum(data), 15.0, 1e-9, "sum of {1,2,3,4,5} = 15");
    
    std::vector<double> negative = {-1.0, -2.0, 3.0};
    TEST_ASSERT_NEAR(Statistics::sum(negative), 0.0, 1e-9, "sum of {-1,-2,3} = 0");
    
    std::vector<double> empty;
    TEST_ASSERT_NEAR(Statistics::sum(empty), 0.0, 1e-9, "sum of {} = 0");
    
    std::cout << "test_sum: PASSED" << std::endl;
    return 0;
}

/**
 * Test min calculation
 * REQ-0004: The system shall provide basic statistical operations
 * REQ-0005: Empty dataset shall return nullopt
 */
int test_min() {
    std::vector<double> data = {3.0, 1.0, 4.0, 1.0, 5.0};
    auto result = Statistics::min(data);
    TEST_ASSERT(result.has_value(), "min should return value for non-empty data");
    TEST_ASSERT_NEAR(*result, 1.0, 1e-9, "min of {3,1,4,1,5} = 1");
    
    std::vector<double> negative = {-5.0, -1.0, -10.0};
    auto result_neg = Statistics::min(negative);
    TEST_ASSERT(result_neg.has_value(), "min should return value");
    TEST_ASSERT_NEAR(*result_neg, -10.0, 1e-9, "min of {-5,-1,-10} = -10");
    
    // REQ-0005: Empty dataset
    std::vector<double> empty;
    TEST_ASSERT(!Statistics::min(empty).has_value(), "min of empty should be nullopt");
    
    std::cout << "test_min: PASSED" << std::endl;
    return 0;
}

/**
 * Test max calculation
 * REQ-0004: The system shall provide basic statistical operations
 * REQ-0005: Empty dataset shall return nullopt
 */
int test_max() {
    std::vector<double> data = {3.0, 1.0, 4.0, 1.0, 5.0};
    auto result = Statistics::max(data);
    TEST_ASSERT(result.has_value(), "max should return value for non-empty data");
    TEST_ASSERT_NEAR(*result, 5.0, 1e-9, "max of {3,1,4,1,5} = 5");
    
    std::vector<double> negative = {-5.0, -1.0, -10.0};
    auto result_neg = Statistics::max(negative);
    TEST_ASSERT(result_neg.has_value(), "max should return value");
    TEST_ASSERT_NEAR(*result_neg, -1.0, 1e-9, "max of {-5,-1,-10} = -1");
    
    // REQ-0005: Empty dataset
    std::vector<double> empty;
    TEST_ASSERT(!Statistics::max(empty).has_value(), "max of empty should be nullopt");
    
    std::cout << "test_max: PASSED" << std::endl;
    return 0;
}

/**
 * Test range calculation
 * REQ-0004: The system shall provide basic statistical operations
 * REQ-0005: Empty dataset shall return nullopt
 */
int test_range() {
    std::vector<double> data = {3.0, 1.0, 4.0, 1.0, 5.0};
    auto result = Statistics::range(data);
    TEST_ASSERT(result.has_value(), "range should return value for non-empty data");
    TEST_ASSERT_NEAR(*result, 4.0, 1e-9, "range of {3,1,4,1,5} = 4 (5-1)");
    
    std::vector<double> same = {5.0, 5.0, 5.0};
    auto result_same = Statistics::range(same);
    TEST_ASSERT(result_same.has_value(), "range should return value");
    TEST_ASSERT_NEAR(*result_same, 0.0, 1e-9, "range of {5,5,5} = 0");
    
    // REQ-0005: Empty dataset
    std::vector<double> empty;
    TEST_ASSERT(!Statistics::range(empty).has_value(), "range of empty should be nullopt");
    
    std::cout << "test_range: PASSED" << std::endl;
    return 0;
}

int main() {
    std::cout << "Running Statistics tests..." << std::endl;
    std::cout << "Traces to: REQ-0004, REQ-0005" << std::endl;
    std::cout << std::endl;
    
    int result = 0;
    
    result += test_mean();
    result += test_sum();
    result += test_min();
    result += test_max();
    result += test_range();
    
    std::cout << std::endl;
    if (result == 0) {
        std::cout << "All Statistics tests PASSED!" << std::endl;
    } else {
        std::cout << "Some tests FAILED!" << std::endl;
    }
    
    return result;
}
