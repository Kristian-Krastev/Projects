#pragma once
#include "Object.h"

class Diamond : public Object
{

public:
	Diamond(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer*);
	~Diamond();

	virtual void poll_events(SDL_Event& event) {};
};

