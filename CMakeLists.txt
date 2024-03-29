cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(dbtrain-mysql)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/third_party/antlr4-cpp-runtime-4.7/src)

file(GLOB_RECURSE ANTLR_SOURCES ${PROJECT_SOURCE_DIR}/third_party/*.cpp)
add_library(antlr4-runtime SHARED ${ANTLR_SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

file(GLOB_RECURSE DBTRAIN_MYSQL_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)
add_library(dbtrain_mysql_shared SHARED ${DBTRAIN_MYSQL_SOURCES})

target_link_libraries(dbtrain_mysql_shared antlr4-runtime)

# Add executable
file(GLOB_RECURSE EXECUTABLE_SOURCES ${PROJECT_SOURCE_DIR}/executable/*.cc)
foreach(executable_source ${EXECUTABLE_SOURCES})
    get_filename_component(executable_filename ${executable_source} NAME)
    string(REPLACE ".cc" "" executable ${executable_filename})
    add_executable(dbtrain_mysql_${executable} ${executable_source})
    target_link_libraries(dbtrain_mysql_${executable} dbtrain_mysql_shared)
endforeach(executable_source ${EXECUTABLE_SOURCES})

# Add test
file(GLOB TESTS ${PROJECT_SOURCE_DIR}/../dbtrain-mysql-test/test/test*)
foreach(test_dir ${TESTS})
    file(GLOB_RECURSE TEST_SOURCES ${test_dir}/*.cc)
    get_filename_component(test ${test_dir} NAME)
    add_executable(${test}_test ${TEST_SOURCES})
    target_link_libraries(${test}_test dbtrain_mysql_shared gtest)
    set_target_properties(${test}_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
endforeach(test_dir ${TESTS})
