# basics subfolder contains very basic operations on matrices,
# like matrix_transpose, etc.
add_library(basics
		"checking.c"
		"basics.c"
	)

# set compile options
set(CMAKE_C_FLAGS "-rdynamic -fPIC -g -Wall")

# compile
target_link_libraries(basics init -lrt -ldl -lm)