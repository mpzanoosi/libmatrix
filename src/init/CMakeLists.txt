# init subfolder contains initialization of libmatrix including
# - init/set/get of different structures and attributes
# - initializing specific matrices and vectors, like matrix_linspace function
add_library(init
		"helper.c"
		"vidx.c"
		"array.c"
		"matrix.c"
	)

# set compile options
set(CMAKE_C_FLAGS "-rdynamic -fPIC -g -Wall")

# compile
target_link_libraries(init -lrt -ldl -lm)