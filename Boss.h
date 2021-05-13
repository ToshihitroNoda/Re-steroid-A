#ifndef BOSS_H_
#define BOSS_H_

#include "Game.h"
#include "Enemy.h"

class Boss : public virtual Enemy
{
public:

    enum class State
    {
        Appear, // �o��
        Normal, // �ʏ펞
        Swoon,  // �C�⎞
        Angry,  // �������[�h
        Dying,  // ���S��
        Die     // ���S
    };

    State state; // ���݂̏��
    int swoonTime = 120; // �c��C�⎞��
    int dyingTime = 180; // ���S���̃A�j���[�V��������

    float vy = 2;
    float vx = 2;
    double angle = 0;
    float v_angle = 1;

    int coolTime = 0;
    int counter = 0; // ���S�G�t�F�N�g�̏I���܂ł̃J�E���^�[

    static bool isEnd;

    // �R���X�g���N�^
    Boss(float x, float y)
        : Enemy(x, y)
    {
        life = 140; // ���C�t
        collisionRadius = 70; // �����蔻�蔼�a

        state = State::Appear; // ���݂̏��
    }

    void Update() override;

    void Draw() override;

    // ���@�e�ɓ����������̏�����override�i�㏑���j����
    void OnCollisionPlayerBullet(std::shared_ptr<GameObject> playerBullet) override;

    // �K�E�Z���g��ꂽ���̏���
    void OnCollisionAbility() override; 
};

#endif // !BOSS_H_

