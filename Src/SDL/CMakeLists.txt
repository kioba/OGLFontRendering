################################################################################
### SDLCXX Library ##############################################################
################################################################################

add_library (SDLCXX SHARED
				Src/FrameWindow.cpp)

SET_TARGET_PROPERTIES(SDLCXX PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(SDLCXX ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})

target_include_directories (SDLCXX PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Src")


# copy SDL2 libs
add_custom_command(TARGET SDLCXX POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		-E copy_directory
			"${RUNTIME_SDL2}"
			$<TARGET_FILE_DIR:SDLCXX>
		VERBATIM
		)


# copy GLEW libs
add_custom_command(TARGET SDLCXX POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		-E copy_directory
			"${RUNTIME_GLEW}"
			$<TARGET_FILE_DIR:SDLCXX>
		VERBATIM
		)

################################################################################
### SDLCXX Library Test  #######################################################
################################################################################

project(SDLTest)
add_executable(SDLTest Test/main.cpp)

target_link_libraries(SDLTest SDLCXX)

if(WIN32)
	# On Windows debug version opens console window.
	set_target_properties(SDLTest PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
	set_target_properties(SDLTest PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
	set_target_properties(SDLTest PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
	set_target_properties(SDLTest PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")

	# Windows release version does not open console window.
	set_target_properties(SDLTest PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
	set_target_properties(SDLTest PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")

	# do not let different linked libraries to be linked
	#set_target_properties(SDLTest PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:msvcrt.lib")
	set_target_properties(SDLTest PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:msvcrt.lib")
	set_target_properties(SDLTest PROPERTIES STATIC_LIBRARY_FLAGS "/NODEFAULTLIB:msvcrt.lib")
endif(WIN32)
