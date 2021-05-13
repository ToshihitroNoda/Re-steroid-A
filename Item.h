#ifndef ITEM_H_
#define ITEM_H_

#include "Game.h"
#include "GameManager.h"
#include "GameObject.h"

class Item : public GameObject
{
public:
    GameManager& gm = GameManager::GetInstance();

    float x; // x座標
    float y; // y座標
    float collisionRadius = 16; // 当たり判定の半径
    bool isDead = false; // 死亡フラグ

    // コンストラクタ
    Item(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    // 更新処理。派生クラスでオーバーライドして使う
    virtual void Update() = 0;

    // 描画処理。派生クラスでオーバーライドして使う
    virtual void Draw() = 0;

    // 自機に当たったときの処理
    virtual void OnCollisionPlayer(std::shared_ptr<GameObject> player)
    {
        /*StopSoundMem(Music.item);
        PlaySoundMem(Music.item, DX.DX_PLAYTYPE_BACK);
        ChangeVolumeSoundMem(120, Music.item);*/
        isDead = true;
    }
};

#endif // !ITEM_H_
