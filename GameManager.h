#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Singleton.h"

#include <vector>
#include <memory>

class Map;
class Player;
class Enemy;
class PlayerBullet;
class EnemyBullet;
class Explosion;
class Item;
class Rule;

class GameManager : public Singleton<GameManager>
{
public:
	friend class Singleton<GameManager>; // Singleton�ł̃C���X�^���X�쐬�͋���

	std::shared_ptr<Map>map{ nullptr };

	std::shared_ptr<Player>player{ nullptr }; // ���@�ւ̎Q��

	std::shared_ptr<Rule>rule{ nullptr };

	std::vector<std::shared_ptr<Enemy>> enemies; // �G�̃��X�g 

	// List<PlayerBullet> playerBullets; // ���@�e�̃��X�g
	std::vector<std::shared_ptr<PlayerBullet>> playerBullets; // ���@�e�̃��X�g 
	// List���Ɠ���vector ��2)�yshared_ptr�z

	std::vector<std::shared_ptr<EnemyBullet>> enemyBullets; // �G�e�̃��X�g 

	std::vector<std::shared_ptr<Explosion>> explosions; // �����G�t�F�N�g�̃��X�g

	std::vector<std::shared_ptr<Item>> items; // �A�C�e���̃��X�g

	// �폜�����e���v���[�g
	template <typename T, class T_if>
	void EraseRemoveIf(std::vector<T>& v, T_if if_condition)
	{
		v.erase(
			std::remove_if(v.begin(), v.end(), if_condition),
			v.end()                          
		);
	};

protected:
	GameManager() {}; // �O������̃C���X�^���X�쐬�͋֎~
	virtual ~GameManager() {}; // �O������̃C���X�^���X�j�����֎~
};

#endif // !GAMEMANAGER_H_
