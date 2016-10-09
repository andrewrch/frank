#pragma once


#include <gl/glew.h>
#include <vector>
#include <memory>
#include "handle.h"
#include "frank.h"

namespace frank
{
	class FRANK_EXPORT Shader
	{
	public:
		Shader(GLenum type);
		~Shader() {}
		static std::unique_ptr<Shader> FromFile(GLenum type, const std::string& filename);

		template <typename ... Strings>
		static std::unique_ptr<Shader> FromSource(GLenum type, Strings&& ... source)
		{
			auto s = std::make_unique<Shader>(type);
			s->addSource(std::forward<Strings>(source)...);
			return s;
		}

		template <typename T>
		void addSource(T&& src)
		{
			source.emplace_back(std::forward<T>(src));
		}

		template <typename T, typename... Ts>
		void addSource(T&& src, Ts&&... more)
		{
			source.emplace_back(std::forward<T>(src));
			addSource(std::forward<Ts>(more)...);
		}

		void compile();

		GLuint getHandle() const;
		
	private:		
		std::vector<std::string> source;



		struct CreateShader
		{
			GLuint operator()(GLenum type)
			{
				return glCreateShader(type);
			}
		};

		struct DeleteShader
		{
			void operator()(GLuint handle)
			{
				glDeleteShader(handle);
			}
		};
		Handle<CreateShader, DeleteShader> handle;
	};
}