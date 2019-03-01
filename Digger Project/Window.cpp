#include "Window.h"

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {	//if it failed
		std::cerr << "Failed to initialize window\n";
		return false;
	}

	window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_RESIZABLE);

	if (window == nullptr) {
		std::cerr << "Failed to create window\n";
		return false;
	}
	return true;
}

Window::Window(const std::string & _title, int _width, int _height) :
	title(_title), width(_width), height(_height)
{
	if (!init()) {
		closed = true;
	}
}

Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::poll_events(SDL_Event& event)
{

	switch (event.type) {
	case SDL_QUIT:
		closed = true; break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			closed = true; break;

		default: break;
		}
	default: break;
	}



}

void Window::draw(SDL_Renderer* renderer) const
{
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}
