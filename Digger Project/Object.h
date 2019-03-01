#pragma once

#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Object
{

private:
	bool init();

protected:
	int width;
	int height;
	int x, y;
	std::string img_name;

public:
	SDL_Texture* texture = nullptr;

public:
	Object(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer*);
	Object();
	virtual ~Object();


public:
	virtual void draw(SDL_Renderer*)const;
	virtual void poll_events(SDL_Event& event) = 0;

	const int get_x()const { return x; };
	const int get_y()const { return y; };
	const std::string get_name()const { return img_name; }

};

