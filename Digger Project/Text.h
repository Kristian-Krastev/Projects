#pragma once
#include <SDL_ttf.h>
#include <SDL.h>

#include <string>


class Text
{
private:
	size_t score = 0;
	std::string text;
	SDL_Color color;

	TTF_Font * font = nullptr;
	SDL_Texture* text_texture = nullptr;
	SDL_Rect text_rect;

public:
	Text(const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color, SDL_Renderer* renderer);
	~Text();

	size_t get_score()const { return score; }
	void add_to_Score(size_t points) { score += points; }
	void reset_score() { score = 0; }
	void display(int x, int y, SDL_Renderer* renderer);
	static SDL_Texture* loadFont(TTF_Font * font_path, int font_size, const std::string& message_text, const SDL_Color& color, SDL_Renderer*);
};

