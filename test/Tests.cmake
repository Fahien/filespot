function(make_test TEST_NAME)
	# Sources
	set(TEST_SOURCES ${FST_TEST_DIR}/${TEST_NAME}.cpp)
	source_group(${TEST_NAME} FILES ${TEST_SOURCES})
	
	# Executable
	add_executable(${TEST_NAME} ${TEST_SOURCES})
	target_include_directories(${TEST_NAME} PUBLIC ${FST_INCLUDE_DIRS})
	set_target_properties(${TEST_NAME} PROPERTIES LINKER_LANGUAGE CXX)
	target_link_libraries(${TEST_NAME} ${FST_LIBRARIES})
	add_test(${TEST_NAME} ${EXECUTABLE_OUTPUT_PATH}/${TEST_NAME})
endfunction(make_test)

make_test(fst-test)
file(COPY ${FST_TEST_DIR}/test.txt DESTINATION ${PROJECT_BINARY_DIR}/test)

include(CTest)
