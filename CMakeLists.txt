cmake_minimum_required (VERSION 3.8)
project (bongocat C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CSFML_DIR "${CMAKE_SOURCE_DIR}/libs/CSFML")

file(GLOB_RECURSE SOURCES "src/*.c")
file(GLOB_RECURSE HEADERS "src/*.h")

add_executable(bongocat ${SOURCES} ${HEADERS})

target_link_libraries(bongocat
	${CSFML_DIR}/lib/msvc/csfml-graphics.lib
	${CSFML_DIR}/lib/msvc/csfml-system.lib
	${CSFML_DIR}/lib/msvc/csfml-window.lib
	${CSFML_DIR}/lib/msvc/csfml-audio.lib
)

target_link_options(bongocat PRIVATE "/subsystem:windows" "/entry:mainCRTStartup")

include_directories(${CSFML_DIR}/include ${CMAKE_SOURCE_DIR}/src)

file(GLOB DLLS "bin/*.dll")
add_custom_command(
	TARGET bongocat
	POST_BUILD
	COMMENT "Copying required files"
	COMMAND ${CMAKE_COMMAND} -E copy ${DLLS} ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
)