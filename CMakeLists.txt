CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

cmake_policy(SET CMP0022 NEW)



add_executable(mytest ${PROJECT_SOURCE_DIR}/main.cpp)



set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# Set C++ standard to C++17
target_compile_features(mytest PRIVATE cxx_std_17)

# Set compiler options, including -stdlib=libc++
target_compile_options(mytest PRIVATE -stdlib=libc++)

add_library(myinventorylib
    src/lib/book.cpp
)

target_compile_features(myinventorylib PRIVATE cxx_std_17)

target_include_directories(myinventorylib
   PUBLIC  /usr/local/mysql-connector-c++-8.2/include/
)
target_include_directories(myinventorylib 
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src/lib/include
)

target_link_libraries(myinventorylib
    PRIVATE /usr/local/mysql-connector-c++-8.2.0/lib64/libmysqlcppconn8.2.dylib
    PUBLIC /usr/local/mysql-connector-c++-8.2.0/lib64/libssl.3.dylib
    PUBLIC /usr/local/mysql-connector-c++-8.2.0/lib64/libcrypto.3.dylib
    # PRIVATE /usr/local/mysql-connector-c++-8.2.0/lib64/libmysqlcppconn8-static.a
)



target_link_libraries(mytest
    PRIVATE myinventorylib
    PRIVATE /usr/local/mysql-connector-c++-8.2.0/lib64/libmysqlcppconn8.2.dylib
    PUBLIC /usr/local/mysql-connector-c++-8.2.0/lib64/libcrypto.3.dylib
    PUBLIC /usr/local/mysql-connector-c++-8.2.0/lib64/libssl.3.dylib 
)



# # set(ENABLE_ASAN true)
# # set(ENABLE_UBSAN true)
# # INCLUDE(Sanitizers.cmake)
# # include(CodeCoverage.cmake)
# # APPEND_COVERAGE_COMPILER_FLAGS()
# # if(ENABLE_COVERAGE)
# #     # add_custom_target ( coverage ${CMAKE_CURRENT_SOURCE_DIR}/run_mytests.sh ${CMAKE_CURRENT_BINARY_DIR}
# #     # WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/)
# #     SETUP_TARGET_FOR_COVERAGE_LCOV(
# #         NAME coverage
# #         EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/run_mytests
# #         EXECUTABLE_ARGS ${CMAKE_CURRENT_BINARY_DIR}
# #         LCOV_ARGS -rc lcov_branch_coverage=1
# #         GENHTML_ARGS  --branch-coverage
# #         DEPENDENCIES mytest_sv_set)

# # endif()



