#include <cstring>

#include "Window.hpp"

Window::Window(char title[], int x, int y, int w, int h, WindowDisplayType window_display_type)
{
	strcpy(this->title, title);
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->window_display_type = window_display_type;
}