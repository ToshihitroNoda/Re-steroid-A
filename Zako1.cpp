#include "Zako1.h"

void Zako1::Update()
{
    angleToPlayer = MyMath::PointToPointAngle(x, y, gm.player->x, gm.player->y);
    speed = 3;
    x += (float)cos(angleToPlayer) * speed;
    y += (float)sin(angleToPlayer) * speed;

    coolTime--; ;

    if (coolTime <= 0)
    {
        for (float angle = 0; angle < 360; angle += 10)
        {
            gm.enemyBullets.push_back(std::make_shared<EnemyBullet>(x, y, angle * MyMath::Deg2Rad, 4));
        }
        coolTime = 30;
    }

    if (x < -32) isDead = true;

}

// •`‰æˆ—
void Zako1::Draw()
{
    DrawRotaGraphF(x, y, 1, 0, Image::zako1, TRUE);
}
