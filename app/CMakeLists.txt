set(ENGINE_BASE_DIR "${PROJECT_SOURCE_DIR}/engine")

set(INCLUDE_DIRS
    include
	${ENGINE_BASE_DIR}/include
)

set(APP_SOURCE_FILES
	src/Colors.cpp
	src/Game.cpp
	src/Main.cpp
)

set(SOURCES
	${APP_SOURCE_FILES}
)

include_directories(${INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(SFML 2 REQUIRED graphics window audio system)

if(SFML_FOUND)
	include_directories( ${SFML_INCLUDE_DIR} )
	target_link_libraries( ${PROJECT_NAME}  ${SFML_LIBRARIES} )
	target_link_libraries( ${PROJECT_NAME}  ${SFML_DEPENDENCIES} )
endif()

target_link_libraries( ${PROJECT_NAME} engine)

if(EXISTS ${CMAKE_SOURCE_DIR}/content)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()