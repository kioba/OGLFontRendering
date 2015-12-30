################################################################################
### GFXMain APP ################################################################
################################################################################

project(GFXMain)

add_executable(GFXMain
				Src/main.cpp
				Src/App.cpp
			)

add_dependencies(GFXMain SDLCXX runic ragna)

target_link_libraries(GFXMain LINK_PUBLIC
						# 3thParty
						${GLEW_LIBRARY}
						${OPENGL_LIBRARIES}
						${SDL2IMAGE_LIBRARIES}
						# Self
						SDLCXX
						ragna
						runic
					)

if(WIN32)
	# On Windows debug version opens console window.
	set_target_properties(GFXMain PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
	set_target_properties(GFXMain PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
	set_target_properties(GFXMain PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
	set_target_properties(GFXMain PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")

	# Windows release version does not open console window.
	set_target_properties(GFXMain PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
	set_target_properties(GFXMain PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")

	# set_target_properties(GFXMain PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:msvcrt.lib")
	set_target_properties(GFXMain PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:msvcrt.lib")
	set_target_properties(GFXMain PROPERTIES STATIC_LIBRARY_FLAGS "/NODEFAULTLIB:msvcrt.lib")

endif(WIN32)

# copy Fonts
add_custom_command(TARGET GFXMain POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		-E copy_directory
			"${FONTS}"
			"$<TARGET_FILE_DIR:GFXMain>/Data"
		VERBATIM
		)


# copy SDLCXX + SDL2 libs
add_custom_command(TARGET GFXMain POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		-E copy_directory
			$<TARGET_FILE_DIR:SDLCXX>
			$<TARGET_FILE_DIR:GFXMain>
		VERBATIM
		)


# copy Ragna libs
add_custom_command(TARGET GFXMain POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		-E copy_directory
			$<TARGET_FILE_DIR:ragna>
			$<TARGET_FILE_DIR:GFXMain>
		VERBATIM
		)


# copy Runic libs
add_custom_command(TARGET GFXMain POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		-E copy_directory
			$<TARGET_FILE_DIR:runic>
			$<TARGET_FILE_DIR:GFXMain>
		VERBATIM
		)
