#include "window.h"

#include <stdexcept>
#include <functional>

#include "GLFW/glfw3.h"

namespace frank
{

class WindowImpl
{
public:
	WindowImpl(int w, int h, const std::string& title);

	static void keyboardCB(GLFWwindow*, int, int, int, int);
	static void mouseButtonCB(GLFWwindow*, int, int, int);
	static void mousePosCB(GLFWwindow*, double, double);
	static void fileDropCB(GLFWwindow*, int, const char**);
	static void errorCB(int, const char*);

	GLFWwindow* getWindow();
private:
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window;
};


WindowImpl::WindowImpl(int w, int h, const std::string& title)
	: window(glfwCreateWindow(w, h, title.c_str(), NULL, NULL), glfwDestroyWindow)
{
	glfwSetWindowUserPointer(window.get(), this);
}

GLFWwindow* WindowImpl::getWindow()
{
	return window.get();
}

void WindowImpl::keyboardCB(GLFWwindow* w, int, int, int, int)
{
	WindowImpl *window = static_cast<WindowImpl*>(glfwGetWindowUserPointer(w));
	//w->render();
}

void WindowImpl::mouseButtonCB(GLFWwindow*, int, int, int)
{
}

void WindowImpl::mousePosCB(GLFWwindow*, double, double)
{
}

void WindowImpl::fileDropCB(GLFWwindow*, int, const char**)
{
}

void WindowImpl::errorCB(int, const char*)
{
}

Window::Window(int width, int height)
{
	impl = std::make_unique<WindowImpl>(width, height, "Window");
	// Setup callbacks	
	glfwSetErrorCallback(&WindowImpl::errorCB);
	glfwSetKeyCallback(impl->getWindow(), &WindowImpl::keyboardCB);
	glfwSetDropCallback(impl->getWindow(), &WindowImpl::fileDropCB);
	glfwSetMouseButtonCallback(impl->getWindow(), &WindowImpl::mouseButtonCB);
	glfwSetCursorPosCallback(impl->getWindow(), &WindowImpl::mousePosCB);
}

void Window::loop()
{
	while (!glfwWindowShouldClose(impl->getWindow()))
	{
		glfwSwapBuffers(impl->getWindow());
	}
}

Window::~Window()
{
}

} // namespace frank
