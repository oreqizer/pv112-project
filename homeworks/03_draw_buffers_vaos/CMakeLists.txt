add_executable(03_draw_buffers_vaos main.cpp application.cpp)

add_dependencies(03_draw_buffers_vaos glfw glad framework)

target_link_libraries(03_draw_buffers_vaos ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} framework)
target_include_directories(03_draw_buffers_vaos 
	PRIVATE ${GLFW_INCLUDE_DIR}
	PRIVATE ${GLAD_INCLUDE_DIR}
	PRIVATE ${SINGLE_HEADER_LIBS_INCLUDE_DIR}
	PRIVATE ${FRAMEWORK_INCLUDE_DIR}
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main.vert" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main.vert" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main.frag" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main.frag" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main_vao.vert" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main_vao.vert" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main_vao.frag" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main_vao.frag" COPYONLY)

