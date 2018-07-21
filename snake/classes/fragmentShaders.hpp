#ifndef FRAGMENT_SHADERS_HPP
#define FRAGMENT_SHADERS_HPP

class FragmentShaders {
	const char * snakeShader;
	const char * appleShader;
	const char * wallShader;

public:
	FragmentShaders();
	const char * getSnakeShader();
	const char * getAppleShader();
	const char * getWallShader();
};
#endif // !FRAGMENT_SHADERS_HPP
