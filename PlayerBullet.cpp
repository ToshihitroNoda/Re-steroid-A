#include "PlayerBullet.h"

void PlayerBullet::Update()
{
    // 移動
    x += vx;
    y += vy;

    if (seCoolTime % 2 == 0)
    {
        StopSoundMem(Music::playerBulletSE);
        PlaySoundMem(Music::playerBulletSE, DX_PLAYTYPE_BACK, TRUE);
        ChangeVolumeSoundMem(80, Music::playerBulletSE);
        seCoolTime++;
    }

    // 画面外に出たら死亡フラグを立てる
    if (x + VisibleRadius < 0 || x - VisibleRadius > Screen::Width ||
        y + VisibleRadius < 0 || y - VisibleRadius > Screen::Height)
    {
        isDead = true;
    }
}

// 描画処理
void PlayerBullet::Draw()
{
     DrawRotaGraphF(x, y, 1, 0, Image::playerBullet, TRUE);
}

