#include "Zako3.h"

void Zako3::Update()
{
    if (x >= 700) x--;
    else x++;

    coolTime--;

    if (coolTime <= 0)
    {
        // Ž©‹@‘_‚¢’e
        float angle = MyMath::PointToPointAngle(x, y, gm.player->x, gm.player->y);
        gm.enemyBullets.push_back(std::make_shared<EnemyBullet>(x, y, angle, 3));
        coolTime += 15;
    }

    if (x < -32) isDead = true;
}

void Zako3::Draw()
{
    DrawRotaGraphF(x, y, 1, 0, Image::zako3, TRUE);
}