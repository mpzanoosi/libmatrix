# unit testing
if(TEST)
	# testing library components
	add_executable(test_matrix
			"test_matrix.c"
		)
	# target_include_directories(test_matrix PRIVATE "src/init/")
	target_link_libraries(test_matrix matrix)
endif()