#ifndef ZAKO1_H_
#define ZAKO1_H_

#include "Game.h"
#include "Enemy.h"

class Zako1 : public virtual Enemy
{
public:
	int coolTime = 0;

	float angleToPlayer = 0;
	float speed = 0;

	Zako1(float x, float y)
		:Enemy(x, y)
	{
		this->tag = "Zako1";
		life = 5;
	}

	void Update() override;

	void Draw() override;
};

#endif // !ZAKO1_H_
