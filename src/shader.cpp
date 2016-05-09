#include "shader.h"
#include <fstream>

namespace frank
{

Shader::Shader(GLenum type)
	: ShaderHandle(type)
{
}

Shader Shader::FromFile(GLenum type, const std::string& filename)
{
	std::string source;
	{
		std::ifstream f(filename);
		source.assign(std::istreambuf_iterator<char>(f),
					  std::istreambuf_iterator<char>());
		f.close();
	}
	return Shader::FromSource(type, source);
}

Shader::operator std::shared_ptr<Shader>() const 
{
	return std::make_shared<Shader>(*this);
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
}

}