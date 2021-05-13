#ifndef ZAKO3_H_
#define ZAKO3_H_

#include "Game.h"
#include "Enemy.h"

class Zako3 : public virtual Enemy
{
public:

	int coolTime = 0; // クールタイム(冷却時間。0になるまで次の弾が撃てない)

		// コンストラクタ
	Zako3(float x, float y)
		: Enemy(x, y)
	{
		life = 7;
	}

	// 更新処理
	void Update() override;

	void Draw() override;

};

#endif // !ZAKO3_H_
