add_executable(02_shaders_final main.cpp application.cpp)

add_dependencies(02_shaders_final glfw glad framework)

target_link_libraries(02_shaders_final ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} framework)
target_include_directories(02_shaders_final 
	PRIVATE ${GLFW_INCLUDE_DIR}
	PRIVATE ${GLAD_INCLUDE_DIR}
	PRIVATE ${SINGLE_HEADER_LIBS_INCLUDE_DIR}
	PRIVATE ${FRAMEWORK_INCLUDE_DIR}
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main.vert" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main.vert" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main.frag" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main.frag" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main2.vert" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main2.vert" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/main2.frag" "${CMAKE_CURRENT_BINARY_DIR}/shaders/main2.frag" COPYONLY)