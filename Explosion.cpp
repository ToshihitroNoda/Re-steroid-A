#include "Explosion.h"

void Explosion::Update()
{
    counter++;

    imageIndex = counter / 3; // ���̂܂܂��Ƒ�������̂ŁA3�Ŋ���

    if (seCoolTime % 2 == 0)
    {
        seCoolTime++;
        StopSoundMem(Music::explosionSE);
        PlaySoundMem(Music::explosionSE, DX_PLAYTYPE_BACK, TRUE);
        ChangeVolumeSoundMem(120, Music::explosionSE);
    }

    // �G��16�������Ȃ��i0�`15�j�̂ŁA
    // 16�Ԗڂ�\�����悤�Ƃ�����I���B
    if (imageIndex >= 16)
    {
        isDead = true;
    }
}

void Explosion::Draw()
{
    // Image.explosion�͔z��ł���A
    // �������ēǂݍ��񂾊G�̃n���h�����e�v�f�Ɋi�[����Ă���̂ŁA
    // �v�f�ԍ����w�肵�ăn���h�������o���Ďg���B
    DrawRotaGraphF(x, y, 1, 0, Image::explosion.HandleArray[imageIndex], TRUE);
}