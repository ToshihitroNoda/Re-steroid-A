#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_

#include "Game.h"
#include "GameManager.h"
#include "GameObject.h"

class Enemy;

class PlayerBullet : public GameObject
{
public:

    const float Speed = 25; // �ړ����x
    const int VisibleRadius = 16;

    float x; // x���W
    float y; // y���W
    bool isDead = false;
    float collisionRadius = 16; // �����蔻��̔��a

    float vx;
    float vy;

    int seCoolTime = 0;

    GameManager& gm = GameManager::GetInstance();

    // �R���X�g���N�^
    PlayerBullet(float x, float y, float angle)
    {
        this->tag ="PlayerBullet";
        this->x = x;
        this->y = y;

        vx = (float)std::cos(angle) * Speed;
        vy = (float)std::sin(angle) * Speed;
    }

    // �f�X�g���N�^
    ~PlayerBullet()
    {
        //delete mem; //�ynew�������́z�͔j����������ΕK�v�ynew���u�A�_���A��΁z
    }

    void Update();

    void Draw();

    void OnCollisionEnemy(std::shared_ptr<GameObject> other)
    {
        isDead = true;
    }
};

#endif // !PLAYERBULLET_H_
