#include "Explosion.h"

void Explosion::Update()
{
    counter++;

    imageIndex = counter / 3; // そのままだと早すぎるので、3で割る

    if (seCoolTime % 2 == 0)
    {
        seCoolTime++;
        StopSoundMem(Music::explosionSE);
        PlaySoundMem(Music::explosionSE, DX_PLAYTYPE_BACK, TRUE);
        ChangeVolumeSoundMem(120, Music::explosionSE);
    }

    // 絵は16枚しかない（0～15）ので、
    // 16番目を表示しようとしたら終了。
    if (imageIndex >= 16)
    {
        isDead = true;
    }
}

void Explosion::Draw()
{
    // Image.explosionは配列であり、
    // 分割して読み込んだ絵のハンドルが各要素に格納されているので、
    // 要素番号を指定してハンドルを取り出して使う。
    DrawRotaGraphF(x, y, 1, 0, Image::explosion.HandleArray[imageIndex], TRUE);
}