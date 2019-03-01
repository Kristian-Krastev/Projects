#include "Dirt.h"



Dirt::Dirt(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer* render):
	Object(w, h, x, y, img_path, render)
{
}


Dirt::~Dirt()
{
}
