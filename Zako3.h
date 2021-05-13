#ifndef ZAKO3_H_
#define ZAKO3_H_

#include "Game.h"
#include "Enemy.h"

class Zako3 : public virtual Enemy
{
public:

	int coolTime = 0; // �N�[���^�C��(��p���ԁB0�ɂȂ�܂Ŏ��̒e�����ĂȂ�)

		// �R���X�g���N�^
	Zako3(float x, float y)
		: Enemy(x, y)
	{
		life = 7;
	}

	// �X�V����
	void Update() override;

	void Draw() override;

};

#endif // !ZAKO3_H_
