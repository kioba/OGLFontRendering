################################################################################
### Ragna Library ##############################################################
################################################################################

add_library (ragna SHARED
				# utils
				Src/Core/Molten.cpp
				Src/Core/Core.cpp
				Src/Core/Rect.cpp
				Src/Core/Glyph.cpp

				# opengl
				Src/Core/Object.cpp
				Src/Core/Event.cpp
				Src/Core/Shaders/Shader.cpp
				Src/Core/Shaders/BasicShader.cpp
				Src/Core/Shaders/TextureShader.cpp
				Src/Core/Shaders/CurveShader.cpp

				# Ragna Layouts
				Src/Layout.cpp
				Src/CardLayout.cpp

				# Ragna Materials
				Src/Material.cpp
				Src/View.cpp
				Src/Panel.cpp
				Src/Menu.cpp
				Src/Button.cpp
				Src/Image.cpp
				Src/Text.cpp

				)

SET_TARGET_PROPERTIES(ragna PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(ragna LINK_PUBLIC
						${GLEW_LIBRARY}
						${OPENGL_LIBRARIES}
						${SDL2_LIBRARY}
						${SDL2IMAGE_LIBRARIES}
						runic
						)

target_include_directories (ragna PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Src")


# copy SDL2 libs
add_custom_command(TARGET ragna POST_BUILD
					COMMAND ${CMAKE_COMMAND}
					-E copy_directory
						"${RUNTIME_SDL2}"
						$<TARGET_FILE_DIR:ragna>
					VERBATIM
					)


# copy GLEW libs
add_custom_command(TARGET ragna POST_BUILD
					COMMAND ${CMAKE_COMMAND}
					-E copy_directory
						"${RUNTIME_GLEW}"
						$<TARGET_FILE_DIR:ragna>
					VERBATIM
					)


# copy runic libs
add_custom_command(TARGET ragna POST_BUILD
					COMMAND ${CMAKE_COMMAND}
					-E copy_directory
						$<TARGET_FILE_DIR:runic>
						$<TARGET_FILE_DIR:ragna>
					VERBATIM
					)


################################################################################
### ragna Library Unit Test ####################################################
################################################################################

add_executable(RagnaUnitTest
				Test/RagnaUnitTest.cpp
				Test/CardLayoutTest.cpp
				Test/RectTest.cpp
				)

# Standard linking to gtest stuff.
target_link_libraries(RagnaUnitTest gtest gtest_main ragna)

# copy gtest libs
add_custom_command(TARGET ragna POST_BUILD
					COMMAND ${CMAKE_COMMAND}
					-E copy_directory
						$<TARGET_FILE_DIR:gtest>
						$<TARGET_FILE_DIR:ragna>
					VERBATIM
					)


# copy gtest_main libs
add_custom_command(TARGET ragna POST_BUILD
					COMMAND ${CMAKE_COMMAND}
					-E copy_directory
						$<TARGET_FILE_DIR:gtest_main>
						$<TARGET_FILE_DIR:ragna>
					VERBATIM
					)
