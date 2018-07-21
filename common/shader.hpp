#ifndef SHADER_HPP
#define SHADER_HPP

GLuint LoadShadersExternal(const char * vertex_file_path, const char * fragment_file_path);
GLuint LoadShaders(const char * vertex_shader, const char * fragment_shader);

#endif