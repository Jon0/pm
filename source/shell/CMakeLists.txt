
# shell files
file(GLOB SHELL_FILES
	"*.sh"
)

# copy files
file(COPY "${SHELL_FILES}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
