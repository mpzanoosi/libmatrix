# minimum required cmake
cmake_minimum_required(VERSION 3.16)

# project name
project(libmatrix
		DESCRIPTION "library for fast & memory-efficient matrix computations using C"
		HOMEPAGE_URL "https://github.com/mpzanoosi/libmatrix")

# versioning
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)
set(VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

# uncomment next line to enable testing
option(TEST "option to libmatrix components" ON)

# directories for outputs
if(TEST)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
	add_subdirectory(utest)
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRACTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# adding subdirectories
add_subdirectory(src)