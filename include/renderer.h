#pragma once

class Mesh;

namespace frank
{
	class Renderer
	{
	public:
		template <typename ... Args>
		void Draw(Mesh<Args...>&& mesh);
	};
}

template <typename ... Args>
frank::Renderer::Draw(Mesh<Args...>&& mesh)
{
	mesh.bind();
	glDrawElements();
}