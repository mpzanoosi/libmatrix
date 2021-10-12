# note: a good approach for adding .c and .h files
#		is to add them manually!
# 		if the number of files gets so big, maybe I 
#		switch to use file(GLOB_RECURSE ...) instead

# adding files to the project
add_library(matrix SHARED
		"init/matrix.c"
	)

# adding properties
set_target_properties(matrix PROPERTIES 
		PUBLIC_HEADER "init/matrix.h"
		VERSION ${VERSION_STRING}
		SOVERSION ${VERSION_MAJOR}
	)

# adding install method
INSTALL(TARGETS matrix 
        LIBRARY DESTINATION lib/matrix/
        PUBLIC_HEADER DESTINATION include/matrix/
        LIBRARY PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE
	)
	
# adding subdirectories
add_subdirectory(init)
add_subdirectory(basics)
add_subdirectory(funcs)

# actually making the library
target_link_libraries(matrix init basics funcs)