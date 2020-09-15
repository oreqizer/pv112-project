add_executable(07_framebuffer main.cpp application.cpp)

add_dependencies(07_framebuffer glfw glad framework)

target_link_libraries(07_framebuffer ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} framework)
target_include_directories(07_framebuffer 
	PRIVATE ${GLFW_INCLUDE_DIR}
	PRIVATE ${GLAD_INCLUDE_DIR}
	PRIVATE ${SINGLE_HEADER_LIBS_INCLUDE_DIR}
	PRIVATE ${FRAMEWORK_INCLUDE_DIR}
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main.vert" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main.vert" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main.frag" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main.frag" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/postprocess.vert" "${CMAKE_CURRENT_BINARY_DIR}/shaders/postprocess.vert" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/postprocess.frag" "${CMAKE_CURRENT_BINARY_DIR}/shaders/postprocess.frag" COPYONLY)

# Copy images to compile directory
configure_file("${IMAGE_DIR}/rocks.jpg" "${CMAKE_CURRENT_BINARY_DIR}/images/rocks.jpg" COPYONLY)
configure_file("${IMAGE_DIR}/wood.jpg" "${CMAKE_CURRENT_BINARY_DIR}/images/wood.jpg" COPYONLY)