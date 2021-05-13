#include "Player.h"

void Player::Update()
{
	float vx = 0; // x�����ړ����x
	float vy = 0; // y�����ړ����x

	if (Input::GetButton(PAD_INPUT_LEFT))
	{
		vx = -MoveSpeed; // ��
	}
	else if (Input::GetButton(PAD_INPUT_RIGHT))
	{
		vx = MoveSpeed; // �E
	}

	if (Input::GetButton(PAD_INPUT_UP))
	{
		vy = -MoveSpeed; // ��
	}
	else if (Input::GetButton(PAD_INPUT_DOWN))
	{
		vy = MoveSpeed; // ��
	}

	// �΂߈ړ����������x�ɂȂ�悤�ɒ���
	if (vx != 0 && vy != 0)
	{
		vx /= MyMath::Sqrt2;
		vy /= MyMath::Sqrt2;
	}

	// ���ۂɓ�����
	x += vx;
	y += vy;

	if (x < 32) x = 32;
	if (x > Screen::Width - PlayerSize) x = (float)(Screen::Width - PlayerSize);
	if (y < 32) y = 32;
	if (y > Screen::Height - PlayerSize) y = (float)(Screen::Height - PlayerSize);

	// �{�^�������Ŏ��@�e�𔭎�
	if (Input::GetButtonDown(PAD_INPUT_1))
	{   // game->��(C#�ł�game.�Ɠ�����)game�z����playerBullets�����ǂ��
		gm.playerBullets.push_back(std::make_shared<PlayerBullet>(x, y, 0)); //�E (�p�xangle��������)
		if (getItem1 == true)
		{
			gm.playerBullets.push_back(std::make_shared<PlayerBullet>(x, y, -15 * MyMath::Deg2Rad)); // �E��
			gm.playerBullets.push_back(std::make_shared<PlayerBullet>(x, y, +15 * MyMath::Deg2Rad)); // �E��
		}
	}

	// ���C�t�񕜂̏���
	if (healBorder <= Game::score && Game::score != 0)
	{
		healBorder += 3000;
		if (life < 5)
		{
			PlaySoundMem(Music::heal, DX_PLAYTYPE_BACK, TRUE);
			life++;
		}
	}

	mutekiTimer--;
}
void Player::Draw()
{
	// ���G�ł͂Ȃ��ꍇ�͕`��
	// ���G����2�t���[����1��`��i�_�Łj
	if (mutekiTimer <= 0 || mutekiTimer % 2 == 0)
	DrawRotaGraphF(x, y, 1, 0, Image::player, TRUE);
}

void Player::OnCollisionEnemy(std::shared_ptr<GameObject> enemy)
{
	// ���G����Ȃ���΃_���[�W���󂯂�
	if (mutekiTimer <= 0)
	{
		Player::TakeDamage();
		StopSoundMem(Music::damageSE);
		PlaySoundMem(Music::damageSE, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(80, Music::damageSE);
	}
}

void Player::OnCollisionEnemyBullets(std::shared_ptr<GameObject> enemyBullet)
{
	// ���G����Ȃ���΃_���[�W���󂯂�
	if (mutekiTimer <= 0)
	{
		Player::TakeDamage();
		StopSoundMem(Music::damageSE);
		PlaySoundMem(Music::damageSE, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(80, Music::damageSE);
	}
}

void Player::OnCollisionItem(std::shared_ptr<GameObject> item)
{
	if (getItem1 == true)
	{
		if (life < 5)
		{
			PlaySoundMem(Music::heal, DX_PLAYTYPE_BACK, TRUE);
			life++;
		}
	}
	getItem1 = true;
}

void Player::TakeDamage()
{
	life -= 1; // ���C�t����

	if (life <= 0)
	{
		// ���C�t�������Ȃ����玀�S
		isDead = true;
		// �������o��
		gm.explosions.push_back(std::make_shared <Explosion>(x, y));
	}
	else
	{
		// ���G���Ԕ���
		mutekiTimer = MutekiJikan;
	}
}