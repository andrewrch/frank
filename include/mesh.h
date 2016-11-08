#pragma once

#include "buffer.h"
#include "vao.h"
#include "valid.h"
#include <glm/glm.hpp>

template <typename T>
void configureAttrib(size_t N)
{
}

template <>
void configureAttrib<glm::vec3>(size_t N)
{
	glVertexAttribPointer(N, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

template <>
void configureAttrib<unsigned int>(size_t N)
{
	glVertexAttribPointer(N, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
}

namespace frank
{
	template <typename ... Args>
	class Mesh
	{
	public:
		void bind() const;

		template <typename T>
		void addVertex(T&& args);

		template <typename T>
		void addVertices(T&& v);

		template <typename T>
		void addIndices(T&& i);

		template <typename V, typename I>
		void add(V&& vertices, I&& indices);

	private:
		template <size_t N, typename Attrib, typename ... Attribs>
		void configureAttribs() const
		{
			configureAttrib<Attrib>(N);
			configureAttribs<N + 1, Attribs...>();
		}
		template <size_t N>
		void configureAttribs() const
		{
		}

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
		configureAttribs<0, Args...>();
		isValid.set(true);
	}
}

template <typename ... Args>
template <typename T>
void frank::Mesh<Args...>::addVertex(T&& vertex)
{
	vertexBuffer.addElement(std::forward<std::tuple<Args...>>(vertex));
}

template <typename ... Args>
template <typename T>
void frank::Mesh<Args...>::addVertices(T&& v)
{
	for (auto&& i : v)
	{
		//addVertex(std::forward<Args>(i)...);
		addVertex(std::forward<std::tuple<Args...>>(i));
	}
}

template <typename ... Args>
template <typename T>
void frank::Mesh<Args...>::addIndices(T&& indices)
{
	for (auto&& i : indices)
	{
		indexBuffer.addElement(std::forward<std::tuple<unsigned int>>(i));
	}
}

template <typename ... Args>
template <typename V, typename I>
void frank::Mesh<Args...>::add(V&& vertices, I&& indices)
{
	addVertices(std::forward<V>(vertices));
	addIndices(std::forward<I>(indices));
}