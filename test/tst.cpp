#include "shader.h"
#include "shader_program.h"
#include "vertex_buffer.h"
#include "window.h"

#include "GL/wglew.h"
#include <glm/glm.hpp>
#include <memory>

using namespace frank;

#define GLSL(shader) #shader

const char* vertex = GLSL(
#version 330\n
in vec3 pos;
in vec3 norm;

uniform mat4 mv;
uniform mat4 proj;

out vec4 vertex_pos;
void main()
{
	vertex_pos = proj * mv * vec4(pos, 1);
}
);

const char* frag = GLSL(
#version 330\n
out vec4 frag_colour;
void main()
{
	frag_colour = vec4(1, 1, 1, 1);
}
);

int main()
{
	Window window(640, 480);
	glewInit();
	ShaderProgram s(Shader::FromSource(GL_FRAGMENT_SHADER, frag),
					Shader::FromSource(GL_VERTEX_SHADER, vertex));

	VertexBuffer<glm::vec3, glm::vec3, glm::vec4> v;
	v.addVertex(glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec4(0, 0, 0, 1));

	v.addVertex(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 1 }, glm::vec4{ 0, 0, 0, 1 });
	return 1;
}