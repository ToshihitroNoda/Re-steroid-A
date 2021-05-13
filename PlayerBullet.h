#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_

#include "Game.h"
#include "GameManager.h"
#include "GameObject.h"

class Enemy;

class PlayerBullet : public GameObject
{
public:

    const float Speed = 25; // 移動速度
    const int VisibleRadius = 16;

    float x; // x座標
    float y; // y座標
    bool isDead = false;
    float collisionRadius = 16; // 当たり判定の半径

    float vx;
    float vy;

    int seCoolTime = 0;

    GameManager& gm = GameManager::GetInstance();

    // コンストラクタ
    PlayerBullet(float x, float y, float angle)
    {
        this->tag ="PlayerBullet";
        this->x = x;
        this->y = y;

        vx = (float)std::cos(angle) * Speed;
        vy = (float)std::sin(angle) * Speed;
    }

    // デストラクタ
    ~PlayerBullet()
    {
        //delete mem; //【newしたもの】は破棄処理が絶対必要【new放置、ダメ、絶対】
    }

    void Update();

    void Draw();

    void OnCollisionEnemy(std::shared_ptr<GameObject> other)
    {
        isDead = true;
    }
};

#endif // !PLAYERBULLET_H_
