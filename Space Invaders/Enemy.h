#ifndef _ENEMYBASE_H_
#define _ENEMYBASE_H_

#include "Matrix.h"


class Enemy
{
protected:
	size_t posX;
	size_t posY;


public:
	Enemy(size_t, size_t);
	virtual~Enemy() {}

public:
	virtual void visualize(Matrix&) const = 0;
	virtual bool isInCollision(size_t, size_t) const = 0;
	virtual void write(std::ofstream&) const = 0;
	virtual void read(std::ifstream&) = 0;

	void move() { posX--; }
	size_t getX() { return posX; }
	size_t getY() {	return posY; }

};

#endif
