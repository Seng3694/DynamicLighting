cmake_minimum_required(VERSION 3.5)

project (DynamicLighting)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_CXX_STANDARD 14)

if(WIN32)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

set(SFML_ROOT "C:/Program Files (x86)/SFML")

add_subdirectory(engine)
add_subdirectory(app)
add_subdirectory(tests)