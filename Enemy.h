#ifndef ENEMY_H_
#define ENEMY_H_

#include <string>

#include "GameManager.h"
#include "GameObject.h"
#include "MyRandom.h"
#include "MyMath.h"
#include "Image.h"
#include "Player.h"

class Game;
class PlayerBullet;

class Enemy : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	float x;
	float y;
	float collisionRadius = 32; // �����蔻��̔��a
	bool isDead = false; // ���S�t���O

	float life = 1;

	Enemy(float x, float y)
	{
		this->tag = "Enemy";
		this->x = x;
		this->y = y;
	}

	//���z�f�X�g���N�^
	// ���f�X�g���N�^���x�[�X���N���X�Łyvirtual(��)�Ƃ��Đ�Β�`����z����
	// �y�Ɉ��ȃ��������z���z�f�X�g���N�^��`���Y��y�_���A��΁I�I�z
	// Enemy���p������Zako�n�̃��������y�S�����|������Ȃ��Ȃ�I�I�z
	// https://marycore.jp/prog/cpp/virtual-destructor/
	virtual ~Enemy()
	{   // �������������Ă�Zako��delete��string�ϐ������鎞�y�������܂ŌĂ΂�Ȃ��Ȃ�z

		// ��{}���g�̏����������Ă�virtual(���̒�`)�Ły��Βf�Œ�`�I�z

	}

	virtual void Update() = 0; // = 0 �Ŋ֐�����`�A�B����abstract�N���X�Ɠ���

	virtual void Draw() = 0;

	// ���@�e�ɓ��������Ƃ��̏���
	virtual void OnCollisionPlayerBullet(std::shared_ptr<GameObject> playerBullet)
	{
		life -= 1;

		if (life <= 0)
		{
			isDead = true;
			// �������o��
			gm.explosions.push_back(std::make_shared<Explosion>(x, y));
		}
	}
	// �K�E�Z���g��ꂽ���̏���
	virtual void OnCollisionAbility()
	{
		isDead = true;
		gm.explosions.push_back(std::make_shared<Explosion>(x, y));
	}
};

#endif // !ENEMY_H_