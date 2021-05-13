#ifndef MAP_H_
#define MAP_H_

#include <map>
#include <vector>

#include "GameManager.h"
#include "GameObject.h"
#include "DataCsv.h"

#include "Zako0.h"
#include "Zako1.h"
#include "Zako2.h"
#include "Zako3.h"
#include "Boss.h"
#include "Item1.h"

class Map
{
public:
	//★【仲介者パターン】ゲーム内のもの同士はマネージャを通して一元化してやり取り
	GameManager& gm = GameManager::GetInstance(); //唯一のゲームマネージャへの参照(&)を得る

	// マス目のXとYを保持するデータ型
	struct CellXY
	{
		int X = 0;
		int Y = 0;

		CellXY(int X, int Y) : X{ X }, Y{ Y }
		{};
		// ★連想配列で使うため < 比較演算子(連想配列並べ替えのため)をカスタム定義
		// http://programming-tips.info/use_struct_as_key_of_map/cpp/index.html
		bool operator < (const CellXY& otherXY) const {
			if (Y < otherXY.Y) return true; // Y優先並べ替え
			if (Y > otherXY.Y) return false;
			if (X < otherXY.X) return true; // Yが同じ時はXを比較
			if (X > otherXY.X) return false;
			return false; // 完全一致のときは
		}
	};

	int SpawnRangeX = 30; // 敵出現射程スポーンレンジ【注意！Xの単位はマス目】
	int SpawnRangeY = 30; // 敵出現射程スポーンレンジ【注意！Yの単位はマス目】
	// ★【最速かつ柔軟?連想配列】https://qiita.com/_EnumHack/items/f462042ec99a31881a81
	std::map<CellXY, bool> SpawnDic; // 辞書:SpawnDic["10,5"]==trueなら出現範囲 


	const int CellSize = 32; // マップの1マスのピクセル数

	std::vector<std::vector<int>> terrain; // 地形データ
	int TerrainWidth = 0; // マップデータの横のマス数
	int TerrainHeight = 0; // マップデータの縦のマス数

	// ★多次元配列をvectorインvectorで
	// https://atcoder.jp/contests/APG4b/tasks/APG4b_t
	DataCsv enemyData; // 敵配置データ

	float positionX = 0; // 現在の位置（マップ左端の座標）
	float positionY = 0; // 現在の位置（マップ上端の座標）

	float deltaSumX = 0; // deltaXの変化が溜まってマス目が移動が発生するかの判定の計算に使う
	float deltaSumY = 0; // deltaYの変化が溜まってマス目が移動が発生するかの判定の計算に使う

	// コンストラクタ
	// startPosition : 開始位置（デバッグやリスタート時に、面の途中から開始できるように）
	// filePath : CSVファイルのパス
	Map(float startPosition, std::string stageName);

	// デストラクタ
	~Map()
	{
		// マップデータのお掃除
		enemyData.clear();
		//terrain.clear();
	}

	// 敵出現射程の辞書初期化【先に計算して辞書化】すると計算が必要なくなり【高速化する】
	//【注意！XとYの単位はマス目】
	void InitSpawnDic(int rangeCellX, int rangeCellY);

	// 画面スクロール（位置の更新）
	//void Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj = NULL);
	void Scroll(float delta);

	// オブジェクトを生成・配置する
	//void SpawnObject(int mapX, int mapY, int objectID);
};

#endif // !MAP_H_
