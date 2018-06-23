cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 11)

project(FileSpot C CXX)

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
	set(ANDROID ON)
	add_definitions(-DANDROID)
endif()

# Includes
set(FST_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

# Sources
set(FST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(FST_SOURCES    ${FST_SOURCE_DIR}/Ifstream.cpp)

if(ANDROID)
	set(FST_SOURCES ${FST_SOURCES}
		${FST_SOURCE_DIR}/AssetManager.cpp)
endif()

# Library
set(FST_NAME filespot)
set(FST_LIBRARY ${FST_NAME})
set(FST_LIBRARIES ${FST_LIBRARY})
if(ANDROID)
	set(FST_LIBRARIES ${FST_LIBRARIES} android)
endif()

add_library(${FST_NAME} ${FST_SOURCES})
target_include_directories(${FST_NAME} PUBLIC ${FST_INCLUDE_DIRS})
target_link_libraries(${FST_NAME} ${FST_LIBRARIES})

# Test
set(FST_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
include(${FST_TEST_DIR}/Tests.cmake)
