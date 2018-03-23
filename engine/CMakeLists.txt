set(INCLUDE_DIRS
	include
)

set(SOURCES
	src/BaseGame.cpp
	src/FpsCounter.cpp
	src/MathHelper.cpp
	src/Random.cpp
	src/LightSource.cpp
	src/CollidableShape.cpp
	src/Line.cpp
)

include_directories(${INCLUDE_DIRS})

add_library(engine ${SOURCES})

find_package(SFML 2 REQUIRED graphics window audio system)

if(SFML_FOUND)
	include_directories( ${SFML_INCLUDE_DIR} )
	target_link_libraries( engine  ${SFML_LIBRARIES} )
	target_link_libraries( engine  ${SFML_DEPENDENCIES} )
endif()