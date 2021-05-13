#ifndef ZAKO0_H_
#define ZAKO0_H_

#include "Game.h"
#include "Enemy.h"

class Zako0 : public virtual Enemy
{
public:
	int coolTime = 0;

	float theta = 0;
	float radius = 10;

	Zako0(float x, float y)
		:Enemy(x, y)
	{
		this->tag = "Zako0";
	}

	void Update() override;

	void Draw() override;
};

#endif // !ZAKO0_H_

