#include "vertexShaders.hpp"

VertexShaders::VertexShaders() {
	general3DShader = "#version 330 core\n"
		"// Input vertex data, different for all executions of this shader.\n"
		"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
		"// Values that stay constant for the whole mesh.\n"
		"uniform mat4 MVP;\n"
		"void main() {\n"
		"// Output position of the vertex, in clip space : MVP * position\n"
		"gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n"
		"}";

	general3DShaderTexture = "#version 330 core\n"
		"// Input vertex data, different for all executions of this shader.\n"
		"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
		"layout(location = 1) in vec2 texCoord;\n"
		"layout(location = 2) in vec2 uvCoord;\n"
		"// Values that stay constant for the whole mesh.\n"
		"out vec2 out_texCoord;\n"
		"out vec2 out_uvCoord; \n"
		"uniform mat4 MVP;\n"
		"void main() {\n"
		"// Output position of the vertex, in clip space : MVP * position\n"
		"out_uvCoord  = uvCoord; \n"
		"out_texCoord = vec2(texCoord.x, texCoord.y);\n"
		"gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n"
		"}";

}

const char * VertexShaders::getGeneral3DShader() {
	return general3DShader;
}

const char * VertexShaders::getGeneral3DShaderTexture() {
	return general3DShaderTexture;
}