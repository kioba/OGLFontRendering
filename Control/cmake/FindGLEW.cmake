#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_PATH
# GLEW_LIBRARY
#

IF (WIN32)
	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
		$ENV{PROGRAMFILES}/GLEW/include
		${PROJECT_SOURCE_DIR}/cmake/glew-1.12.0/include
		$ENV{GLEW}/include
		${GLEW}/include
		DOC "The directory where GL/glew.h resides")

	FIND_LIBRARY( GLEW_LIBRARY
		NAMES glew GLEW glew32
		# glew32s glew32mx glew32mxs glew32d glew32sd glew32mxsd glew32smxd
		PATHS
		$ENV{PROGRAMFILES}/GLEW/lib
		$ENV{GLEW}/bin/Release/Win32
		${GLEW}/bin/Release/Win32
		${PROJECT_SOURCE_DIR}/cmake/glew-1.12.0/bin/Release/Win32
		$ENV{GLEW}/lib/Release/Win32
		${GLEW}/lib/Release/Win32
		${PROJECT_SOURCE_DIR}/cmake/glew-1.12.0/lib/Release/Win32
		DOC "The GLEW library")

ELSE (WIN32)
	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where GL/glew.h resides")

	FIND_LIBRARY( GLEW_LIBRARY
		NAMES GLEW glew
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The GLEW library")
ENDIF (WIN32)

IF ((GLEW_INCLUDE_PATH STREQUAL "NOTFOUND") OR (GLEW_LIBRARY STREQUAL "NOTFOUND"))
	SET( GLEW_FOUND 0 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ELSE ((GLEW_INCLUDE_PATH STREQUAL "NOTFOUND") OR (GLEW_LIBRARY STREQUAL "NOTFOUND"))
	SET( GLEW_FOUND 1 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ENDIF ((GLEW_INCLUDE_PATH STREQUAL "NOTFOUND") OR (GLEW_LIBRARY STREQUAL "NOTFOUND"))

MARK_AS_ADVANCED( GLEW_FOUND )
