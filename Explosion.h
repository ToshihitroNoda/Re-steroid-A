#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Game.h"
#include "GameObject.h"
#include "GameObject.h"

class Explosion : public GameObject
{
public:
    float x; // x座標
    float y; // y座標
    bool isDead = false; // 死亡フラグ

    int counter = 0; // 時間を計るための変数
    int imageIndex = 0; // 表示すべき画像の番号

    int seCoolTime = 0;

    Explosion(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    void Update();
    void Draw();
};

#endif // !EXPLOSION_H_

