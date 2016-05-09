#pragma once

#include <GL\glew.h>
#include <memory>
#include <map>

template <typename Creator, typename Deleter>
class Handle
{
public:
	template <typename ... Data>
	Handle(Data... data)
		: handle(Creator()(data...))
	{
	}

	~Handle()
	{
		Deleter()(handle);
	}

	GLuint getHandle()
	{
		return handle;
	}

private:
	GLuint handle;
};
