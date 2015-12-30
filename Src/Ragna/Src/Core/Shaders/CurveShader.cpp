#include "CurveShader.hpp"

#include <sstream>

namespace Ragna {

// #############################################################################
// ### Ragna::CurveShader ######################################################
// #############################################################################

CurveShader::CurveShader()
{
	std::stringstream vert_stream;
	vert_stream << "\n"
		<< "#version 330\n"

		<< "layout(location = 0) in vec3 vert_model_space;\n"
		<< "layout(location = 1) in vec2 vert_uv;\n"

		// Output data; will be interpolated for each fragment.
		<< "out vec2 uv;\n"
		<< "uniform mat4 MVP;\n"

		<< "void main()\n"
		<< "{\n"
		<< "	gl_Position = MVP * vec4(vert_model_space, 1);\n"
		<< "	uv = vert_uv;\n"
		<< "}\n"
		<< "\n";
	vert_shader = vert_stream.str();


	std::stringstream frag_stream;
	frag_stream << "\n"
		<< "#version 330\n"

		// Ouput data
		<< "out vec4 color;\n"

		// Interpolated values from the vertex shaders
		<< "in vec2 uv;\n"

		// incoming color values
		<< "uniform vec4 obj_color;\n"
		
		<< "uniform bool is_positive_arc;\n"

		// main part
		<< "void main()\n"
		<< "{\n"
		<< "	float curve = pow(uv.x, 2) - uv.y;\n"
		<< "	bool paint = is_positive_arc ? curve <= 0 : curve >= 0;\n"
		<< "	if (paint) {\n"
		<< "		color = obj_color;\n"
		<< "	} else {\n"
		<< "		discard;\n"
		<< "	}\n"
		<< "}\n"
		<< "\n";

	frag_shader = frag_stream.str();

	// Create and compile our GLSL program from the shaders
	compileShaders(vert_shader, frag_shader);
}


CurveShader::~CurveShader()
{
}


} // Ragna namespace
