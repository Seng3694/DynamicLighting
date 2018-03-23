cmake_minimum_required(VERSION 3.5)

project (DynamicLighting)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_CXX_STANDARD 11)

if(WIN32)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

file(GLOB_RECURSE SOURCES src/*.cpp include/*.hpp include/*.h include/*.inl)

set(INCLUDE_DIRS
    include
)

include_directories(${INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

set(SFML_ROOT "C:/Program Files (x86)/SFML")
find_package(SFML 2 REQUIRED graphics window audio system)

if(SFML_FOUND)
	include_directories( ${SFML_INCLUDE_DIR} )
	target_link_libraries( ${PROJECT_NAME}  ${SFML_LIBRARIES} )
	target_link_libraries( ${PROJECT_NAME}  ${SFML_DEPENDENCIES} )
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/content)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()