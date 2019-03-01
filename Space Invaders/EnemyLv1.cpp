#include "EnemyLv1.h"

EnemyLv1::EnemyLv1(size_t x, size_t y): Enemy(x, y)
{
}

void EnemyLv1::visualize(Matrix& matrix) const
{
	matrix.setPos(posY - 1, posX, 'o');
	matrix.setPos(posY - 1, posX + 1, 'o');
	matrix.setPos(posY, posX - 1, 'o');
	matrix.setPos(posY, posX, 'o');
	matrix.setPos(posY, posX + 1, 'o');
	matrix.setPos(posY + 1, posX, 'o');
	matrix.setPos(posY + 1, posX + 1, 'o');
}

bool EnemyLv1::isInCollision(size_t x, size_t y) const
{
	if ((posX - 1 == x + 1 && posY == y) || (posX - 1 == x && posY == y - 1)
		|| (posX - 1 == x && posY == y + 1) || (posX - 1 == x && posY == y - 2)
		|| (posX - 1 == x && posY == y + 2)) {
		return true;
	}

	return false;
}

void EnemyLv1::write(std::ofstream& ofs) const
{

	ofs << '1' << ' ' << posX << ' ' << posY << std::endl;
}

void EnemyLv1::read(std::ifstream& ifs)
{

	ifs >> posX >> posY;
}
