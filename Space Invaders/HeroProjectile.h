#ifndef _HEROPROJECTILE_H_
#define _HEROPROJECTILE_H_

#include "Matrix.h"

class HeroProjectile
{

private:
	size_t posX;
	size_t posY;


public:
	HeroProjectile(size_t = 0, size_t = 0);
	bool operator==(HeroProjectile& other) {
		if (this->posX == other.posX && this->posY == other.posY) {
			return true;
		}
		return false;
	}
public:
	void move() { posX += 2; }
	void draw(Matrix&) const;

	size_t getX() const { return posX; }
	size_t getY() const { return posY; }
	
	void write(std::ofstream&)const;
	void read(std::ifstream&);
};

#endif