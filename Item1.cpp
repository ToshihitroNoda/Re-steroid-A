#include "Item1.h"

// 更新処理
void Item1::Update()
{
    x -= 2;
    if (x < -16) isDead = true;
}

// 描画処理
void Item1::Draw()
{
    DrawRotaGraphF(x, y, 1, 0, Image::item1, TRUE);
}
