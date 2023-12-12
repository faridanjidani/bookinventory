cmake_minimum_required(VERSION 3.0.0)



add_executable(test ${PROJECT_SOURCE_DIR}/main.cpp)



set_property(TARGET test PROPERTY CXX_STANDARD 20)



set(ENABLE_ASAN true)
set(ENABLE_UBSAN true)
INCLUDE(Sanitizers.cmake)
include(CodeCoverage.cmake)
APPEND_COVERAGE_COMPILER_FLAGS()
if(ENABLE_COVERAGE)
    # add_custom_target ( coverage ${CMAKE_CURRENT_SOURCE_DIR}/run_tests.sh ${CMAKE_CURRENT_BINARY_DIR}
    # WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage
        EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/run_tests
        EXECUTABLE_ARGS ${CMAKE_CURRENT_BINARY_DIR}
        LCOV_ARGS -rc lcov_branch_coverage=1
        GENHTML_ARGS  --branch-coverage
        DEPENDENCIES test_sv_set)

endif()


