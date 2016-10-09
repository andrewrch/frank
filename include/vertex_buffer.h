#pragma once

#include <memory>
#include <handle.h>
#include <GL/glew.h>
#include <vector>
#include <utility>

namespace frank
{
template <typename ... Args>
class FRANK_EXPORT VertexBuffer
{
public:
	template <typename ... Args>
	void addVertex(Args&&... args)
	{
		addVertexHelper<0>(std::forward<Args>(args)...);
	}

private:
	template <int i, typename T, typename ... Args>
	void addVertexHelper(T&& t, Args&&... args)
	{
		auto& v = std::get<i>(vertices);
		v.emplace_back(std::forward<T>(t));
		addVertexHelper<i + 1>(std::forward<Args>(args)...);
	}
	template <int i, typename T>
	void addVertexHelper(T&& t)
	{
		auto& v = std::get<i>(vertices);
		v.push_back(std::forward<T>(t));
	}
	// Vertices aren't interleaved so we can build
	// by variadic template args
	std::tuple<std::vector<Args>...> vertices;

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
	Handle<CreateBuffer, DeleteBuffer> handle;

};
}