#pragma once
#include "Object.h"

class Dirt: public Object {

public:
	Dirt(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer*);
	~Dirt();

public:

	virtual void poll_events(SDL_Event& event) {};
};
