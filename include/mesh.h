#pragma once

#include "buffer.h"
#include "vao.h"
#include "valid.h"

namespace frank
{
	template <typename ... Args>
	class Mesh
	{
	public:
		void bind() const;

		void addVertex(Args&& ... args);

		template <typename T>
		void addVertices(T&& v);

		template <typename T>
		void addIndices(T&& i);

		template <typename V, typename I>
		void add(V&& vertices, I&& indices);

	private:
		Vao vao;
		mutable Valid isValid;
		Buffer<unsigned int> indexBuffer;
		Buffer<Args...> vertexBuffer;
	};
}

template <typename ... Args>
void frank::Mesh<Args...>::bind() const
{
	vao.bind();
	if (!isValid)
	{
		vertexBuffer.bind(GL_ARRAY_BUFFER);
		indexBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
		isValid.set(true);
	}
}

template <typename ... Args>
void frank::Mesh<Args...>::addVertex(Args&& ... args)
{
	vertexBuffer.addElement(std::forward<Args>(args)...);
}

template <typename ... Args>
template <typename T>
void frank::Mesh<Args...>::addVertices(T&& v)
{
	for (auto&& i : v)
	{
		addVertex(std::forward<Args>(i)...);
	}
}

template <typename ... Args>
template <typename T>
void frank::Mesh<Args...>::addIndices(T&& indices)
{
	for (auto&& i : indices)
	{
		indexBuffer.addElement(std::forward<unsigned int>(i));
	}
}

template <typename ... Args>
template <typename V, typename I>
void frank::Mesh<Args...>::add(V&& vertices, I&& indices)
{
	addVertices(std::forward<V>(vertices));
	addIndices(std::forward<I>(indices));
}