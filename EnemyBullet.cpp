#include "EnemyBullet.h"

// �X�V����
void EnemyBullet::Update()
{
    // ���x�̕������ړ�
    x += vx;
    y += vy;

    if (seCoolTime % 120 == 0)
    {
        StopSoundMem(Music::enemyBulletSE);
        PlaySoundMem(Music::enemyBulletSE, DX_PLAYTYPE_BACK, TRUE);
        ChangeVolumeSoundMem(100, Music::enemyBulletSE);
    }

    // ��ʊO�ɏo���玀�S�t���O�𗧂Ă�
    if (y + VisibleRadius < 0 || y - VisibleRadius > Screen::Height ||
        x + VisibleRadius < 0 || x - VisibleRadius > Screen::Width)
    {
        isDead = true;
    }
}

// �`�揈��
void EnemyBullet::Draw()
{
    DrawRotaGraphF(x, y, 1, 0, Image::enemyBullet16,TRUE);
}
