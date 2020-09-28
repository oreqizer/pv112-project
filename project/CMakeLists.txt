aux_source_directory(src SRC)
add_executable(project main.cpp application.cpp ${SRC})

add_dependencies(project glfw glad freeglut framework)

target_link_libraries(project ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} ${FREEGLUT_LIBRARIES} ${IRRKLANG_LIBRARY} framework)
target_include_directories(project 
	PRIVATE ${GLFW_INCLUDE_DIR}
	PRIVATE ${GLAD_INCLUDE_DIR}
	PRIVATE ${FREEGLUT_INCLUDE_DIR}
	PRIVATE ${IRRKLANG_INCLUDE_DIR}
	PRIVATE ${SINGLE_HEADER_LIBS_INCLUDE_DIR}
	PRIVATE ${FRAMEWORK_INCLUDE_DIR}
)

# Shaders
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/snake.vert" "${CMAKE_CURRENT_BINARY_DIR}/shaders/snake.vert" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/snake.frag" "${CMAKE_CURRENT_BINARY_DIR}/shaders/snake.frag" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/wall.vert" "${CMAKE_CURRENT_BINARY_DIR}/shaders/wall.vert" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/wall.frag" "${CMAKE_CURRENT_BINARY_DIR}/shaders/wall.frag" COPYONLY)

# Sound
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/sound/crunch.mp3" "${CMAKE_CURRENT_BINARY_DIR}/sound/crunch.mp3" COPYONLY)
