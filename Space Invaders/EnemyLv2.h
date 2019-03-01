#ifndef _ENEMYLV2_H_
#define _ENEMYLV2_H_

#include "Enemy.h"

class EnemyLv2: public Enemy
{

public:
	EnemyLv2(size_t = 0, size_t = 0);

	virtual void visualize(Matrix&) const;
	virtual bool isInCollision(size_t, size_t) const;

	virtual void write(std::ofstream&)const;
	virtual void read(std::ifstream&);
};

#endif
