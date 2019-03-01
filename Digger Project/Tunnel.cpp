#include "Tunnel.h"



Tunnel::Tunnel(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer* render) :
	Object(w, h, x, y, img_path, render)
{
}


Tunnel::~Tunnel()
{
}
