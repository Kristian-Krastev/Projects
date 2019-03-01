#include "ProjectileCollection.h"



ProjectileCollection::ProjectileCollection(): heroP(nullptr), numOfHeroP(0), enemyP(nullptr), numOfEnemyP(0), heroCap(0), enemyCap(0)
{
}


ProjectileCollection::~ProjectileCollection()
{
	delete[] heroP;
	numOfHeroP = 0;
	delete[] enemyP;
	numOfEnemyP = 0;
}

void ProjectileCollection::resizeHeroP(size_t newCap)
{
	heroCap = newCap;
	HeroProjectile* temp = new HeroProjectile[newCap];
	for (int i = 0; i < numOfHeroP; i++) {

		temp[i] = heroP[i];
	}

	delete[] heroP;
	heroP = temp;
}

void ProjectileCollection::resizeEnemyP(size_t newCap)
{
	enemyCap = newCap;
	EnemyProjectile* temp = new EnemyProjectile[newCap];
	for (int i = 0; i < numOfEnemyP; i++) {

		temp[i] = enemyP[i];
	}

	delete[] enemyP;
	enemyP = temp;
}

void ProjectileCollection::removeHeroProjectile(size_t index)
{

	removeAt(index);
}

void ProjectileCollection::removeEnemyProjectile(size_t x, size_t y)
{
	for (int i = 0; i < numOfEnemyP; i++) {
		if (enemyP[i].getX() == x && enemyP[i].getY() == y) {
			EnemyProjectile temp = enemyP[i];
			enemyP[i] = enemyP[numOfEnemyP - 1];
			enemyP[numOfEnemyP - 1] = temp;
			break;
		}
	}
	numOfEnemyP--;
}

void ProjectileCollection::addHeroProjectile(const HeroProjectile& newProj)
{
	if (numOfHeroP >= heroCap) {

		size_t newCap = (heroCap == 0 ? 2 : heroCap * 2);
		resizeHeroP(newCap);
	}

	heroP[numOfHeroP] = newProj;
	numOfHeroP++;
}

void ProjectileCollection::addEnemyProjectile(const EnemyProjectile& newProj)
{
	if (numOfEnemyP >= enemyCap) {

		size_t newCap = (enemyCap == 0 ? 2 : enemyCap * 2);
		resizeEnemyP(newCap);
	}

	enemyP[numOfEnemyP++] = newProj;
}

void ProjectileCollection::removeAllProjectiles()
{
	int i = 0;
	while(numOfEnemyP != 0) {

		removeEnemyProjectile(enemyP[i].getX(), enemyP[i].getY());
		i++;
	}
	int j = 0;
	while(numOfHeroP != 0) {

		removeHeroProjectile(j);
		j++;
	}

}

bool ProjectileCollection::isInCollisionWithHeroP(size_t x, size_t y)
{
 	for (int i = 0; i < numOfHeroP; i++) {
		if ((heroP[i].getX() == x - 1 && heroP[i].getY() == y)
			|| (heroP[i].getX() == x && heroP[i].getY() == y
			|| (heroP[i].getX() == x + 1 && heroP[i].getY() == y)
			|| (heroP[i].getX() == x + 1 && heroP[i].getY() == y - 1)
			|| (heroP[i].getX() == x + 2 && heroP[i].getY() == y - 1)
			|| (heroP[i].getX() == x && heroP[i].getY() == y - 1)
			|| (heroP[i].getX() == x + 1 && heroP[i].getY() == y + 1)
			|| (heroP[i].getX() == x + 2 && heroP[i].getY() == y + 1) 
			|| (heroP[i].getX() == x && heroP[i].getY() == y + 1))) {
			removeHeroProjectile(i);
			return true;
		}
	}

	return false;
}

bool ProjectileCollection::isInCollisionWithEnemyP(size_t x, size_t y)
{
	for (int i = 0; i < numOfEnemyP; i++) {
		if ((enemyP[i].getX() == x + 1 && enemyP[i].getY() == y)
			|| (enemyP[i].getX() == x && enemyP[i].getY() == y)
			|| (enemyP[i].getX() == x + 1 && enemyP[i].getY() == y - 1)
			|| (enemyP[i].getX() == x + 1 && enemyP[i].getY() == y + 1)) {
			removeEnemyProjectile(x, y);
			return true;
		}
	}

	return false;
}

void ProjectileCollection::visualize(Matrix& matrix)const
{
	for (int i = 0; i < numOfEnemyP; i++) {

		enemyP[i].draw(matrix);
	}

	for (int i = 0; i < numOfHeroP; i++) {

		heroP[i].draw(matrix);
	}

}

void ProjectileCollection::moveAllProj()
{
	for (int i = 0; i < numOfEnemyP; i++) {

		if (enemyP[i].getX() == 0 || enemyP[i].getX() == 1 || enemyP[i].getX() >= MAX_WIDTH - 5) {
			removeEnemyProjectile(enemyP[i].getX(), enemyP[i].getY());
			continue;
		}
		enemyP[i].move();
	}

	for (int i = 0; i < numOfHeroP; i++) {

		if (heroP[i].getX() == MAX_WIDTH - 2 || heroP[i].getX() == MAX_WIDTH - 3) {
			removeHeroProjectile(i);
			continue;
		}
		heroP[i].move();
	}

}

void ProjectileCollection::write(std::ofstream& ofs) const
{

	for (int i = 0; i < numOfEnemyP; i++) {

		enemyP[i].write(ofs);
	}

	for (int i = 0; i < numOfHeroP; i++) {

		heroP[i].write(ofs);
	}
}

void ProjectileCollection::removeAt(size_t index)
{
	for (int i = 0; i < numOfHeroP - 1; i++) {
		if (i >= index) {
			HeroProjectile temp = heroP[i];
			heroP[i] = heroP[i + 1];
			heroP[i + 1] = temp;
		}
	}
	numOfHeroP--;

}
