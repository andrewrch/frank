#pragma once

#include <memory>

class GLFWwindow;

namespace frank
{
	class Window
	{
	public:
		Window(int width, int height);
		~Window();
	private:
		void ErrorCallback();
		std::shared_ptr<GLFWwindow> window;
	};
}