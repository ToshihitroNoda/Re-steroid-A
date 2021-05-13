#ifndef ZAKO2_H_
#define ZAKO2_H_

#include "Game.h"
#include "Enemy.h"

class Zako2 : public virtual Enemy
{
public:

	int coolTime = 0; // �N�[���^�C��(��p���ԁB0�ɂȂ�܂Ŏ��̒e�����ĂȂ�)

		// �R���X�g���N�^
	Zako2(float x, float y)
		: Enemy(x, y)
	{
	}

	// �X�V����
	void Update() override;

	void Draw() override;

};

#endif // !ZAKO2_H_

