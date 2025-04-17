cmake_minimum_required(VERSION 3.10)
project(mathlib VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create library target
add_library(mathlib INTERFACE)
target_include_directories(mathlib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Add executable
add_executable(mathlib_examples main.cpp)
target_link_libraries(mathlib_examples PRIVATE mathlib)
target_include_directories(mathlib_examples PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Install rules
install(TARGETS mathlib mathlib_examples EXPORT mathlibTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

# Export targets
install(EXPORT mathlibTargets
    FILE mathlibTargets.cmake
    NAMESPACE mathlib::
    DESTINATION lib/cmake/mathlib
)

# Create config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/mathlibConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/mathlibConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/mathlibConfig.cmake"
    INSTALL_DESTINATION lib/cmake/mathlib
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/mathlibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/mathlibConfigVersion.cmake"
    DESTINATION lib/cmake/mathlib
) 