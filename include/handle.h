#pragma once

#include <GL\glew.h>
#include <memory>
#include <map>

template <typename Creator, typename Binder, typename Deleter>
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

	template <typename ... Args>
	void bind(Args&& ... data) const
	{
		Binder()(handle, data...);
	}
	
	template <typename ... Args>
	void unBind(Args&& ... data) const
	{
		Binder()(0, std::forward<Args>(data...));
	}

	GLuint get() const
	{
		return handle;
	}

private:
	GLuint handle;
};
