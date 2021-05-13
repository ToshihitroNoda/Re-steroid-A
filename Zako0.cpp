#include "Zako0.h"

void Zako0::Update()
{
	theta += 0.05f;
	x -= 2;
	y -= (int)(sin(theta - MyMath::PI / 4) * radius);

	coolTime--;

	float randomAngle = MyRandom::Range(0, 360);

	if (coolTime <= 0)
	{
		gm.enemyBullets.push_back(std::make_shared<EnemyBullet>(x, y, randomAngle * MyMath::Deg2Rad, 3));
		coolTime += 10;
	}

	if (x < -32) isDead = true;
}

void Zako0::Draw()
{
	DrawRotaGraphF(x, y, 1, 0, Image::zako0, TRUE);
}
