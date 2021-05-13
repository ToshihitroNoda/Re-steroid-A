#include "Zako2.h"

void Zako2::Update()
{
    x -= 20;

    coolTime--;
    float randomAngle = MyRandom::RangeInt(164, 195);

    if (coolTime <= 0)
    {
        gm.enemyBullets.push_back(std::make_shared<EnemyBullet>(x, y, -randomAngle * MyMath::Deg2Rad, 5));
        coolTime += 5;
    }

    if (x < -32) isDead = true;
}
    
void Zako2::Draw()
{
    DrawRotaGraphF(x, y, 1, 0, Image::zako2, TRUE);
}
