#ifndef ZAKO2_H_
#define ZAKO2_H_

#include "Game.h"
#include "Enemy.h"

class Zako2 : public virtual Enemy
{
public:

	int coolTime = 0; // クールタイム(冷却時間。0になるまで次の弾が撃てない)

		// コンストラクタ
	Zako2(float x, float y)
		: Enemy(x, y)
	{
	}

	// 更新処理
	void Update() override;

	void Draw() override;

};

#endif // !ZAKO2_H_

