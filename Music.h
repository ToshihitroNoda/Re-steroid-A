#ifndef MUSIC_H_
#define MUSIC_H_

#include "Game.h"

class Music
{
public:
	Music() {};
	~Music() {};
	static void Load();

	static int playerBulletSE;
	static int enemyBulletSE;
	static int explosionSE;
	static int damageSE;
	static int ability;
	static int item;
	static int heal;
};

#endif // !MUSIC_H_

