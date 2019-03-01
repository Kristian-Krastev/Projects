#pragma once
#include "Object.h"


class Projectile : public Object
{

public:
	Projectile(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer*);
	~Projectile();

	virtual void poll_events(SDL_Event& e) {}
};

