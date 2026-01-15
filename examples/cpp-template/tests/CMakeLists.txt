# Test suite for MathUtils
# Uses CTest with simple test executables

# Test helper function
function(add_mathutils_test TEST_NAME)
    add_executable(${TEST_NAME} ${TEST_NAME}.cpp)
    target_link_libraries(${TEST_NAME} PRIVATE MathUtils::mathutils)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    
    # Set test properties
    set_tests_properties(${TEST_NAME} PROPERTIES
        TIMEOUT 10
        LABELS "unit"
    )
endfunction()

# Test executables
add_mathutils_test(test_calculator)
add_mathutils_test(test_statistics)

# Integration test (if needed)
# add_mathutils_test(test_integration)
