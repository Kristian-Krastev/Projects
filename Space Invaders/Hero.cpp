#include "Hero.h"

Hero* Hero::firstInstance = NULL;

Hero::Hero() :posX(1), posY(MAX_HEIGHT/2), lives(3)
{
}

void Hero::visualize(Matrix& matrix) const
{
	matrix.setPos(posY - 1, posX - 1, '\\');
	matrix.setPos(posY - 1, posX, '-');
	matrix.setPos(posY - 1, posX + 1, ' ');
	matrix.setPos(posY, posX - 1, '=');
	matrix.setPos(posY, posX, 'X');
	matrix.setPos(posY, posX + 1, '>');
	matrix.setPos(posY + 1, posX - 1, '/');
	matrix.setPos(posY + 1, posX, '-');
	matrix.setPos(posY + 1, posX + 1, ' ');
}

void Hero::write(std::ofstream& ofs) const
{

	ofs << posX << ' ' << posY << ' ' << lives << std::endl;
}

void Hero::read(std::ifstream& ifs)
{

	ifs >> posX >> posY >> lives;
}

