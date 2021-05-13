#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

// ゲーム上に表示される物体の基底クラス。
// プレイヤーや敵、アイテムなどはこのクラスを継承して作る。
class GameObject
{
public:
    GameManager& gm = GameManager::GetInstance();

    std::string tag = ""; // 文字タグ:オブジェクトの種類判別に使うタグ

	float x = 0; // x座標
	float y = 0; // y座標
	bool isDead = false; // 死んだ（削除対象）フラグ
protected:
	//PlayScene playScene; // PlaySceneの参照
	int imageWidth = 0;
	int imageHeight = 0;
	int hitboxOffsetLeft = 0;
	int hitboxOffsetRight = 0;
	int hitboxOffsetTop = 0;
	int hitboxOffsetBottom = 0;

	// コンストラクタ
	GameObject()
	{

	}

    // 当たり判定の左端を取得
    virtual float GetLeft()
    {
        return x + hitboxOffsetLeft;
    }

    // 左端を指定することにより位置を設定する
    virtual void SetLeft(float left)
    {
        x = left - hitboxOffsetLeft;
    }

    // 右端を取得
    virtual float GetRight()
    {
        return x + imageWidth - hitboxOffsetRight;
    }

    // 右端を指定することにより位置を設定する
    virtual void SetRight(float right)
    {
        x = right + hitboxOffsetRight - imageWidth;
    }

    // 上端を取得
    virtual float GetTop()
    {
        return y + hitboxOffsetTop;
    }

    // 上端を指定することにより位置を設定する
    virtual void SetTop(float top)
    {
        y = top - hitboxOffsetTop;
    }

    // 下端を取得する
    virtual float GetBottom()
    {
        return y + imageHeight - hitboxOffsetBottom;
    }

    // 下端を指定することにより位置を設定する
    virtual void SetBottom(float bottom)
    {
        y = bottom + hitboxOffsetBottom - imageHeight;
    }

    // 更新処理
    virtual void Update() = 0; //純粋仮想関数に

    // 描画処理
    virtual void Draw() = 0;

};

#endif // !GAMEOBJECT_H_