aux_source_directory(src SRC)
add_executable(project main.cpp application.cpp ${SRC})

# TODO maybe clean up relative paths of /../ and /project/

# IRRKLANG library
set(IRRKLANG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../libs/irrklang/include")
set(IRRKLANG_LIBRARIES
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/irrklang/lib/Winx64-visualStudio/irrKlang.lib"
    # "${CMAKE_CURRENT_SOURCE_DIR}/../libs/irrklang/bin/Winx64-visualStudio/irrKlang.dll"
    # "${CMAKE_CURRENT_SOURCE_DIR}/../libs/irrklang/bin/Winx64-visualStudio/ikpMP3.dll"
)

add_custom_command(TARGET project POST_BUILD
  # TODO cleanup, add release
  # Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../libs/irrklang/bin/Winx64-visualStudio/irrKlang.dll ${CMAKE_BINARY_DIR}/project/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../libs/irrklang/bin/Winx64-visualStudio/ikpMP3.dll ${CMAKE_BINARY_DIR}/project/Debug
)

# FREETYPE library
set(FREETYPE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../libs/freetype/include")
set(FREETYPE_LIBRARIES
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/freetype/win64/freetype.lib"
    # "${CMAKE_CURRENT_SOURCE_DIR}/../libs/freetype/win64/freetype.dll"
)

add_custom_command(TARGET project POST_BUILD
  # TODO cleanup, add release
  # Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../libs/freetype/win64/freetype.dll ${CMAKE_BINARY_DIR}/project/Debug
)

add_dependencies(project glfw glad framework)

target_link_libraries(project
	${GLFW_LIBRARIES}
	${GLAD_LIBRARIES}
	${IRRKLANG_LIBRARIES}
	${FREETYPE_LIBRARIES}
	framework
)
target_include_directories(project 
	PRIVATE ${GLFW_INCLUDE_DIR}
	PRIVATE ${GLAD_INCLUDE_DIR}
	PRIVATE ${IRRKLANG_INCLUDE_DIR}
	PRIVATE ${FREETYPE_INCLUDE_DIR}
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
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/sound/portal.mp3" "${CMAKE_CURRENT_BINARY_DIR}/sound/portal.mp3" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/sound/trombone.mp3" "${CMAKE_CURRENT_BINARY_DIR}/sound/trombone.mp3" COPYONLY)
