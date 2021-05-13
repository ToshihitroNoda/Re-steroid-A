#include "Rule.h"

void Rule::Update()
{
    if (Input::GetButtonDown(PAD_INPUT_1))
    {
        massege++;
    }
    if (Input::GetButtonDown(PAD_INPUT_3))
    {
        massegeEnd = true;
    }
}

void Rule::Draw()
{
    DrawString(50, 400, massegeList[massege].c_str(), GetColor(255, 255, 255));
    if (massege > (signed)massegeList->length() - 2) massegeEnd = true;
    SetFontSize(15);
    DrawString(800, 500, " Cキーでスキップ ", GetColor(255, 255, 255));
    SetFontSize(25);
}