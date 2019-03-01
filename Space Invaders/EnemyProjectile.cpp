#include "EnemyProjectile.h"



EnemyProjectile::EnemyProjectile(size_t x, size_t y): posX(x), posY(y)
{
}

void EnemyProjectile::draw(Matrix& matrix) const
{
	matrix.setPos(posY, posX, '-');

}

void EnemyProjectile::write(std::ofstream& ofs) const
{
	
	ofs << 'e' << ' ' << posX << ' ' << posY << std::endl;
}

void EnemyProjectile::read(std::ifstream& ifs)
{

	ifs >> posX >> posY;
}
