#include "Game.h"

int Game::score{ 0 };
bool Game::abilityFlg = false;
enum Game::State Game::state;

void Game::Init()
{
	Input::Init();
	Image::Load();
	Music::Load();
	state = Game::State::Title;

	x = 100; // X�̏����ʒu
	vx = 10;

	Reset();
}

void Game::Reset()
{
	while (gm.enemyBullets.size())
	{
		gm.enemyBullets.pop_back();
	}

	while (gm.enemies.size())
	{
		gm.enemies.pop_back();
	}

	while (gm.explosions.size())
	{
		gm.explosions.pop_back();
	}

	while (gm.items.size())
	{
		gm.items.pop_back();
	}

	gm.player = std::make_shared<Player>(100, Screen::Height / 2);

	gm.rule = std::make_shared<Rule>();

	// �w�i�X�N���[���̏�����
	backx = 0;
	backx_2 = Screen::Width;

	// �X�R�A�̏�����
	score = 0;
	// ���[�������\���t���O�̏�����
	gm.rule->massegeEnd = false;
	gm.rule->massege = 0;
	// �J�b�g�C���̃t���O�̏�����
	cutinFlg = false;
	// �K�E�Z�̃t���O�̏�����
	abilityFlg = false;
	//  ���C�t�񕜂̃{�[�_�[�̏�����
	gm.player->healBorder = 3000;

	PlayMusic("Music/op.mp3", DX_PLAYTYPE_LOOP);
	SetVolumeMusic(125);

	gm.map = std::make_shared<Map>(0, "stage1");

	state = State::Title;
}

