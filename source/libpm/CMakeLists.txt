# main library cpp files
file(GLOB SRC_FILES
	"*.cpp"
	"http/*.cpp"
	"module/*.cpp"
	"os/*.cpp"
)

file(GLOB INCLUDE_FILES
	"*.h"
	"http/*.h"
	"module/*.h"
	"os/*.h"
)

add_library(
	${MAIN_LIBRARY_NAME}
	SHARED
	${SRC_FILES}
	${INCLUDE_FILES}
)

target_link_libraries(
	${MAIN_LIBRARY_NAME}
	${CMAKE_THREAD_LIBS_INIT}
	${CMAKE_DL_LIBS}
)
