set(ENGINE_BASE_DIR "${PROJECT_SOURCE_DIR}/engine")

set(INCLUDE_DIRS
    include
	${ENGINE_BASE_DIR}/include
)

set(SOURCES
	src/CollidableShapeTest.cpp
	src/Main.cpp
	src/MathHelperTest.cpp
	src/NullableTest.cpp
	src/RandomTest.cpp
)

include_directories(${INCLUDE_DIRS})

add_executable(tests ${SOURCES})

find_package(SFML 2 REQUIRED graphics window audio system)

if(SFML_FOUND)
	include_directories( ${SFML_INCLUDE_DIR} )
	target_link_libraries( tests  ${SFML_LIBRARIES} )
	target_link_libraries( tests  ${SFML_DEPENDENCIES} )
endif()

target_link_libraries( tests engine )