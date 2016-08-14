#include "shader.h"
#include "shader_program.h"
#include "window.h"

#include <memory>

using namespace frank;

int test()
{
	ShaderProgram s(Shader::FromSource(GL_FRAGMENT_SHADER, "hello"),
					Shader::FromFile(GL_VERTEX_SHADER, "hello"));

	Window window(640, 480);
	return 1;
}