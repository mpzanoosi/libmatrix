# minimum required cmake
cmake_minimum_required(VERSION 3.9)

# project name
project(libmatrix)

# versioning
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)
set(VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

# uncomment next line to enable testing
option(TEST "option to test ipc engine" ON)

# directories for outputs
if(TEST)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRACTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# making libmatrix
set(CMAKE_C_FLAGS "-rdynamic -fPIC -g -Wformat")
# adding source files
add_library(matrix	SHARED
		# "src/backtrace.c"
		"src/helper.c"
		"src/vidx.c"
		"src/array.c"
		"src/funcs.c"
		"src/operator.c"
		"src/matrix.c"
	)
# adding properties
set_target_properties(matrix PROPERTIES 
	PUBLIC_HEADER "src/matrix.h"
	VERSION ${VERSION_STRING}
	SOVERSION ${VERSION_MAJOR}
	)
# adding install method
INSTALL(TARGETS matrix 
        LIBRARY DESTINATION lib/
        PUBLIC_HEADER DESTINATION include/
        LIBRARY PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE
	)
# actually making the library
target_link_libraries(matrix -lrt -ldl -lm)

# unit testing
if(TEST)
	# test ipc engine
	add_executable(test_matrix
			"test/test_matrix.c"
		)
	target_include_directories(test_matrix PRIVATE "src/")
	target_link_libraries(test_matrix matrix)
endif()
