#pragma once
#include "Object.h"

class Shield : public Object
{

public:
	Shield(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer*);
	~Shield();

	virtual void poll_events(SDL_Event& event) {};


};

