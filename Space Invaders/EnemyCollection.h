#ifndef _ENEMYCOLLECTION_H_
#define _ENEMYCOLLECTION_H_

#include <stdlib.h> 
#include <time.h> 
#include "Enemy.h"
#include "ProjectileCollection.h"
#include "Hero.h"

extern size_t score;

class EnemyCollection
{
private:
	Enemy** enemies;
	size_t size;

private:
	void removeEnemy(size_t, size_t);
public:
	EnemyCollection();
	EnemyCollection(const EnemyCollection&) = delete;
	EnemyCollection& operator=(const EnemyCollection&) = delete;
	~EnemyCollection();

public:
	void addEnemy(Enemy*);
	void move(ProjectileCollection&, Hero*);
	void visualize(Matrix&)const;
	bool isInCollisionWIthHero(size_t, size_t);
	size_t getSize()const { return size; }
	void removeAllEnemies();

	bool isClear();

	void write(std::ofstream&)const;
};

#endif
