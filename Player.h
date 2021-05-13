#ifndef PLAYER_H_
#define PLAYER_H_

#include "Game.h"
#include "GameManager.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	const float MoveSpeed = 6; // 移動速度
	const int MutekiJikan = 120;
	const int PlayerSize = 32;

	float x; // x座標
	float y; // y座標

	float collisionRadius = 8.0f; // 当たり判定半径
	bool isDead; // 死亡フラグ
	int life = 5; // ライフ
	int mutekiTimer = 0; // 残り無敵時間。0以下なら無敵じゃないってこと
	int healBorder = 3000; // ライフ回復のボーダー
	bool getItem1 = false; //item1の獲得フラグ

	GameManager& gm = GameManager::GetInstance();

	// コンストラクタ
	// x : 初期位置x
	// y : 初期位置y
	Player(float x, float y)
		:x{ x }, y{ y }
	{
		this->tag = "Player";
		this->x = x;
		this->y = y;

		isDead = false;
	}

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	void OnCollisionEnemy(std::shared_ptr<GameObject> enemy);

	void OnCollisionEnemyBullets(std::shared_ptr<GameObject> enemyBullet);

	void OnCollisionItem(std::shared_ptr<GameObject> item);

	void TakeDamage();

};

#endif // !PLAYER_H_