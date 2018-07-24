#include "fragmentShaders.hpp"

FragmentShaders::FragmentShaders() {
	snakeShader = "#version 330 core\n"
		"// Output data\n"
		"out vec3 color;\n"
		"void main() {\n"

		"color = vec3(0, 0.8, 0);\n"
		"}";

	appleShader = "#version 330 core\n"
		"// Output data\n"
		"out vec3 color;\n"
		"void main() {\n"

		"color = vec3(0.8, 0, 0);\n"
		"}";
	wallShader = "#version 330 core\n"
		"// Output data\n"
		"out vec3 color;\n"
		"void main() {\n"

		"color = vec3(0.6, 0.6, 0.6);\n"
		"}";
}

const char * FragmentShaders::getSnakeShader() {
	return snakeShader;
}

const char * FragmentShaders::getAppleShader() {
	return appleShader;
}

const char * FragmentShaders::getWallShader() {
	return wallShader;
}