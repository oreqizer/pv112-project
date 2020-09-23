aux_source_directory(src SRC)
add_executable(project main.cpp application.cpp ${SRC})

add_dependencies(project glfw glad framework)

target_link_libraries(project ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} framework)
target_include_directories(project 
	PRIVATE ${GLFW_INCLUDE_DIR}
	PRIVATE ${GLAD_INCLUDE_DIR}
	PRIVATE ${SINGLE_HEADER_LIBS_INCLUDE_DIR}
	PRIVATE ${FRAMEWORK_INCLUDE_DIR}
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/core.vert" "${CMAKE_CURRENT_BINARY_DIR}/shaders/core.vert" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/core.frag" "${CMAKE_CURRENT_BINARY_DIR}/shaders/core.frag" COPYONLY)
