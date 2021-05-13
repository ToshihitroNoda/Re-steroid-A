#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

// �Q�[����ɕ\������镨�̂̊��N���X�B
// �v���C���[��G�A�A�C�e���Ȃǂ͂��̃N���X���p�����č��B
class GameObject
{
public:
    GameManager& gm = GameManager::GetInstance();

    std::string tag = ""; // �����^�O:�I�u�W�F�N�g�̎�ޔ��ʂɎg���^�O

	float x = 0; // x���W
	float y = 0; // y���W
	bool isDead = false; // ���񂾁i�폜�Ώہj�t���O
protected:
	//PlayScene playScene; // PlayScene�̎Q��
	int imageWidth = 0;
	int imageHeight = 0;
	int hitboxOffsetLeft = 0;
	int hitboxOffsetRight = 0;
	int hitboxOffsetTop = 0;
	int hitboxOffsetBottom = 0;

	// �R���X�g���N�^
	GameObject()
	{

	}

    // �����蔻��̍��[���擾
    virtual float GetLeft()
    {
        return x + hitboxOffsetLeft;
    }

    // ���[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
    virtual void SetLeft(float left)
    {
        x = left - hitboxOffsetLeft;
    }

    // �E�[���擾
    virtual float GetRight()
    {
        return x + imageWidth - hitboxOffsetRight;
    }

    // �E�[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
    virtual void SetRight(float right)
    {
        x = right + hitboxOffsetRight - imageWidth;
    }

    // ��[���擾
    virtual float GetTop()
    {
        return y + hitboxOffsetTop;
    }

    // ��[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
    virtual void SetTop(float top)
    {
        y = top - hitboxOffsetTop;
    }

    // ���[���擾����
    virtual float GetBottom()
    {
        return y + imageHeight - hitboxOffsetBottom;
    }

    // ���[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
    virtual void SetBottom(float bottom)
    {
        y = bottom + hitboxOffsetBottom - imageHeight;
    }

    // �X�V����
    virtual void Update() = 0; //�������z�֐���

    // �`�揈��
    virtual void Draw() = 0;

};

#endif // !GAMEOBJECT_H_