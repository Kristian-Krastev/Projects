#include "Projectile.h"



Projectile::Projectile(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer* renderer):
	Object(w, h, x, y, img_path, renderer)
{
}


Projectile::~Projectile()
{
}
