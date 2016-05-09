#pragma once

#include "shader.h"

namespace frank
{
	namespace detail
	{
		struct CreateShaderProgram
		{
			GLuint operator()()
			{
				return glCreateProgram();
			}
		};
		struct DeleteShaderProgram
		{
			void operator()(GLint p)
			{
				glDeleteProgram(p);
			}
		};
	}
	using ShaderProgramHandle = Handle<detail::CreateShaderProgram, detail::DeleteShaderProgram>;
	class ShaderProgram : public ShaderProgramHandle
	{
	public:
		template <typename ... Shaders>
		ShaderProgram(Shaders& ... s)
			: shaders{s...}
		{
			GLuint program = this->getHandle();
			for (auto& s : shaders)
			{
				s->compile();
				glAttachShader(program, s->getHandle());
			}
			glLinkProgram(program);
			for (auto& s : shaders)
			{
				glDetachShader(program, s->getHandle());
			}
			shaders.clear();
		}

	private:
		std::vector<std::shared_ptr<Shader>> shaders;
	};
}
