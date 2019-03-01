#ifndef _ENEMYPROJECTILE_H_
#define _ENEMYPROJECTILE_H_

#include "Matrix.h"

class EnemyProjectile
{
private:
	size_t posX;
	size_t posY;
public:
	EnemyProjectile(size_t = 0, size_t = 0);

public:
	void move() { posX -= 2; };
	void draw(Matrix&) const;

	size_t getY()const { return posY; }
	size_t getX()const { return posX; }
	void write(std::ofstream&) const;
	void read(std::ifstream&);

};

#endif