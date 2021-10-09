# NOTE: all submodules are able to be used as a library by add_library command (modular coding issue)
# adding executables into this submodule (as a local library)
add_library(init
		"helper.c"
		"vidx.c"
		"array.c"
		"funcs.c"
		"operator.c"
		"matrix.c"
	)

# set compile options
set(CMAKE_C_FLAGS "-rdynamic -fPIC -g -Wall")

# compile
target_link_libraries(init -lrt -ldl -lm)