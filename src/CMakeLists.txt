# CMakeLists for libmatrix; source files are added manually 
# which seems that is a good approach! :/

# adding files to the project
add_library(matrix SHARED
	"core/array.c"
	"core/basic.c"
	"core/check.c"
	"core/init.c"
	"core/mm.c"
	)

# adding properties
set_target_properties(matrix PROPERTIES 
		PUBLIC_HEADER "core/matrix.h"
		VERSION ${VERSION_STRING}
		SOVERSION ${VERSION_MAJOR}
	)

# adding install method
INSTALL(TARGETS matrix 
        LIBRARY DESTINATION lib/matrix/
        PUBLIC_HEADER DESTINATION include/matrix/
        LIBRARY PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE
	)
	
# adding new subdirectories
# 1. add your CMakeLists.txt into your subdir
# 2. use add_subdirectory(<dir>) below
# 3. add made object files into target_link_libraries() in the end

# add_subdirectory(stat)

# making the library
set(CMAKE_C_FLAGS "-rdynamic -fPIC -g -Wall")
target_link_libraries(matrix -lrt -ldl -lm)