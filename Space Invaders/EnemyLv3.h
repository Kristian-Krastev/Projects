#ifndef _ENEMYLV3_H_
#define _ENEMYLV3_H_

#include "Enemy.h"

class EnemyLv3: public Enemy
{

public:
	EnemyLv3(size_t = 0, size_t = 0);

public:
	virtual void visualize(Matrix&)const;
	virtual bool isInCollision(size_t, size_t)const;

	virtual void write(std::ofstream&)const;
	virtual void read(std::ifstream&);
};

#endif
