enum Type
{
	FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	EXCLUSIVE_FULLSCREEN = SDL_WINDOW_DESKTOP
};

class Window
{
	const char title[];
	int x;
	int y;
	int w;
	int h;
	Type type;
	
	Window()
	{
		this.title = title;
		this.x = x;
		this.y = y;
		this.w = w;
		this.h = h;
		this.type = type;
	}
};