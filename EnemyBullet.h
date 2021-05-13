#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

#include "Game.h"
#include "GameManager.h"
#include "GameObject.h"
 
class EnemyBullet : public GameObject
{
public:
    const float VisibleRadius = 8; // 見た目の半径

    float x; // x座標
    float y; // y座標
    bool isDead = false; // 死亡フラグ
    float collisionRadius = 8; // 当たり判定半径

    float vx; // x方向移動速度
    float vy; // y方向移動速度

    int seCoolTime = 0;

    GameManager& gm = GameManager::GetInstance();

    EnemyBullet(float x, float y, float angle, float speed)
    {
        this->x = x;
        this->y = y;

        // 角度からx方向の移動速度を算出
        vx = (float)cos(angle) * speed;
        // 角度からy方向の移動速度を算出
        vy = (float)sin(angle) * speed;
    }

    ~EnemyBullet()
    {
        //delete mem; //【newしたもの】は破棄処理が絶対必要【new放置、ダメ、絶対】
    };

    void Update();

    void Draw();

    // 必殺技が使われた時の処理
    void OnCollisionAbility()
    {
        isDead = true;
    }
};

#endif // !ENEMYBULLET_H_

