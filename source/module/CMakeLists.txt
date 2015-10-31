# main library cpp files
file(GLOB SRC_FILES
	"*.cpp"
)

file(GLOB INCLUDE_FILES
	"*.h"
)

set(MODULE_NAME "module")
add_library(
	${MODULE_NAME}
	SHARED
	${SRC_FILES}
	${INCLUDE_FILES}
)

target_link_libraries(
	${MODULE_NAME}
)
