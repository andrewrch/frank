#include "shader.h"

int test()
{
	frank::Shader s(GL_FRAGMENT_SHADER);
	s.addSource("hello", "how are you?");
	s.compile();
	return 1;
}