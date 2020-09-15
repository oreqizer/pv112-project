add_executable(01_window_final main.cpp application.cpp)

add_dependencies(01_window_final glfw glad)

target_link_libraries(01_window_final ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
target_include_directories(01_window_final 
	PRIVATE ${GLFW_INCLUDE_DIR}
	PRIVATE ${GLAD_INCLUDE_DIR}
	PRIVATE ${SINGLE_HEADER_LIBS_INCLUDE_DIR}
)