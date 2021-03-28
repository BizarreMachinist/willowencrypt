cmake_minimum_required(VERSION 3.18.4)
set(PROJ_VER 1.0.0)
set(PROJ_NAME willowencrypt)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
#set(JSON_BuildTests OFF CACHE INTERNAL "")

project(${PROJ_NAME} VERSION ${PROJ_VER})
configure_file(mainConfig.hpp.in mainConfig.hpp @ONLY)
include(FetchContent)

FetchContent_Declare(nlohmann_json
	GIT_REPOSITORY https://github.com/nlohmann/json.git
	PREFIX ${PROJECT_SOURCE_DIR}/externals
	INSTALL_COMMAND ""
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(lib)
list(APPEND EXTRA_LIBS locallib)

target_include_directories(${PROJECT_NAME}
	PUBLIC
	${PROJECT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
	${EXTRA_LIBS}
	
	PRIVATE
	nlohmann_json::nlohmann_json
)
