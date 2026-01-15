# MathUtils library

add_library(mathutils
    calculator.cpp
    statistics.cpp
)

target_include_directories(mathutils
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Alias for use in subdirectories
add_library(MathUtils::mathutils ALIAS mathutils)
