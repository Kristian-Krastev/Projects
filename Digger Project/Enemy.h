#pragma once
#include "Object.h"

class Enemy : public Object
{

public:
	Enemy(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer*);
	~Enemy();

public:
	void move(const std::string& direction);

	virtual void poll_events(SDL_Event& event) {};

};

