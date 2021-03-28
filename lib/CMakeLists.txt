#dummy.cpp only exists to not have add_library throw an error
#If you include actual .cpp files, then you don't need dummy.cpp
add_library(locallib dummy.cpp)
target_include_directories(locallib
	PUBLIC
	include
	
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
	)
