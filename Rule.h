#ifndef RULE_H_
#define RULE_H_

#include <string>
#include <iostream>

#include "Game.h"
#include "GameManager.h"
#include "GameObject.h"

class Rule
{
public:
    //★【仲介者パターン】ゲーム内のもの同士はマネージャを通して一元化してやり取り
    GameManager& gm = GameManager::GetInstance(); //唯一のゲームマネージャへの参照(&)を得る

    int massege = 0;
    bool massegeEnd = false;

    std::string massegeList[12]{
        " ～指令室～ ",
        "「よく来たな、新兵！！」",
        "「これからお前には迫りくる外敵を殲滅してもらう」",
        "「機体の操作は簡単だ。」",
        "「～操作説明～」",
        "① 移動 : ←↑→↓　攻撃 : Zキー",
        "② 回復 : SCOREが3000増えるごとに1回復",
        "③ 必殺技 : SCORE20000でXキーを押す事によって発動できる",
        "「以上が機体の操作だ。」",
        "「それでは、早速だが戦場に出てもらう！！」",
        "「分からないことは戦場で学べ！幸運を祈る！！」" ,
        ""
    };

    Rule()
    {
        massege = 0;
        massegeEnd = false;
    }

    ~Rule() {}

    void Update();

    void Draw();
};

#endif // !RULE_H_


