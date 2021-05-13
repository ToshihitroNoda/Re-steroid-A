#include "Boss.h"

bool Boss::isEnd = false;

void Boss::Update()
{
	if (state == State::Appear) // 登場状態
	{
		x -= 1; //左へ移動

		if (x <= 750) // x座標が750以下になったら
		{
			state = State::Normal; // 通常状態へ移行
			PlayMusic("Music/boss.mp3", DX_PLAYTYPE_LOOP);
			SetVolumeMusic(125);
		}
	}
	else if (state == State::Normal) // 通常状態
	{
		// 楕円軌道の計算
		vx = 400 * (float)cos(angle * MyMath::Deg2Rad);
		vy = 230 * (float)sin(angle * MyMath::Deg2Rad);
		// 先に前回の楕円軌道分のXを引いて初期位置に計算して戻す
		x -= vx;
		y -= vy;

		angle += v_angle; // 1度ずらし
		if (angle > 90 || angle < -90)
		{   // 楕円軌道の角度の方向のマイナスプラスを切り替え
			v_angle = -v_angle;
		}
		// 1度ずらしからの楕円軌道の計算をしてから
		vx = 400 * (float)cos(angle * MyMath::Deg2Rad);
		vy = 230 * (float)sin(angle * MyMath::Deg2Rad);
		// 楕円軌道を足す
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
	else if (state == State::Swoon) // 気絶状態
	{
		swoonTime--; // タイマー減少

		if (swoonTime <= 0) // タイマーが0になったら
		{
			if (life > 70)
			{
				state = State::Normal;
				swoonTime = 120;
			}
			else
			{
				state = State::Angry; // 発狂モードへ
			}
		}
	}
	else if (state == State::Angry) // 発狂モード
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
	else if (state == State::Dying) // 死亡中
	{
		dyingTime--; // タイマー減少

		y += 0.3f;

		// 爆発を出す
		if (dyingTime % 5 == 0)
		{
			float rx = MyRandom::PlusMinus(100);
			float ry = MyRandom::PlusMinus(100);
			gm.explosions.push_back(std::make_shared<Explosion>(x + rx, y + ry));
		}

		if (dyingTime <= 0) // タイマーが0になったら
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
	else if (state == State::Die) // 死亡
	{
		counter++;
		if (counter == 60)
		{
			isEnd = true;
			isDead = true; // 完全に消滅
			Game::GameOverChange();
		}
	}
}

void Boss::Draw()
{
	if (state == State::Appear || state == State::Normal) // 登場時と通常時
	{
		DrawRotaGraphF(x, y, 1, 0, Image::boss1, TRUE); // 普通の画像
	}
	else if (state == State::Swoon) // 気絶時
	{
		DrawRotaGraphF(x, y, 1, 0, Image::boss2, TRUE); // 気絶時の画像
	}
	else if (state == State::Angry) // 発狂モード
	{
		DrawRotaGraphF(x, y, 1, 0, Image::boss3, TRUE); // 怒っている画像
	}
	else if (state == State::Dying) // 死亡中
	{
		DrawRotaGraphF(x, y, 1, 0, Image::boss2, TRUE); // 気絶中の画像
	}
}

// 自機弾に当たった時の処理をoverride（上書き）する
void Boss::OnCollisionPlayerBullet(std::shared_ptr<GameObject> playerBullet)
{
	// 登場時、気絶時、死亡時は被弾しても何もしない
	if (state == State::Appear || state == State::Swoon || state == State::Dying)
		return;

	life -= 1; // ライフを減らす

	if (life <= 0)
	{
		// ライフがなくなったら、すぐ消滅するのではなく、死亡状態へ移行
		state = State::Dying;
	}
	else if (state == State::Normal && life <= 70)
	{
		// 通常状態でライフが70以下になったら、気絶する
		state = State::Swoon;
	}
}

void Boss::OnCollisionAbility() // 必殺技が使われた時の処理
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
