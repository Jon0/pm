add_definitions(-std=c++14)

# build main library
set(MAIN_LIBRARY_NAME "pm")
add_subdirectory(libpm)
include_directories("${PROJECT_SOURCE_DIR}/source/libpm")


# build modules
add_subdirectory(module)
add_subdirectory(install)

# executable files
file(GLOB MAIN_FILES
	"*.cpp"
)

set(EXECUTABLE_NAME "pmstart")
add_executable(${EXECUTABLE_NAME} ${MAIN_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${MAIN_LIBRARY_NAME})
