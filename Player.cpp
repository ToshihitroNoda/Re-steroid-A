#include "Player.h"

void Player::Update()
{
	float vx = 0; // x方向移動速度
	float vy = 0; // y方向移動速度

	if (Input::GetButton(PAD_INPUT_LEFT))
	{
		vx = -MoveSpeed; // 左
	}
	else if (Input::GetButton(PAD_INPUT_RIGHT))
	{
		vx = MoveSpeed; // 右
	}

	if (Input::GetButton(PAD_INPUT_UP))
	{
		vy = -MoveSpeed; // 上
	}
	else if (Input::GetButton(PAD_INPUT_DOWN))
	{
		vy = MoveSpeed; // 下
	}

	// 斜め移動も同じ速度になるように調整
	if (vx != 0 && vy != 0)
	{
		vx /= MyMath::Sqrt2;
		vy /= MyMath::Sqrt2;
	}

	// 実際に動かす
	x += vx;
	y += vy;

	if (x < 32) x = 32;
	if (x > Screen::Width - PlayerSize) x = (float)(Screen::Width - PlayerSize);
	if (y < 32) y = 32;
	if (y > Screen::Height - PlayerSize) y = (float)(Screen::Height - PlayerSize);

	// ボタン押下で自機弾を発射
	if (Input::GetButtonDown(PAD_INPUT_1))
	{   // game->で(C#でのgame.と同じく)game配下のplayerBulletsをたどれる
		gm.playerBullets.push_back(std::make_shared<PlayerBullet>(x, y, 0)); //右 (角度angleが増えた)
		if (getItem1 == true)
		{
			gm.playerBullets.push_back(std::make_shared<PlayerBullet>(x, y, -15 * MyMath::Deg2Rad)); // 右上
			gm.playerBullets.push_back(std::make_shared<PlayerBullet>(x, y, +15 * MyMath::Deg2Rad)); // 右下
		}
	}

	// ライフ回復の処理
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
	// 無敵ではない場合は描画
	// 無敵中は2フレームに1回描画（点滅）
	if (mutekiTimer <= 0 || mutekiTimer % 2 == 0)
	DrawRotaGraphF(x, y, 1, 0, Image::player, TRUE);
}

void Player::OnCollisionEnemy(std::shared_ptr<GameObject> enemy)
{
	// 無敵じゃなければダメージを受ける
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
	// 無敵じゃなければダメージを受ける
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
	life -= 1; // ライフ減少

	if (life <= 0)
	{
		// ライフが無くなったら死亡
		isDead = true;
		// 爆発を出す
		gm.explosions.push_back(std::make_shared <Explosion>(x, y));
	}
	else
	{
		// 無敵時間発動
		mutekiTimer = MutekiJikan;
	}
}