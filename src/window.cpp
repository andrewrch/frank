#include "window.h"
#include <stdexcept>

#include "GLFW/glfw3.h"

namespace frank
{
	Window::Window(int width, int height)
	{
		window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, "My Title", NULL, NULL), glfwDestroyWindow);
		if (!window)
		{
			throw std::runtime_error("Can not create window");
		}
	}

	Window::~Window()
	{
	}
}
