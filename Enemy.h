#ifndef ENEMY_H_
#define ENEMY_H_

#include <string>

#include "GameManager.h"
#include "GameObject.h"
#include "MyRandom.h"
#include "MyMath.h"
#include "Image.h"
#include "Player.h"

class Game;
class PlayerBullet;

class Enemy : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	float x;
	float y;
	float collisionRadius = 32; // 当たり判定の半径
	bool isDead = false; // 死亡フラグ

	float life = 1;

	Enemy(float x, float y)
	{
		this->tag = "Enemy";
		this->x = x;
		this->y = y;
	}

	//仮想デストラクタ
	// ★デストラクタをベース基底クラスで【virtual(仮)として絶対定義する】こと
	// 【極悪なメモリ問題】仮想デストラクタ定義し忘れ【ダメ、絶対！！】
	// Enemyを継承したZako系のメモリが【全部お掃除されなくなる！！】
	// https://marycore.jp/prog/cpp/virtual-destructor/
	virtual ~Enemy()
	{   // ★処理が無くてもZakoでdeleteやstring変数がある時【そっちまで呼ばれなくなる】

		// ★{}中身の処理が無くてもvirtual(仮の定義)で【絶対断固定義！】

	}

	virtual void Update() = 0; // = 0 で関数未定義、曖昧なabstractクラスと同じ

	virtual void Draw() = 0;

	// 自機弾に当たったときの処理
	virtual void OnCollisionPlayerBullet(std::shared_ptr<GameObject> playerBullet)
	{
		life -= 1;

		if (life <= 0)
		{
			isDead = true;
			// 爆発を出す
			gm.explosions.push_back(std::make_shared<Explosion>(x, y));
		}
	}
	// 必殺技が使われた時の処理
	virtual void OnCollisionAbility()
	{
		isDead = true;
		gm.explosions.push_back(std::make_shared<Explosion>(x, y));
	}
};

#endif // !ENEMY_H_