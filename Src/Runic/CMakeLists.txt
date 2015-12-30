################################################################################
### Runic Library ##############################################################
################################################################################

# create runic shared library
add_library(runic SHARED

			# poly2tri
			../3thParty/poly2tri/poly2tri/common/shapes.cc
			../3thParty/poly2tri/poly2tri/sweep/advancing_front.cc
			../3thParty/poly2tri/poly2tri/sweep/cdt.cc
			../3thParty/poly2tri/poly2tri/sweep/sweep.cc
			../3thParty/poly2tri/poly2tri/sweep/sweep_context.cc

			# Runic
			Src/RunicBinary.cpp
			Src/RunicCmapTable.cpp
			Src/RunicEndian.cpp
			Src/RunicExceptions.cpp
			Src/RunicFont.cpp
			Src/RunicGlyph.cpp
			Src/RunicGlyphTable.cpp
			Src/RunicHeadTable.cpp
			Src/RunicLoader.cpp
			Src/RunicLocaTable.cpp
			Src/RunicMaxpTable.cpp
			Src/RunicNameTable.cpp
			Src/RunicRange.cpp
			Src/RunicTriangulator.cpp
			Src/RunicTypes.cpp
			)

# add cxx compile target
SET_TARGET_PROPERTIES(runic PROPERTIES LINKER_LANGUAGE CXX)

# include runic headers for each project which is using it
target_include_directories (runic PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Src")


################################################################################
# Unit Tests ###################################################################
################################################################################

add_executable(RunicUintTest Test/RunicUnitTest.cpp)

# Standard linking to gtest stuff.
target_link_libraries(RunicUintTest LINK_PUBLIC gtest gtest_main)

# Extra linking for the project.
target_link_libraries(RunicUintTest LINK_PUBLIC runic)


# copy gtest libs
add_custom_command(TARGET RunicUintTest POST_BUILD
					COMMAND ${CMAKE_COMMAND}
					-E copy_directory
						$<TARGET_FILE_DIR:gtest>
						$<TARGET_FILE_DIR:RunicUintTest>
					VERBATIM
					)


# copy gtest_main libs
add_custom_command(TARGET RunicUintTest POST_BUILD
					COMMAND ${CMAKE_COMMAND}
					-E copy_directory
						$<TARGET_FILE_DIR:gtest_main>
						$<TARGET_FILE_DIR:RunicUintTest>
					VERBATIM
					)


################################################################################
### Runic Test #################################################################
################################################################################

# create RunicTest exe for testing
add_executable(RunicTest Test/RunicTest.cpp)

add_dependencies(RunicTest runic)

target_link_libraries(RunicTest LINK_PUBLIC runic ${SDL2_LIBRARY} ${SDL2IMAGE_LIBRARIES})

if(WIN32)
	# set_target_properties(RunicTest PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:msvcrt.lib")
	set_target_properties(RunicTest PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:msvcrt.lib")
	set_target_properties(RunicTest PROPERTIES STATIC_LIBRARY_FLAGS "/NODEFAULTLIB:msvcrt.lib")
endif(WIN32)

# copy SDL2 libs
add_custom_command(TARGET RunicTest POST_BUILD
					COMMAND ${CMAKE_COMMAND}
					-E copy_directory
						"${RUNTIME_SDL2}"
						$<TARGET_FILE_DIR:RunicTest>
					VERBATIM
					)

# copy Fonts
add_custom_command(TARGET RunicTest POST_BUILD
					COMMAND ${CMAKE_COMMAND}
					-E copy_directory
						"${FONTS}"
						"$<TARGET_FILE_DIR:RunicTest>/Data"
					VERBATIM
					)
