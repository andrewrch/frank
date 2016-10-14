#pragma once

#include <memory>
#include <handle.h>
#include <GL/glew.h>
#include <vector>
#include <utility>

namespace frank
{
template <typename ... Args>
class FRANK_EXPORT Buffer
{
public:
	template <typename ... Args>
	void addElement(Args&&... args)
	{
		addElementHelper<0>(std::forward<Args>(args)...);
	}
	void bind(GLenum target) const
	{
		handle.bind(target);
	}

private:
	template <int i, typename T, typename ... Args>
	void addElementHelper(T&& t, Args&&... args)
	{
		auto& v = std::get<i>(elements);
		v.emplace_back(std::forward<T>(t));
		addElementHelper<i + 1>(std::forward<Args>(args)...);
	}
	template <int i, typename T>
	void addElementHelper(T&& t)
	{
		auto& v = std::get<i>(elements);
		v.emplace_back(std::forward<T>(t));
	}
	// Vertices aren't interleaved so we can build
	// by variadic template args
	std::tuple<std::vector<Args>...> elements;

	struct CreateBuffer
	{
		GLuint operator()()
		{
			GLuint buffer;
			glGenBuffers(1, &buffer);
			return buffer;			
		}
	};
	struct DeleteBuffer
	{
		void operator()(GLuint handle)
		{
			glDeleteBuffers(1, &handle);
		}
	};
	struct BindBuffer
	{
		void operator()(GLuint handle, GLenum target)
		{
			glBindBuffer(target, handle);
		}
	};
	Handle<CreateBuffer, BindBuffer, DeleteBuffer> handle;

};
}