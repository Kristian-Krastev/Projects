#pragma once
#include "Object.h"

class Tunnel : public Object
{

public:
	Tunnel(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer*);
	~Tunnel();

	virtual void poll_events(SDL_Event& event) {};

};

