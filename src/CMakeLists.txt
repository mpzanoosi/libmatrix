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
        LIBRARY DESTINATION lib/
        PUBLIC_HEADER DESTINATION include/
        LIBRARY PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE
	)
	
# adding subdirectories
add_subdirectory(init)

# actually making the library
target_link_libraries(matrix init)