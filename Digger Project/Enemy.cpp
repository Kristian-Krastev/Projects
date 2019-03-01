#include "Enemy.h"



Enemy::Enemy(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer* r):
	Object(w, h, x, y, img_path, r)
{
}


Enemy::~Enemy()
{
}

void Enemy::move(const std::string & direction)
{
	if (direction == "up") {
		(y - 1) >= 0 ? y -= 1 : y;
	}
	else if (direction == "down") {
		(y + 1) * 80 < 850 ? y += 1 : y;
	}
	else if (direction == "left") {
		(x - 1) >= 0 ? x -= 1 : x;

	}
	else if (direction == "right") {
		(x + 1) * 80 < 1650 ? x += 1 : x;
	}

}