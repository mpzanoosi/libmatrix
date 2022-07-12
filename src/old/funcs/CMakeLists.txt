# funcs subfolder contains function-based operations
# like performing element-wise calculations, etc.
add_library(funcs
		"funcs.c"
	)

# set compile options
set(CMAKE_C_FLAGS "-rdynamic -fPIC -g -Wall")

# compile
target_link_libraries(funcs init -lrt -ldl -lm)