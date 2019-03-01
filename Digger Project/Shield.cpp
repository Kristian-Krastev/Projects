#include "Shield.h"



Shield::Shield(int w, int h, int _x, int _y, const std::string & img_path, SDL_Renderer* renderer):
	Object(w, h, _x, _y, img_path, renderer)
{
}


Shield::~Shield()
{
}
