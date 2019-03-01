#ifndef _HERO_H_
#define _HERO_H_

#include "Matrix.h"

class Hero
{
private:
	size_t lives;
	size_t posX;
	size_t posY;
	static Hero* firstInstance;

private:
	Hero();

public:
	static Hero* getInstance() {
		if (firstInstance == NULL) {
			return new Hero();
		}
		return firstInstance;
	}

public:
	void visualize(Matrix&) const;
	size_t getLives()const { return lives; }
	void reduceLives() { lives--; }
	void extraLive() { lives++; }
	void reset() { posX = 1; posY = MAX_HEIGHT / 2;};
	void write(std::ofstream&) const;
	void read(std::ifstream&);

	size_t getX() const { return posX; }
	size_t getY() const{ return posY; }

	void moveUp() {
		if (posY != 1) {
			posY--;
		}
	}
	void moveDown() {
		if (posY != MAX_HEIGHT - 2) {
			posY++;
		}
	}
	void moveLeft() {
		if (posX != 1) {
			posX--;
		}
	}
	void moveRight() {
		if (posX != MAX_WIDTH - 2) {
			posX++;
		}
	}
};

#endif