void Game::Update()
{
	Input::Update();

	if (state == State::Title)
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			state = State::Massege;
			PlayMusic("Music/rule.mp3", DX_PLAYTYPE_LOOP);
			SetVolumeMusic(125);
		}
	}

	if (state == State::Massege)
	{
		gm.rule->Update();
		if (gm.rule->massegeEnd == true)
		{
			state = State::Play;
			PlayMusic("Music/bgm.mp3", DX_PLAYTYPE_LOOP);
			SetVolumeMusic(125);
		}
	}

	else if (state == State::Play)
	{
		gm.map->Scroll(scrollSpeed);

		for (int i = 0; i < 1000 / Screen::Width; i++)
		{
			backx -= (int)scrollSpeed * 2;
			backx_2 -= (int)scrollSpeed * 2;
			if (backx <= -Screen::Width) backx = Screen::Width;
			if (backx_2 <= -Screen::Width) backx_2 = Screen::Width;
		}

		//if (!gm.player->isDead) // ���@������ł��Ȃ����
		gm.player->Update();

		// ���@�e�̍X�V����
		// C#��foreach���Ɠ������S���@�e���X�V�ł���
		for (const auto& b : gm.playerBullets)
		{// auto�L�[���[�h�̓r���h�̃R���p�C���@�B��|��̎��Ɍ^���������_���Ă����
			b->Update();
		}

		for (const auto& b : gm.enemyBullets)
		{
			b->Update();
		}

		// �G�̍X�V����
		for (const auto& e : gm.enemies)
		{// auto�L�[���[�h�̓r���h�̃R���p�C���@�B��|��̎��Ɍ^���������_���Ă����
			e->Update();
		}

		// ���@�e�ƓG�̏Փ˔���
		for (const auto& playerBullet : gm.playerBullets)
		{
			// ���@�e������ł���X�L�b�v����
			if (playerBullet->isDead)
				continue;

			for (const auto& enemy : gm.enemies)
			{
				// �G������ł���X�L�b�v����
				if (enemy->isDead)
				{
					score += 100;
					continue;
				}

				// ���@�e�ƓG���d�Ȃ��Ă��邩�H
				if (MyMath::CircleCircleIntersection(
					playerBullet->x, playerBullet->y, playerBullet->collisionRadius,
					enemy->x, enemy->y, enemy->collisionRadius))
				{
					// �d�Ȃ��Ă�����A���ꂼ��̂Ԃ������Ƃ��̏������Ăяo��
					enemy->OnCollisionPlayerBullet(playerBullet);
					playerBullet->OnCollisionEnemy(enemy);

					// �Փ˂̌��ʁA���@�e�����񂾂�A���̒e�̃��[�v�͂����܂�
					if (playerBullet->isDead)
						break;
				}
			}
		}

		// ���@�ƓG�e�̏Փ˔���
		for (const auto& enemyBullet : gm.enemyBullets)
		{
			// ���@�����񂾂炱��ȏ㔻�肵�Ȃ�
			if (gm.player->isDead)
			{
				state = State::GameOver;
				break;
			}

			// �G�e�����񂾂�X�L�b�v
			if (enemyBullet->isDead)
				continue;

			// �~���m�̏Փ˔���Œ��ׂ�
			if (MyMath::CircleCircleIntersection(
				gm.player->x, gm.player->y, gm.player->collisionRadius,
				enemyBullet->x, enemyBullet->y, enemyBullet->collisionRadius))
			{
				gm.player->OnCollisionEnemyBullets(enemyBullet);
			}
		}

		// ���@�ƓG�̏Փ˔���
		for (const auto& enemy : gm.enemies)
		{
			// ���@������ł��炱��ȏ㔻�肵�Ȃ�
			if (gm.player->isDead)
			{
				state = State::GameOver;
				break;
			}

			// �G������ł���X�L�b�v
			if (enemy->isDead)
				continue;

			// �~���m�̏Փ˔���Œ��ׂ�
			if (MyMath::CircleCircleIntersection(
				gm.player->x, gm.player->y, gm.player->collisionRadius,
				enemy->x, enemy->y, enemy->collisionRadius))
			{
				gm.player->OnCollisionEnemy(enemy);
			}
		}

		// �����G�t�F�N�g�̍X�V����
		for (const auto& e : gm.explosions)
		{
			e->Update();
		}

		// �A�C�e���̍X�V����
		for (const auto& i : gm.items)
		{
			i->Update();
		}

		// ���@�ƃA�C�e�������蔻��
		for (const auto& item : gm.items)
		{
			// �~���m�̏Փ˔���Œ��ׂ�
			if (MyMath::CircleCircleIntersection(
				gm.player->x, gm.player->y, gm.player->collisionRadius,
				item->x, item->y, item->collisionRadius))
			{
				item->OnCollisionPlayer(gm.player);
				gm.player->OnCollisionItem(item);
			}
		}

		gm.EraseRemoveIf(gm.playerBullets,
			[](std::shared_ptr<PlayerBullet>& ptr) { return ptr->isDead; });
		gm.EraseRemoveIf(gm.enemyBullets,
			[](std::shared_ptr<EnemyBullet>& ptr) { return ptr->isDead; });
		gm.EraseRemoveIf(gm.enemies,
			[](std::shared_ptr<Enemy>& ptr) { return ptr->isDead; });
		gm.EraseRemoveIf(gm.explosions,
			[](std::shared_ptr<Explosion>& ptr) { return ptr->isDead; });
		gm.EraseRemoveIf(gm.items,
			[](std::shared_ptr<Item>& ptr) { return ptr->isDead; });
	}

	else if (state == State::GameOver) // �Q�[���I�[�o�[��Ԃł̏���
	{
		// ����A�{�^���������ꂽ��A�Q�[����������
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			Reset();
		}
	}

	else if (state == State::GameClear) // �Q�[���N���A��Ԃł̏���
	{
		// �����{�^���������ꂽ��A�Q�[����������
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			Reset();
		}
	}

	if (score >= 20000) // �K�E�Z�̏���
	{
		if (Input::GetButtonDown(PAD_INPUT_2) || abilityFlg == true)
		{
			PlaySoundMem(Music::ability, DX_PLAYTYPE_BACK, TRUE);
			cutinFlg = true;

			if (abilityFlg == true)
			{
				for (const auto& enemy : gm.enemies)
				{
					enemy->OnCollisionAbility();
				}
				for (const auto& enemyBullet : gm.enemyBullets)
				{
					enemyBullet->OnCollisionAbility();
				}
				score -= 20000;
				cutinFlg = false;
				abilityFlg = false;
			}
		}
	}
}

