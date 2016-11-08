#include "shader.h"
#include "shader_program.h"
#include "buffer.h"
#include "window.h"
#include "mesh.h"

#include "GL/wglew.h"
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <array>

using namespace frank;

#define GLSL(shader) #shader

const std::string shaderVersion = "#version 330\n";

const char* vertex = GLSL(
in vec3 pos;
in vec4 colour;

uniform mat4 mv;
uniform mat4 proj;

out vec4 vertex_pos;
out vec4 vertex_colour;
void main()
{
	vertex_colour = colour;
	vertex_pos = proj * mv * vec4(pos, 1);
}
);

const char* frag = GLSL(
in vec4 vertex_colour;
out vec4 frag_colour;
void main()
{
	frag_colour = vec4(1, 0, 0, 1);
}
);

int main()
{
	Window window(640, 480);
	glewInit();
	ShaderProgram s(Shader::FromSource(GL_FRAGMENT_SHADER, shaderVersion, frag),
		Shader::FromSource(GL_VERTEX_SHADER, shaderVersion, vertex));

	Mesh<glm::vec3, glm::vec4> m;
	m.add(std::array<std::tuple<glm::vec3, glm::vec4>, 4>{
	    std::make_tuple(glm::vec3(-1, -1, 0), glm::vec4(1, 1, 1, 1)),
		std::make_tuple(glm::vec3(-1,  1, 0), glm::vec4(1, 1, 1, 1)),
		std::make_tuple(glm::vec3( 1, -1, 0), glm::vec4(1, 1, 1, 1)),
		std::make_tuple(glm::vec3( 1,  1, 0), glm::vec4(1, 1, 1, 1))
	},
		std::array<unsigned int, 6>{ 0, 1, 2, 2, 1, 3});

	m.bind();
	s.bind();


}