#ifndef BOSS_H_
#define BOSS_H_

#include "Game.h"
#include "Enemy.h"

class Boss : public virtual Enemy
{
public:

    enum class State
    {
        Appear, // 登場
        Normal, // 通常時
        Swoon,  // 気絶時
        Angry,  // 発狂モード
        Dying,  // 死亡中
        Die     // 死亡
    };

    State state; // 現在の状態
    int swoonTime = 120; // 残り気絶時間
    int dyingTime = 180; // 死亡時のアニメーション時間

    float vy = 2;
    float vx = 2;
    double angle = 0;
    float v_angle = 1;

    int coolTime = 0;
    int counter = 0; // 死亡エフェクトの終了までのカウンター

    static bool isEnd;

    // コンストラクタ
    Boss(float x, float y)
        : Enemy(x, y)
    {
        life = 140; // ライフ
        collisionRadius = 70; // 当たり判定半径

        state = State::Appear; // 現在の状態
    }

    void Update() override;

    void Draw() override;

    // 自機弾に当たった時の処理をoverride（上書き）する
    void OnCollisionPlayerBullet(std::shared_ptr<GameObject> playerBullet) override;

    // 必殺技が使われた時の処理
    void OnCollisionAbility() override; 
};

#endif // !BOSS_H_

