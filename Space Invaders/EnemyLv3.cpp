#include "EnemyLv3.h"

EnemyLv3::EnemyLv3(size_t x, size_t y): Enemy(x, y)
{
}

void EnemyLv3::visualize(Matrix& matrix) const
{
	matrix.setPos(posY, posX - 1, '<');
	matrix.setPos(posY, posX, '(');
	matrix.setPos(posY, posX + 1, '-');
	matrix.setPos(posY, posX + 2, ')');
	matrix.setPos(posY, posX + 3, '-');
	matrix.setPos(posY - 1, posX, '/');
	matrix.setPos(posY + 1, posX, '\\');
}

bool EnemyLv3::isInCollision(size_t x, size_t y) const	//with the hero
{
	if ((posX - 1 == x + 1 && posY == y) || (posX - 1 == x && posY == y - 1)
		|| (posX - 1 == x && posY == y + 1) || (posX - 1 == x && posY == y - 2)
		|| (posX - 1 == x && posY == y + 2)) {
		return true;
	}

	return false;
}

void EnemyLv3::write(std::ofstream& ofs) const
{

	ofs << '3' << ' ' << posX << ' ' << posY << std::endl;
}

void EnemyLv3::read(std::ifstream& ifs)
{

	ifs >> posX >> posY;
}