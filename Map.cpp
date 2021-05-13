#include "Map.h"

Map::Map(float startPosition, std::string stageName)
{
	positionX = startPosition;

	enemyData.Load("Map/" + stageName + ".csv");

	assert(SpawnRangeX > 0 && SpawnRangeY > 0); // ちゃんと敵出現射程を設定してね
	// 敵出現射程の辞書初期化
	InitSpawnDic(SpawnRangeX, SpawnRangeY);
}

// 敵出現射程の辞書初期化【先に計算して辞書化】すると計算が必要なくなり【高速化する】
   //【注意！XとYの単位はマス目】
void Map::InitSpawnDic(int rangeCellX, int rangeCellY)
{
	SpawnDic.clear();//一旦辞書をクリアするのでゲーム中の再設定も可(だが処理時間はかかる)
	// 敵出現射程の辞書初期化
	// ★ X = A cosθ Y = B sinθ(←楕円の方程式)
	// ★ 楕円の半径 r = √(A×A×cosθ×cosθ + B×B×sinθ×sinθ)
	// ★ xの2乗 + yの2乗 < rならば楕円の内側
	float A2 = (float)(rangeCellX * rangeCellX); // 2乗
	float B2 = (float)(rangeCellY * rangeCellY); // 2乗
	for (int x = -rangeCellX; x <= rangeCellX; x++)
	{
		for (int y = -rangeCellY; y <= rangeCellY; y++)
		{   //★[逆三角関数] https://cpprefjp.github.io/reference/cmath/atan2.html
			float theta = (float)std::atan2(y, x); // ★[逆三角関数]
			float cos_t = std::cos(theta);
			float sin_t = std::sin(theta);
			float r2 = A2 * cos_t * cos_t + B2 * sin_t * sin_t;
			if (x * x + y * y <= r2) // ★ xの2乗 + yの2乗 < rならば楕円の内側
			{   //楕円の内側なら辞書SpawnDic[(x,y)] = true;として登録
				//【★楕円にしたいときはこちら】SpawnDic[CellXY(x,y)] = true; //【例】SpawnDic[(3,2)] = true;
			}
			//【★四角形にしたいときはこちら】
			SpawnDic[CellXY(x, y)] = true;
		}
	}
}

void Map::Scroll(float delta)
{
	// スクロールする前の、画面右端のセルの列番号（x）
	int prevRightCell = (int)(Map::positionX + Screen::Width) / CellSize;

	positionX += delta; // スクロールする

	// スクロールした後の、画面右端のセルの列番号（x）
	int currentRightCell = (int)(positionX + Screen::Width) / CellSize;

	// スクロールした後の画面右端のセルがマップの範囲外に出ちゃったら何もしないで終了
	if (currentRightCell >= enemyData.Width)
		return;

	// スクロールする前と後で、画面右端のセルが同じ場合は、何もしないで終了
	if (prevRightCell == currentRightCell)
		return;

	// 画面右端のセルの左端のx座標
	float x = currentRightCell * CellSize - positionX;

	// 上端のセルから下端のセルまで舐めて、敵データが配置されていたら、敵を生成する
	for (int cellY = 0; cellY < enemyData.Height; cellY++)
	{
		float y = float(cellY * CellSize);

		int id = enemyData.Data[cellY][currentRightCell];


		// 番号に応じて敵を生成する
		if (id == -1) continue; // -1は空白なので、何もしない
		else if (id == 0) gm.enemies.push_back(std::make_shared<Zako0>(x + 32, y + 32));
		else if (id == 1) gm.enemies.push_back(std::make_shared <Zako1>(x + 32, y + 32));
		else if (id == 2) gm.enemies.push_back(std::make_shared <Zako2>(x + 32, y + 32));
		else if (id == 3) gm.enemies.push_back(std::make_shared <Zako3>(x + 32, y + 32));
		else if (id == 50) gm.items.push_back(std::make_shared<Item1>(x + 32, y + 32));
		else if (id == 100) gm.enemies.push_back(std::make_shared <Boss>(x + 90, y + 32)); // ボスは横幅180pxだから90px右に生成	
	}

}