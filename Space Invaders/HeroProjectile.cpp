#include "HeroProjectile.h"



HeroProjectile::HeroProjectile(size_t x, size_t y): posX(x), posY(y)
{
}


void HeroProjectile::draw(Matrix& matrix) const
{
	matrix.setPos(posY, posX - 1, '-');
	matrix.setPos(posY, posX, ' ');
	matrix.setPos(posY, posX + 1, '-');
}

void HeroProjectile::write(std::ofstream& ofs) const
{

	ofs << 'h' << ' ' << posX << ' ' << posY << std::endl;
}

void HeroProjectile::read(std::ifstream& ifs)
{

	ifs >> posX >> posY;
}
