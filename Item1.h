#ifndef ITEM1_H_
#define ITEM1_H_

#include "Game.h"
#include "Item.h"

class Item1 : public Item
{
public:
    // �R���X�g���N�^
    Item1(float x, float y) 
       : Item(x, y)
    {
    }

    // �X�V����
    void Update() override;

    // �`�揈��
    void Draw() override;
};

#endif // !ITEM1_H_

