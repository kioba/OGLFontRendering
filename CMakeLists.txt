cmake_minimum_required (VERSION 3.0.2)

# "MSVC" is a string and does not derefered for variables
cmake_policy(SET CMP0054 OLD)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Control/cmake")

# maybe later for release?
# set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/BUILD/x32")
# set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/BUILD/x32")

set(SDL2 "${CMAKE_CURRENT_SOURCE_DIR}/Control/cmake/SDL2-2.0.3-VC")
set(GLEW "${CMAKE_CURRENT_SOURCE_DIR}/Control/cmake/glew-1.12.0")
set(FONTS "${CMAKE_CURRENT_SOURCE_DIR}/Control/Data")


# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR
	${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR
	${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")

	INCLUDE(FindPkgConfig)

	PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
	INCLUDE_DIRECTORIES(${SDL2IMAGE_INCLUDE_DIRS})

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")

	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4  /WX /EHsc /MT" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()

	if (RELEASE)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")
	else (RELEASE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd")
	endif (RELEASE)

	set(RUNTIME_SDL2 "${CMAKE_CURRENT_SOURCE_DIR}/Control/WRL/SDL2/SDL2-2.0.3-win32-x86")
	set(RUNTIME_GLEW "${CMAKE_CURRENT_SOURCE_DIR}/Control/WRL/GLEW/Win32/Normal")
endif()

set(errorlevel 0)

################################
# OpenGL
################################

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIR})
	message("-- OpenGL found!")
else(OPENGL_FOUND)
	message(FATAL_ERROR "-- Could not find OpenGL!")
endif(OPENGL_FOUND)


################################
# GLEW
################################

find_package(GLEW REQUIRED)
if (${GLEW_FOUND} STREQUAL "1")
	include_directories(${GLEW_INCLUDE_PATH})
	message ("-- GLEW found!")
else(${GLEW_FOUND} STREQUAL "1")
	message (FATAL_ERROR "-- Could not find GLEW!")
endif(${GLEW_FOUND} STREQUAL "1")


################################
# GLM
################################

include_directories (Src/3thParty/glm)


################################
# Poly2Tri
################################

include_directories (Src/3thParty/poly2tri/poly2tri)

################################
# GoogleTest
################################

ADD_SUBDIRECTORY (Src/3thParty/googletest/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# SDL2
################################

find_package(SDL2 REQUIRED)
if (${SDL2_FOUND} STREQUAL "TRUE")
	include_directories(${SDL2_INCLUDE_DIR})
	message ("-- SDL2 found!")
else ()
	message (FATAL_ERROR "Could not find SDL2!")
endif ()


################################
# Project
################################

add_subdirectory(Src/Ragna)
add_subdirectory(Src/Runic)
add_subdirectory(Src/SDL)
add_subdirectory(Src/GFX)
