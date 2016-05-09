#pragma once

#include <gl/glew.h>
#include <vector>
#include <memory>
#include "handle.h"

namespace frank
{
	namespace detail
	{
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
	}

	using ShaderHandle = Handle<detail::CreateShader, detail::DeleteShader>;
	class Shader : public ShaderHandle
	{
	public:
		Shader() = delete;

		static Shader FromFile(GLenum type, const std::string& filename);
		template <typename ... Strings>
		static Shader FromSource(GLenum type, const Strings& ... source)
		{
			Shader s(type);
			s.addSource(source...);
			return s;
		}

		operator std::shared_ptr<Shader>() const;

		template <typename... Strings>
		void addSource(const std::string& src, Strings... more)
		{
			source.push_back(src);
			addSource(more...);
		}

		void compile();
		
	private:
		Shader(GLenum type);		
		void addSource() {}

		std::vector<std::string> source;
	};
}