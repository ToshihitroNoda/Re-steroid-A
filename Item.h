#ifndef ITEM_H_
#define ITEM_H_

#include "Game.h"
#include "GameManager.h"
#include "GameObject.h"

class Item : public GameObject
{
public:
    GameManager& gm = GameManager::GetInstance();

    float x; // x���W
    float y; // y���W
    float collisionRadius = 16; // �����蔻��̔��a
    bool isDead = false; // ���S�t���O

    // �R���X�g���N�^
    Item(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    // �X�V�����B�h���N���X�ŃI�[�o�[���C�h���Ďg��
    virtual void Update() = 0;

    // �`�揈���B�h���N���X�ŃI�[�o�[���C�h���Ďg��
    virtual void Draw() = 0;

    // ���@�ɓ��������Ƃ��̏���
    virtual void OnCollisionPlayer(std::shared_ptr<GameObject> player)
    {
        /*StopSoundMem(Music.item);
        PlaySoundMem(Music.item, DX.DX_PLAYTYPE_BACK);
        ChangeVolumeSoundMem(120, Music.item);*/
        isDead = true;
    }
};

#endif // !ITEM_H_
