cmake_minimum_required(VERSION 3.6)
project(FileSpoT C CXX)

# Includes
set(FST_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
include_directories(${FST_INCLUDE_DIRS})

# Sources
set(FST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(FST_SOURCES
	${FST_SOURCE_DIR}/Ifstream.cpp)

# Library
set(FST_NAME filespot)
set(FST_LIBRARIES ${FST_NAME})
add_library(${FST_NAME} ${FST_SOURCES})
target_include_directories(${FST_NAME} PUBLIC ${FST_INCLUDE_DIRS})

# Test
set(FST_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
include(${FST_TEST_DIR}/Tests.cmake)
