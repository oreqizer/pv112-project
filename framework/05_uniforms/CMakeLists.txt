add_executable(05_uniforms main.cpp application.cpp)

add_dependencies(05_uniforms glfw glad framework)

target_link_libraries(05_uniforms ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} framework)
target_include_directories(05_uniforms 
	PRIVATE ${GLFW_INCLUDE_DIR}
	PRIVATE ${GLAD_INCLUDE_DIR}
	PRIVATE ${SINGLE_HEADER_LIBS_INCLUDE_DIR}
	PRIVATE ${FRAMEWORK_INCLUDE_DIR}
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main.vert" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main.vert" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main.frag" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main.frag" COPYONLY)
