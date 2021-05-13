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
	friend class Singleton<GameManager>; // Singletonでのインスタンス作成は許可

	std::shared_ptr<Map>map{ nullptr };

	std::shared_ptr<Player>player{ nullptr }; // 自機への参照

	std::shared_ptr<Rule>rule{ nullptr };

	std::vector<std::shared_ptr<Enemy>> enemies; // 敵のリスト 

	// List<PlayerBullet> playerBullets; // 自機弾のリスト
	std::vector<std::shared_ptr<PlayerBullet>> playerBullets; // 自機弾のリスト 
	// List↑と同じvector ↑2)【shared_ptr】

	std::vector<std::shared_ptr<EnemyBullet>> enemyBullets; // 敵弾のリスト 

	std::vector<std::shared_ptr<Explosion>> explosions; // 爆発エフェクトのリスト

	std::vector<std::shared_ptr<Item>> items; // アイテムのリスト

	// 削除処理テンプレート
	template <typename T, class T_if>
	void EraseRemoveIf(std::vector<T>& v, T_if if_condition)
	{
		v.erase(
			std::remove_if(v.begin(), v.end(), if_condition),
			v.end()                          
		);
	};

protected:
	GameManager() {}; // 外部からのインスタンス作成は禁止
	virtual ~GameManager() {}; // 外部からのインスタンス破棄も禁止
};

#endif // !GAMEMANAGER_H_
