# main library cpp files
file(GLOB SRC_FILES
	"*.cpp"
)

file(GLOB INCLUDE_FILES
	"*.h"
)

set(MODULE_NAME "shell")
add_library(
	${MODULE_NAME}
	SHARED
	${SRC_FILES}
	${INCLUDE_FILES}
)

target_link_libraries(
	${MODULE_NAME}
	${MAIN_LIBRARY_NAME}
)

# copy files
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/shell.conf" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/shell.html" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/update.sh" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
