#include "EnemyCollection.h"

size_t score = 0;

EnemyCollection::EnemyCollection(): enemies(nullptr), size(0)
{
}
EnemyCollection::~EnemyCollection()
{
	for (int i = 0; i < size; i++) {
		delete[] enemies[i];
	}
	delete[] enemies;
	enemies = nullptr;
	size = 0;
}

void EnemyCollection::removeEnemy(size_t x, size_t y)
 {
	Enemy** temp = new Enemy*[size - 1];
	int j = 0;
	int tempS = size;
	for (int i = 0; i < size; i++) {
		if (enemies[i]->getX() == x && enemies[i]->getY() == y) {	
			tempS--;			// because sometimes 2 enemies are spawned in the same position (couldnt fix it)
			delete[] enemies[i];
			continue;
		}

		temp[j] = enemies[i];
		j++;
	}
	size = tempS;
	delete[] enemies;
	enemies = new Enemy*[size];
	for (int i = 0; i < size; i++) {

		enemies[i] = temp[i];
	}

	delete[] temp;
}

void EnemyCollection::addEnemy(Enemy* newEnemy)
{
	if (newEnemy == nullptr) {
		throw std::exception("Can't add this enemy...\n");
	}
	Enemy** temp = new Enemy*[size + 1];
	for (int i = 0; i < size; i++) {
		temp[i] = enemies[i];
	}
	temp[size] = newEnemy;
	size++;

	delete[] enemies;
	enemies = temp;

}

void EnemyCollection::move(ProjectileCollection& coll, Hero* hero)
 {
	for (int i = 0; i < size; i++) {
		if ((coll.isInCollisionWithHeroP(enemies[i]->getX(), enemies[i]->getY()))) {	//if an enemy is hit - increase the score

			removeEnemy(enemies[i]->getX(), enemies[i]->getY());
			score += 200;
			if (score == 5000 || score == 10000 || score == 20000 || score == 50000) {
				hero->extraLive();
			}
			continue;
		}
		if (enemies[i]->getX() == 0) {	//if an enemy reaches the borders remove it without increasing the score
			removeEnemy(enemies[i]->getX(), enemies[i]->getY());
			continue;
		}

		enemies[i]->move();
		srand(time(NULL));
		int random = rand() % 10;
		if (random > 6) {
			EnemyProjectile newProj(enemies[i]->getX() - 1, enemies[i]->getY());
			coll.addEnemyProjectile(newProj);
		}
	}

}

void EnemyCollection::visualize(Matrix& matrix) const
{
	for (int i = 0; i < size; i++) {

		enemies[i]->visualize(matrix);
	}

}

bool EnemyCollection::isInCollisionWIthHero(size_t x, size_t y)
{
	for (int i = 0; i < size; i++) {
		
		if (enemies[i]->isInCollision(x, y)) {
			removeEnemy(enemies[i]->getX(), enemies[i]->getY());
			return true;
		}
	}

	return false;
}

void EnemyCollection::removeAllEnemies()
{
	int i = size - 1;
	while (size != 0) {
		removeEnemy(enemies[i]->getX(), enemies[i]->getY());
		i--;
	}
}

bool EnemyCollection::isClear()
{
	for (int i = 0; i < size; i++) {
		if (enemies[i]->getX() > 65) {
			return false;
		}

	}

	return true;
}

void EnemyCollection::write(std::ofstream& ofs) const
{
	for (int i = 0; i < size; i++) {

		enemies[i]->write(ofs);
	}

}


