#include "Text.h"
#include <iostream>


Text::Text(const std::string & font_path, int font_size, const std::string & message_text, const SDL_Color & _color, SDL_Renderer* renderer):
	text(message_text), color(_color), font(TTF_OpenFont(font_path.c_str(), font_size))
{
	text_texture = loadFont(font, font_size, message_text, color, renderer);
	SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);

}

Text::~Text()
{
}

void Text::display(int x, int y, SDL_Renderer* renderer)
{
	std::string temp_txt = text;

	text.append(std::to_string(score));
	text_texture = loadFont(font, 50, text, color, renderer);
	SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
	
	text_rect.x = x;
	text_rect.y = y;
	SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);
	text = temp_txt;
}

SDL_Texture * Text::loadFont(TTF_Font * font_path, int font_size, const std::string & message_text, const SDL_Color & _color, SDL_Renderer* renderer)
{
	auto text_surface = TTF_RenderText_Solid(font_path, message_text.c_str(), _color);
	if (!text_surface) {
		std::cerr << "Failed to create text surface\n";
	}
	auto _text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (!_text_texture) {
		std::cerr << "Failed to create text texture\n";
	}
	SDL_FreeSurface(text_surface);
	return _text_texture;
}
