#include "EnemyBullet.h"

// 更新処理
void EnemyBullet::Update()
{
    // 速度の分だけ移動
    x += vx;
    y += vy;

    if (seCoolTime % 120 == 0)
    {
        StopSoundMem(Music::enemyBulletSE);
        PlaySoundMem(Music::enemyBulletSE, DX_PLAYTYPE_BACK, TRUE);
        ChangeVolumeSoundMem(100, Music::enemyBulletSE);
    }

    // 画面外に出たら死亡フラグを立てる
    if (y + VisibleRadius < 0 || y - VisibleRadius > Screen::Height ||
        x + VisibleRadius < 0 || x - VisibleRadius > Screen::Width)
    {
        isDead = true;
    }
}

// 描画処理
void EnemyBullet::Draw()
{
    DrawRotaGraphF(x, y, 1, 0, Image::enemyBullet16,TRUE);
}
