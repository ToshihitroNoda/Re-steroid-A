#ifndef PLAYER_H_
#define PLAYER_H_

#include "Game.h"
#include "GameManager.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	const float MoveSpeed = 6; // �ړ����x
	const int MutekiJikan = 120;
	const int PlayerSize = 32;

	float x; // x���W
	float y; // y���W

	float collisionRadius = 8.0f; // �����蔻�蔼�a
	bool isDead; // ���S�t���O
	int life = 5; // ���C�t
	int mutekiTimer = 0; // �c�薳�G���ԁB0�ȉ��Ȃ疳�G����Ȃ����Ă���
	int healBorder = 3000; // ���C�t�񕜂̃{�[�_�[
	bool getItem1 = false; //item1�̊l���t���O

	GameManager& gm = GameManager::GetInstance();

	// �R���X�g���N�^
	// x : �����ʒux
	// y : �����ʒuy
	Player(float x, float y)
		:x{ x }, y{ y }
	{
		this->tag = "Player";
		this->x = x;
		this->y = y;

		isDead = false;
	}

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

	void OnCollisionEnemy(std::shared_ptr<GameObject> enemy);

	void OnCollisionEnemyBullets(std::shared_ptr<GameObject> enemyBullet);

	void OnCollisionItem(std::shared_ptr<GameObject> item);

	void TakeDamage();

};

#endif // !PLAYER_H_