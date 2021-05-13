#include "PlayerBullet.h"

void PlayerBullet::Update()
{
    // �ړ�
    x += vx;
    y += vy;

    if (seCoolTime % 2 == 0)
    {
        StopSoundMem(Music::playerBulletSE);
        PlaySoundMem(Music::playerBulletSE, DX_PLAYTYPE_BACK, TRUE);
        ChangeVolumeSoundMem(80, Music::playerBulletSE);
        seCoolTime++;
    }

    // ��ʊO�ɏo���玀�S�t���O�𗧂Ă�
    if (x + VisibleRadius < 0 || x - VisibleRadius > Screen::Width ||
        y + VisibleRadius < 0 || y - VisibleRadius > Screen::Height)
    {
        isDead = true;
    }
}

// �`�揈��
void PlayerBullet::Draw()
{
     DrawRotaGraphF(x, y, 1, 0, Image::playerBullet, TRUE);
}

