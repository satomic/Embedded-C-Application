cmake_minimum_required(VERSION 3.16)

project(internal_modules_test_framework
    VERSION 1.0.0
    DESCRIPTION "AI Tool Evaluation Framework for Internal Module Usage"
    LANGUAGES C CXX
)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags for embedded-like environment
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -O2")

# Debug flags
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -DDEBUG -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -DDEBUG -O0")

# Include directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/internal_modules)

# Internal Module Libraries
add_subdirectory(internal_modules)

# Test scenarios (optional - can be built separately)
option(BUILD_TEST_SCENARIOS "Build test scenario examples" OFF)
if(BUILD_TEST_SCENARIOS)
    add_subdirectory(test_scenarios)
endif()

# Create a library containing all internal modules
add_library(internal_modules_all INTERFACE)
target_link_libraries(internal_modules_all INTERFACE
    xgpio_hal
    xspi_hal
    xi2c_hal
    xuart_hal
    xtemp_sensor
    xaccel_sensor
    xgyro_sensor
    xmem_pool
    xring_buffer
    xdma_manager
    xcan_protocol
    xmodbus_protocol
    xproprietary_protocol
    xrtos_scheduler
    xhw_timer
    xsoft_timer
    xlcd_display
    xpower_mgmt
    xcrypto_engine
)

# Export configuration for external projects
install(TARGETS internal_modules_all EXPORT InternalModulesTargets)
install(DIRECTORY internal_modules/ DESTINATION include/internal_modules
    FILES_MATCHING PATTERN "*.h")

# Create config files for find_package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    InternalModulesConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    cmake/InternalModulesConfig.cmake.in
    InternalModulesConfig.cmake
    INSTALL_DESTINATION lib/cmake/InternalModules
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/InternalModulesConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/InternalModulesConfigVersion.cmake
    DESTINATION lib/cmake/InternalModules
)

install(EXPORT InternalModulesTargets
    FILE InternalModulesTargets.cmake
    NAMESPACE InternalModules::
    DESTINATION lib/cmake/InternalModules
)

# Documentation target
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXTRACT_PRIVATE YES)
    set(DOXYGEN_EXTRACT_STATIC YES)
    
    doxygen_add_docs(docs
        ${CMAKE_SOURCE_DIR}/internal_modules
        COMMENT "Generate API documentation"
    )
endif()

# Print configuration summary
message(STATUS "")
message(STATUS "Internal Modules Test Framework Configuration:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  Build test scenarios: ${BUILD_TEST_SCENARIOS}")
message(STATUS "")