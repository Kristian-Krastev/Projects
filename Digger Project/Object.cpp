#include "Object.h"
#include <SDL_image.h>

bool Object::init()
{
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cerr << "Failed to initialize SDL image\n";
		return false;
	}

	return true;
}

Object::Object(int w, int h, int _x, int _y, const std::string & img_path, SDL_Renderer* renderer) :
	width(w), height(h), x(_x), y(_y)
{
	if (!init()) {
		throw std::exception("Couldn't init image\n");
	}

	auto surface = IMG_Load(img_path.c_str());

	if (!surface) {
		std::cerr << "Failed to create surface\n";
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		std::cerr << "Failed to create surface\n";
	}
	SDL_FreeSurface(surface);

	img_name = img_path;
}

Object::Object():width(0), height(0), x(0), y(0)
{
	texture = nullptr;
}

void Object::draw(SDL_Renderer* renderer) const
{
	SDL_Rect rect = { x * 80, y * 80, width, height };
	if (texture) {

		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}
}

Object::~Object()
{

	SDL_DestroyTexture(texture);
}
