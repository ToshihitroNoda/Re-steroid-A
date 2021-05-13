#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Game.h"
#include "GameObject.h"
#include "GameObject.h"

class Explosion : public GameObject
{
public:
    float x; // x���W
    float y; // y���W
    bool isDead = false; // ���S�t���O

    int counter = 0; // ���Ԃ��v�邽�߂̕ϐ�
    int imageIndex = 0; // �\�����ׂ��摜�̔ԍ�

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

