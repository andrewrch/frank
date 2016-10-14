#pragma once

#include "handle.h"

namespace frank
{
	class Vao
	{
	public:
		void bind() const
		{
			handle.bind();
		}
	private:
		struct CreateVao
		{
			unsigned int operator()()
			{
				unsigned int h;
				glCreateVertexArrays(1, &h);
				return h;
			}
		};
		struct DeleteVao
		{
			void operator()(unsigned int h)
			{
				glDeleteVertexArrays(1, &h);
			}
		};
		struct BindVao
		{
			void operator()(unsigned int h)
			{
				glBindVertexArray(h);
			}
		};
		Handle<CreateVao, BindVao, DeleteVao> handle;
	};
}