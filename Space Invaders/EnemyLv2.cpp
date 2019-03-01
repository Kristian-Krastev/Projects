#include "EnemyLv2.h"

EnemyLv2::EnemyLv2(size_t x, size_t y): Enemy(x, y)
{
}

void EnemyLv2::visualize(Matrix& matrix) const
{
	matrix.setPos(posY - 1, posX, '<');
	matrix.setPos(posY, posX - 1, '<');
	matrix.setPos(posY, posX, '<');
	matrix.setPos(posY, posX + 1, '<');
	matrix.setPos(posY, posX + 2, '<');
	matrix.setPos(posY + 1, posX, '<');

}

bool EnemyLv2::isInCollision(size_t x, size_t y) const
{
	if ((posX - 1 == x + 1 && posY == y) || (posX - 1 == x && posY == y - 1)
		|| (posX - 1 == x && posY == y + 1) || (posX - 1 == x && posY == y - 2)
		|| (posX - 1 == x && posY == y + 2)) {
		return true;
	}

	return false;
}

void EnemyLv2::write(std::ofstream& ofs) const
{

	ofs << '2' << ' ' << posX << ' ' << posY << std::endl;
}

void EnemyLv2::read(std::ifstream& ifs)
{

	ifs >> posX >> posY;
}