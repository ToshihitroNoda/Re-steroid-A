#include "Boss.h"

bool Boss::isEnd = false;

void Boss::Update()
{
	if (state == State::Appear) // �o����
	{
		x -= 1; //���ֈړ�

		if (x <= 750) // x���W��750�ȉ��ɂȂ�����
		{
			state = State::Normal; // �ʏ��Ԃֈڍs
			PlayMusic("Music/boss.mp3", DX_PLAYTYPE_LOOP);
			SetVolumeMusic(125);
		}
	}
	else if (state == State::Normal) // �ʏ���
	{
		// �ȉ~�O���̌v�Z
		vx = 400 * (float)cos(angle * MyMath::Deg2Rad);
		vy = 230 * (float)sin(angle * MyMath::Deg2Rad);
		// ��ɑO��̑ȉ~�O������X�������ď����ʒu�Ɍv�Z���Ė߂�
		x -= vx;
		y -= vy;

		angle += v_angle; // 1�x���炵
		if (angle > 90 || angle < -90)
		{   // �ȉ~�O���̊p�x�̕����̃}�C�i�X�v���X��؂�ւ�
			v_angle = -v_angle;
		}
		// 1�x���炵����̑ȉ~�O���̌v�Z�����Ă���
		vx = 400 * (float)cos(angle * MyMath::Deg2Rad);
		vy = 230 * (float)sin(angle * MyMath::Deg2Rad);
		// �ȉ~�O���𑫂�
		x += vx;
		y += vy;

		coolTime--;
		float randomAngle = MyRandom::RangeInt(164, 195);

		if (coolTime <= 0)
		{
			gm.enemyBullets.push_back(std::make_shared<EnemyBullet>(x, y, -randomAngle * MyMath::Deg2Rad, 5));
			coolTime += 5;
		}
	}
	else if (state == State::Swoon) // �C����
	{
		swoonTime--; // �^�C�}�[����

		if (swoonTime <= 0) // �^�C�}�[��0�ɂȂ�����
		{
			if (life > 70)
			{
				state = State::Normal;
				swoonTime = 120;
			}
			else
			{
				state = State::Angry; // �������[�h��
			}
		}
	}
	else if (state == State::Angry) // �������[�h
	{
		float angleToPlayer = MyMath::PointToPointAngle(x, y, gm.player->x, gm.player->y);
		float speed = 1.5f;
		x += (float)cos(angleToPlayer) * speed;
		y += (float)sin(angleToPlayer) * speed;

		coolTime--;
		if (coolTime <= 0)
		{
			for (float angle = 0; angle < 360; angle += 10)
			{
				gm.enemyBullets.push_back(std::make_shared<EnemyBullet>(x, y, angle * MyMath::Deg2Rad, 4));
			}
			coolTime = 80;
		}
	}
	else if (state == State::Dying) // ���S��
	{
		dyingTime--; // �^�C�}�[����

		y += 0.3f;

		// �������o��
		if (dyingTime % 5 == 0)
		{
			float rx = MyRandom::PlusMinus(100);
			float ry = MyRandom::PlusMinus(100);
			gm.explosions.push_back(std::make_shared<Explosion>(x + rx, y + ry));
		}

		if (dyingTime <= 0) // �^�C�}�[��0�ɂȂ�����
		{
			for (int i = 0; i < 20; i++)
			{
				float rx = MyRandom::PlusMinus(100);
				float ry = MyRandom::PlusMinus(100);
				gm.explosions.push_back(std::make_shared<Explosion>(x + rx, y + ry));
			}
			state = State::Die;
		}
	}
	else if (state == State::Die) // ���S
	{
		counter++;
		if (counter == 60)
		{
			isEnd = true;
			isDead = true; // ���S�ɏ���
			Game::GameOverChange();
		}
	}
}

void Boss::Draw()
{
	if (state == State::Appear || state == State::Normal) // �o�ꎞ�ƒʏ펞
	{
		DrawRotaGraphF(x, y, 1, 0, Image::boss1, TRUE); // ���ʂ̉摜
	}
	else if (state == State::Swoon) // �C�⎞
	{
		DrawRotaGraphF(x, y, 1, 0, Image::boss2, TRUE); // �C�⎞�̉摜
	}
	else if (state == State::Angry) // �������[�h
	{
		DrawRotaGraphF(x, y, 1, 0, Image::boss3, TRUE); // �{���Ă���摜
	}
	else if (state == State::Dying) // ���S��
	{
		DrawRotaGraphF(x, y, 1, 0, Image::boss2, TRUE); // �C�⒆�̉摜
	}
}

// ���@�e�ɓ����������̏�����override�i�㏑���j����
void Boss::OnCollisionPlayerBullet(std::shared_ptr<GameObject> playerBullet)
{
	// �o�ꎞ�A�C�⎞�A���S���͔�e���Ă��������Ȃ�
	if (state == State::Appear || state == State::Swoon || state == State::Dying)
		return;

	life -= 1; // ���C�t�����炷

	if (life <= 0)
	{
		// ���C�t���Ȃ��Ȃ�����A�������ł���̂ł͂Ȃ��A���S��Ԃֈڍs
		state = State::Dying;
	}
	else if (state == State::Normal && life <= 70)
	{
		// �ʏ��ԂŃ��C�t��70�ȉ��ɂȂ�����A�C�₷��
		state = State::Swoon;
	}
}

void Boss::OnCollisionAbility() // �K�E�Z���g��ꂽ���̏���
{
	for (int i = 0; i < 10; i++)
	{
		float rx = MyRandom::PlusMinus(100);
		float ry = MyRandom::PlusMinus(100);
		gm.explosions.push_back(std::make_shared<Explosion>(x + rx, y + ry));
	}
	life -= 20;
	state = State::Swoon;
}
