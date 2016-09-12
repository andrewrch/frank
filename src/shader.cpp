#include "shader.h"
#include <fstream>

namespace frank
{

Shader::Shader(GLenum type)
	: ShaderHandle(type)
{
}

std::unique_ptr<Shader> Shader::FromFile(GLenum type, const std::string& filename)
{
	std::string source;
	{
		std::ifstream f(filename);
		source.assign(std::istreambuf_iterator<char>(f),
					  std::istreambuf_iterator<char>());
		f.close();
	}
	return Shader::FromSource(type, std::move(source));
}

void Shader::compile()
{
	GLuint shader = this->getHandle();
	std::vector<const char*> ptrs;
	for (auto& s : source)
	{
		ptrs.push_back(s.data());
	}
	glShaderSource(shader, ptrs.size(), ptrs.data(), NULL);
	glCompileShader(shader);
	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		std::vector<GLchar> errorLog(len);
		glGetShaderInfoLog(shader, len, &len, errorLog.data());

	}
}

}