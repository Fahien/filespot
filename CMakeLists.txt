cmake_minimum_required( VERSION 3.15 )

set( CMAKE_C_STANDARD   11 )
set( CMAKE_CXX_STANDARD 17 )

project( filespot
	VERSION 0.1.0
	LANGUAGES C CXX )

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
	set(ANDROID ON)
	add_definitions(-DANDROID)
endif()

# Includes
set(FST_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

# Sources
set(FST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(FST_SOURCES
	${FST_SOURCE_DIR}/ifstream.cpp
	${FST_SOURCE_DIR}/file.cpp)

if(ANDROID)
	set(FST_SOURCES ${FST_SOURCES}
		${FST_SOURCE_DIR}/asset.cpp)
endif()

# Library
set(FST_LIBRARY ${PROJECT_NAME})
set(FST_LIBRARIES ${FST_LIBRARY})
if(ANDROID)
	set(FST_ANDROID_LIBS android)
	set(FST_LIBRARIES ${FST_LIBRARIES} ${FST_ANDROID_LIBS})
endif()

add_library(${PROJECT_NAME} ${FST_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${FST_INCLUDE_DIRS})
if(ANDROID)
	target_link_libraries(${PROJECT_NAME} ${FST_ANDROID_LIBS})
endif()

# Test
set(FST_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
include(${FST_TEST_DIR}/Tests.cmake)
