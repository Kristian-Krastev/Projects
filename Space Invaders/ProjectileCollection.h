#ifndef _PROJECTILECOLLECTION_H_
#define _PROJECTILECOLLECTION_H_

#include "HeroProjectile.h"
#include "EnemyProjectile.h"

class ProjectileCollection
{
private:
	HeroProjectile* heroP;
	size_t numOfHeroP;
	size_t heroCap;

	EnemyProjectile* enemyP;
	size_t numOfEnemyP;
	size_t enemyCap;

public:
	ProjectileCollection();
	ProjectileCollection(const ProjectileCollection&) = delete;
	ProjectileCollection& operator=(const ProjectileCollection&) = delete;
	~ProjectileCollection();

private:
	void resizeHeroP(size_t);
	void resizeEnemyP(size_t);

	void removeHeroProjectile(size_t);
	void removeEnemyProjectile(size_t, size_t);

public:
	void addHeroProjectile(const HeroProjectile&);
	void addEnemyProjectile(const EnemyProjectile&);
	void removeAllProjectiles();

	bool isInCollisionWithHeroP(size_t, size_t);
	bool isInCollisionWithEnemyP(size_t, size_t);
	void visualize(Matrix&) const;
	void moveAllProj();

	void write(std::ofstream&)const;
	void removeAt(size_t);

};

#endif