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
		ShaderProgram(Shaders&& ... s)
		{
			initShaders(std::forward<Shaders>(s)...);
			GLuint program = this->getHandle();
			for (auto&& s : shaders)
			{
				s->compile();
				glAttachShader(program, s->getHandle());
			}

			link();

			for (auto&& s : shaders)
			{
				glDetachShader(program, s->getHandle());
			}
			shaders.clear();
		}

	private:
		template <typename S>
		void initShaders(S&& s)
		{
			shaders.emplace_back(std::forward<S>(s));
		}
		template <typename S, typename ... Ss>
		void initShaders(S&& first, Ss&& ... rest)
		{
			shaders.emplace_back(std::forward<S>(first));
			initShaders(std::forward<Ss>(rest)...);
		}

		void link()
		{
			GLuint program = this->getHandle();
			glLinkProgram(program);
			GLint linked;
			glGetProgramiv(program, GL_LINK_STATUS, &linked);
			if (!linked)
			{
				GLint len = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
				std::vector<GLchar> infoLog(len);
				glGetProgramInfoLog(program, len, &len, infoLog.data());
			}
		}

		std::vector<std::unique_ptr<Shader>> shaders;
	};
}
