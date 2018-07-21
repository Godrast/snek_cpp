#ifndef VERTEX_SHADERS_HPP
#define VERTEX_SHADERS_HPP

class VertexShaders {
	const char * general3DShader;
	const char * general3DShaderTexture;

public:
	VertexShaders();
	const char * getGeneral3DShader();
	const char * getGeneral3DShaderTexture();
};

#endif // !VErtex_SHADERS_HPP
