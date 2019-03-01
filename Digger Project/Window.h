#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

class Window
{
private:
	std::string title;
	int width;
	int height;

	bool closed = false;

private:
	bool init();

public:
	Window(const std::string& _title, int _width, int _height);
	~Window();

public:
	SDL_Window* window = nullptr;

	bool is_closed() const {
		return closed;
	}

	void poll_events(SDL_Event&);
	void draw(SDL_Renderer* r)const;
};