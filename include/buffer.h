#pragma once

#include <memory>
#include <handle.h>
#include <GL/glew.h>
#include <vector>
#include <utility>
#include <tuple>

template <size_t i>
struct ElementUnpackerImpl
{
	template <typename V, typename E>
	void operator()(V&& v, E&& e)
	{
		std::get<i>(v).emplace_back(std::get<i>(e));
		ElementUnpackerImpl<i - 1> next;
		next(v, e);
	}
};

template <>
struct ElementUnpackerImpl<0>
{
	template <typename V, typename E>
	void operator()(V&& v, E&& e)
	{
		std::get<0>(v).push_back(std::get<0>(e));
	}
};

template <size_t i>
struct ElementUnpacker
{
	template <typename V, typename E>
	void operator()(V&& v, E&& e)
	{
		ElementUnpackerImpl<i - 1> unpacker;
		unpacker(v, e);
	}
};

namespace frank
{
template <typename ... Args>
class FRANK_EXPORT Buffer
{
public:
	template <typename T>
	void addElement(T&& t)
	{
		ElementUnpacker<sizeof...(Args)> unpacker;
		unpacker(elements, t);
	}


	void bind(GLenum target) const
	{
		handle.bind(target);
	}

private:

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