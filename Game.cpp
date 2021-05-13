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

	x = 100; // Xの初期位置
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

	// 背景スクロールの初期化
	backx = 0;
	backx_2 = Screen::Width;

	// スコアの初期化
	score = 0;
	// ルール説明表示フラグの初期化
	gm.rule->massegeEnd = false;
	gm.rule->massege = 0;
	// カットインのフラグの初期化
	cutinFlg = false;
	// 必殺技のフラグの初期化
	abilityFlg = false;
	//  ライフ回復のボーダーの初期化
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

		//if (!gm.player->isDead) // 自機が死んでいなければ
		gm.player->Update();

		// 自機弾の更新処理
		// C#のforeach文と同じく全自機弾を更新できる
		for (const auto& b : gm.playerBullets)
		{// autoキーワードはビルドのコンパイル機械語翻訳の時に型を自動推論してくれる
			b->Update();
		}

		for (const auto& b : gm.enemyBullets)
		{
			b->Update();
		}

		// 敵の更新処理
		for (const auto& e : gm.enemies)
		{// autoキーワードはビルドのコンパイル機械語翻訳の時に型を自動推論してくれる
			e->Update();
		}

		// 自機弾と敵の衝突判定
		for (const auto& playerBullet : gm.playerBullets)
		{
			// 自機弾が死んでたらスキップする
			if (playerBullet->isDead)
				continue;

			for (const auto& enemy : gm.enemies)
			{
				// 敵が死んでたらスキップする
				if (enemy->isDead)
				{
					score += 100;
					continue;
				}

				// 自機弾と敵が重なっているか？
				if (MyMath::CircleCircleIntersection(
					playerBullet->x, playerBullet->y, playerBullet->collisionRadius,
					enemy->x, enemy->y, enemy->collisionRadius))
				{
					// 重なっていたら、それぞれのぶつかったときの処理を呼び出す
					enemy->OnCollisionPlayerBullet(playerBullet);
					playerBullet->OnCollisionEnemy(enemy);

					// 衝突の結果、自機弾が死んだら、この弾のループはおしまい
					if (playerBullet->isDead)
						break;
				}
			}
		}

		// 自機と敵弾の衝突判定
		for (const auto& enemyBullet : gm.enemyBullets)
		{
			// 自機が死んだらこれ以上判定しない
			if (gm.player->isDead)
			{
				state = State::GameOver;
				break;
			}

			// 敵弾が死んだらスキップ
			if (enemyBullet->isDead)
				continue;

			// 円同士の衝突判定で調べる
			if (MyMath::CircleCircleIntersection(
				gm.player->x, gm.player->y, gm.player->collisionRadius,
				enemyBullet->x, enemyBullet->y, enemyBullet->collisionRadius))
			{
				gm.player->OnCollisionEnemyBullets(enemyBullet);
			}
		}

		// 自機と敵の衝突判定
		for (const auto& enemy : gm.enemies)
		{
			// 自機が死んでたらこれ以上判定しない
			if (gm.player->isDead)
			{
				state = State::GameOver;
				break;
			}

			// 敵が死んでたらスキップ
			if (enemy->isDead)
				continue;

			// 円同士の衝突判定で調べる
			if (MyMath::CircleCircleIntersection(
				gm.player->x, gm.player->y, gm.player->collisionRadius,
				enemy->x, enemy->y, enemy->collisionRadius))
			{
				gm.player->OnCollisionEnemy(enemy);
			}
		}

		// 爆発エフェクトの更新処理
		for (const auto& e : gm.explosions)
		{
			e->Update();
		}

		// アイテムの更新処理
		for (const auto& i : gm.items)
		{
			i->Update();
		}

		// 自機とアイテム当たり判定
		for (const auto& item : gm.items)
		{
			// 円同士の衝突判定で調べる
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

	else if (state == State::GameOver) // ゲームオーバー状態での処理
	{
		// もしAボタンが押されたら、ゲームを初期化
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			Reset();
		}
	}

	else if (state == State::GameClear) // ゲームクリア状態での処理
	{
		// もしボタンが押されたら、ゲームを初期化
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			Reset();
		}
	}

	if (score >= 20000) // 必殺技の処理
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
		// 背景の描画
		DrawGraph(backx, 0, Image::back, TRUE);
		DrawGraph(backx_2, 0, Image::back, TRUE);

		if (!(gm.player->isDead)) // 自機が死んでいなければ
			gm.player->Draw();

		// 自機弾の描画処理
		// C#のforeach文と同じく全自機弾を更新できる
		for (const auto& b : gm.playerBullets)
		{// autoキーワードはビルドのコンパイル機械語翻訳の時に型を自動推論してくれる
			b->Draw();
		}

		for (const auto& b : gm.enemyBullets)
		{// autoキーワードはビルドのコンパイル機械語翻訳の時に型を自動推論してくれる
			b->Draw();
		}

		for (const auto& e : gm.enemies)
		{// autoキーワードはビルドのコンパイル機械語翻訳の時に型を自動推論してくれる
			e->Draw();
		}

		for (const auto& i : gm.items)
		{// autoキーワードはビルドのコンパイル機械語翻訳の時に型を自動推論してくれる
			i->Draw();
		}

		for (const auto& e : gm.explosions)
		{// autoキーワードはビルドのコンパイル機械語翻訳の時に型を自動推論してくれる
			e->Draw();
		}

		// スコアの描画
		DrawString(720, 0, "Score : ", GetColor(255, 255, 255));
		DrawString(830, 0, std::to_string(score).c_str(), GetColor(255, 255, 255));


		// 「必殺技使用可能」の表示
		if (score >= 20000)
			DrawString(670, 30, "！！必殺技使用可能！！", GetColor(255, 0, 0));

		// ライフの描画
		for (int i = 0; i < gm.player->life; i++)
		{
			DrawGraph(i * 35, 0, Image::life1, TRUE);
		}

		// カットインの描画

		if (cutinFlg)
		{
			DrawGraph(cutinx += cutinSpeed, 0, Image::cutin, TRUE);
			if (cutinx >= 0) cutinSpeed = 0;
			cutinCoolTime++;

			if (cutinCoolTime >= 60)
			{
				// カットイン表示時間の初期化
				cutinCoolTime = 0;
				// カットインのx座標の初期化
				cutinx = -480;
				// カットインスピードの初期化
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

