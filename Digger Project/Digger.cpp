#include "Digger.h"



Digger::Digger(int w, int h, int x, int y, const std::string & img_path, SDL_Renderer * r):
	Object(w, h, x, y, img_path, r)
{
}

Digger::Digger(): Object()
{
}

Digger::~Digger()
{
}

bool Digger::is_left_side()
{
	return (img_name == "face.png");
}

bool Digger::is_right_side()
{
	return (img_name == "face_r.png");
}

void Digger::change_side(const std::string& img_path, SDL_Renderer* renderer) {

	SDL_DestroyTexture(texture);
	auto surface = IMG_Load(img_path.c_str());

	if (!surface) {
		std::cerr << "Failed to create surface\n";
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		std::cerr << "Failed to create surface\n";
	}
	SDL_FreeSurface(surface);

	this->img_name = img_path;
}

void Digger::draw(SDL_Renderer * renderer)
{
		SDL_Rect rect = { x * 80, y * 80, width, height };

		SDL_RenderCopy(renderer, texture, nullptr, &rect);

}

void Digger::poll_events(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_DOWN:
			(y + 1)*80 < 850 ? y += 1 : y;
			break;
		case SDLK_UP:
			(y - 1) >= 0 ? y -= 1 : y;
			break;
		case SDLK_LEFT:
			(x - 1) >= 0 ? x -= 1 : x;
			break;
		case SDLK_RIGHT:
			(x + 1)*80 < 1650 ? x += 1 : x;
			break;
		default: break;
		}
	}

}
