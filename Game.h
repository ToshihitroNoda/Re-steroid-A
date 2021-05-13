#ifndef GAME_H_
#define GAME_H_

#include <vector>	// C#�ɂ�����List�̋@�\
#include <memory>	// �������������y�|�C���^�ɕK�v�z

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

	Game() {};  // �R���X�g���N�^
	~Game() {}; // �f�X�g���N�^

	void Init();
	void Reset();
	void Update();
	void Draw();
	static void GameOverChange();

	int x = 0;
	int vx = 0;

	float scrollSpeed = 1.5f;	 // �w�i�̃X�N���[�����x
	int backx = 0;				 // �X�N���[���p1���ڂ̔w�i�摜��x���W
	int backx_2 = Screen::Width; // �X�N���[���p2���ڂ̔w�i�摜��x���W
	bool cutinFlg = false; // �J�b�g�C���̃t���O
	static bool abilityFlg; // �K�E�Z�̃t���O
	int cutinCoolTime = 0; // �J�b�g�C���\������// �J�b�g�C����x���W�̏�����
	int cutinx = -480; // �J�b�g�C����x���W
	int cutinSpeed = 16; // �J�b�g�C���X�s�[�h
	static int score; // �X�R�A

	static State state;

	GameManager& gm = GameManager::GetInstance(); // �B��̃Q�[���}�l�[�W���[�ւ̎Q��


	// 2)�yshared_ptr�z�Ƃ�
	// �u�Z��ŏT�����N�W�����v���y�񂵓ǂ݂���z��
	// ������Ɂy�S���ǂݏI���܂ł͎̂Ă��Ȃ��悤�Ɂz���邽��
	// �y�ǂނ���̐l�J�E���^�z���[���ɂȂ�Ɓy������Ɏ̂Ă���z�v
};

#endif // !GAME_H_