void Game::GameOverChange()
{
	state = State::GameClear;
	PlayMusic("Music/clear.mp3", DX_PLAYTYPE_LOOP);
	SetVolumeMusic(125);
}

void Game::Draw()
{
	if (state == State::Title)
	{
		DrawGraph(0, 0, Image::title, TRUE);
		DrawGraph(0, 0, Image::pushbuttontostart, TRUE);
	}
	else if (state == State::Massege)
	{
		DrawGraph(backx, 0, Image::back, TRUE);
		DrawGraph(0, 0, Image::character, TRUE);
		DrawGraph(0, 0, Image::kyokan, TRUE);
		DrawGraph(0, 0, Image::messagewindow, TRUE);
		gm.rule->Draw();
	}
	else if (state == State::Play || state == State::GameOver || state == State::GameClear)
	{
		// �w�i�̕`��
		DrawGraph(backx, 0, Image::back, TRUE);
		DrawGraph(backx_2, 0, Image::back, TRUE);

		if (!(gm.player->isDead)) // ���@������ł��Ȃ����
			gm.player->Draw();

		// ���@�e�̕`�揈��
		// C#��foreach���Ɠ������S���@�e���X�V�ł���
		for (const auto& b : gm.playerBullets)
		{// auto�L�[���[�h�̓r���h�̃R���p�C���@�B��|��̎��Ɍ^���������_���Ă����
			b->Draw();
		}

		for (const auto& b : gm.enemyBullets)
		{// auto�L�[���[�h�̓r���h�̃R���p�C���@�B��|��̎��Ɍ^���������_���Ă����
			b->Draw();
		}

		for (const auto& e : gm.enemies)
		{// auto�L�[���[�h�̓r���h�̃R���p�C���@�B��|��̎��Ɍ^���������_���Ă����
			e->Draw();
		}

		for (const auto& i : gm.items)
		{// auto�L�[���[�h�̓r���h�̃R���p�C���@�B��|��̎��Ɍ^���������_���Ă����
			i->Draw();
		}

		for (const auto& e : gm.explosions)
		{// auto�L�[���[�h�̓r���h�̃R���p�C���@�B��|��̎��Ɍ^���������_���Ă����
			e->Draw();
		}

		// �X�R�A�̕`��
		DrawString(720, 0, "Score : ", GetColor(255, 255, 255));
		DrawString(830, 0, std::to_string(score).c_str(), GetColor(255, 255, 255));


		// �u�K�E�Z�g�p�\�v�̕\��
		if (score >= 20000)
			DrawString(670, 30, "�I�I�K�E�Z�g�p�\�I�I", GetColor(255, 0, 0));

		// ���C�t�̕`��
		for (int i = 0; i < gm.player->life; i++)
		{
			DrawGraph(i * 35, 0, Image::life1, TRUE);
		}

		// �J�b�g�C���̕`��

		if (cutinFlg)
		{
			DrawGraph(cutinx += cutinSpeed, 0, Image::cutin, TRUE);
			if (cutinx >= 0) cutinSpeed = 0;
			cutinCoolTime++;

			if (cutinCoolTime >= 60)
			{
				// �J�b�g�C���\�����Ԃ̏�����
				cutinCoolTime = 0;
				// �J�b�g�C����x���W�̏�����
				cutinx = -480;
				// �J�b�g�C���X�s�[�h�̏�����
				cutinSpeed = 16;
				abilityFlg = true;
			}
		}

		if (state == State::GameOver)
		{
			DrawGraph(0, 0, Image::gameover, TRUE);
		}
		else if (state == State::GameClear)
		{
			DrawGraph(0, 0, Image::gameclear, TRUE);
		}
	}
}

