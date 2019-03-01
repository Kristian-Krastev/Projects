#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include "EnemyCollection.h"
#include "Hero.h"
#include "Matrix.h"
#include "ProjectileCollection.h"
#include "EnemyLv1.h"
#include "EnemyLv2.h"
#include "EnemyLv3.h"

class Game
{
private:
	Matrix matrix;
	Hero* hero;
	EnemyCollection enemies;
	ProjectileCollection projectiles;

public:

	Game();
	~Game();

public:

	void start();
	void save();
	void continueGame();

};

#endif
