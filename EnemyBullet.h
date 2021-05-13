#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

#include "Game.h"
#include "GameManager.h"
#include "GameObject.h"
 
class EnemyBullet : public GameObject
{
public:
    const float VisibleRadius = 8; // �����ڂ̔��a

    float x; // x���W
    float y; // y���W
    bool isDead = false; // ���S�t���O
    float collisionRadius = 8; // �����蔻�蔼�a

    float vx; // x�����ړ����x
    float vy; // y�����ړ����x

    int seCoolTime = 0;

    GameManager& gm = GameManager::GetInstance();

    EnemyBullet(float x, float y, float angle, float speed)
    {
        this->x = x;
        this->y = y;

        // �p�x����x�����̈ړ����x���Z�o
        vx = (float)cos(angle) * speed;
        // �p�x����y�����̈ړ����x���Z�o
        vy = (float)sin(angle) * speed;
    }

    ~EnemyBullet()
    {
        //delete mem; //�ynew�������́z�͔j����������ΕK�v�ynew���u�A�_���A��΁z
    };

    void Update();

    void Draw();

    // �K�E�Z���g��ꂽ���̏���
    void OnCollisionAbility()
    {
        isDead = true;
    }
};

#endif // !ENEMYBULLET_H_

