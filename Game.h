#ifndef GAME_H_
#define GAME_H_

#include <vector>	// C#におけるListの機能
#include <memory>	// メモリを扱う【ポインタに必要】

#include "GameManager.h"

#include "DxLib.h"
#include "Input.h"
#include "MyMath.h"
#include "Image.h" 
#include "Music.h"
#include "Screen.h"
#include "Map.h"
#include "Rule.h"

#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Explosion.h"

class Game
{
public:

	enum class State
	{
		Title,
		Massege,
		Play,
		GameOver,
		GameClear
	};

	Game() {};  // コンストラクタ
	~Game() {}; // デストラクタ

	void Init();
	void Reset();
	void Update();
	void Draw();
	static void GameOverChange();

	int x = 0;
	int vx = 0;

	float scrollSpeed = 1.5f;	 // 背景のスクロール速度
	int backx = 0;				 // スクロール用1枚目の背景画像のx座標
	int backx_2 = Screen::Width; // スクロール用2枚目の背景画像のx座標
	bool cutinFlg = false; // カットインのフラグ
	static bool abilityFlg; // 必殺技のフラグ
	int cutinCoolTime = 0; // カットイン表示時間// カットインのx座標の初期化
	int cutinx = -480; // カットインのx座標
	int cutinSpeed = 16; // カットインスピード
	static int score; // スコア

	static State state;

	GameManager& gm = GameManager::GetInstance(); // 唯一のゲームマネージャーへの参照


	// 2)【shared_ptr】とは
	// 「兄弟で週刊少年ジャンプを【回し読みする】が
	// おかんに【全員読み終わるまでは捨てられないように】するため
	// 【読むつもりの人カウンタ】がゼロになると【おかんに捨てられる】」
};

#endif // !GAME_H_