#ifndef ITEM1_H_
#define ITEM1_H_

#include "Game.h"
#include "Item.h"

class Item1 : public Item
{
public:
    // コンストラクタ
    Item1(float x, float y) 
       : Item(x, y)
    {
    }

    // 更新処理
    void Update() override;

    // 描画処理
    void Draw() override;
};

#endif // !ITEM1_H_

