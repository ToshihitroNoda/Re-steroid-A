#include "Item1.h"

// XVˆ—
void Item1::Update()
{
    x -= 2;
    if (x < -16) isDead = true;
}

// •`‰æˆ—
void Item1::Draw()
{
    DrawRotaGraphF(x, y, 1, 0, Image::item1, TRUE);
}
