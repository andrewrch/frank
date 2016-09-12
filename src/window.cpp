#include "window.h"

#include <stdexcept>
#include <functional>

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <assert.h>


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
	typedef std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> WindowPtr;
	WindowPtr window;
};

WindowImpl::WindowImpl(int w, int h, const std::string& title)	
	: window(NULL, glfwDestroyWindow)
{	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = WindowPtr(glfwCreateWindow(w, h, title.c_str(), NULL, NULL), glfwDestroyWindow);
	glfwMakeContextCurrent(window.get());
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	assert(err == GL_NO_ERROR);
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
	: impl(new WindowImpl(width, height, "Window"))
{
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
