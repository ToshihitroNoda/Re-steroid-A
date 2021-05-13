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
    //���y����҃p�^�[���z�Q�[�����̂��̓��m�̓}�l�[�W����ʂ��Ĉꌳ�����Ă����
    GameManager& gm = GameManager::GetInstance(); //�B��̃Q�[���}�l�[�W���ւ̎Q��(&)�𓾂�

    int massege = 0;
    bool massegeEnd = false;

    std::string massegeList[12]{
        " �`�w�ߎ��` ",
        "�u�悭�����ȁA�V���I�I�v",
        "�u���ꂩ�炨�O�ɂ͔��肭��O�G��r�ł��Ă��炤�v",
        "�u�@�̂̑���͊ȒP���B�v",
        "�u�`��������`�v",
        "�@ �ړ� : ���������@�U�� : Z�L�[",
        "�A �� : SCORE��3000�����邲�Ƃ�1��",
        "�B �K�E�Z : SCORE20000��X�L�[���������ɂ���Ĕ����ł���",
        "�u�ȏオ�@�̂̑��삾�B�v",
        "�u����ł́A�����������ɏo�Ă��炤�I�I�v",
        "�u������Ȃ����Ƃ͐��Ŋw�ׁI�K�^���F��I�I�v" ,
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


