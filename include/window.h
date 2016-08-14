#pragma once

#include "frank.h"
#include <memory>

namespace frank
{

class WindowImpl;

class FRANK_EXPORT Window
{
public:
	Window(int width, int height);
	~Window();
	void loop();
private:
	std::unique_ptr<WindowImpl> impl;
};

}