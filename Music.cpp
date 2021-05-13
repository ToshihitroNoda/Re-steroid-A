#include "Music.h"

int Music::playerBulletSE{ -1 };
int Music::enemyBulletSE{ -1 };
int Music::explosionSE{ -1 };
int Music::damageSE{ -1 };
int Music::ability{ -1 };
int Music::item{ -1 };
int Music::heal{ -1 };

void Music::Load()
{
    playerBulletSE       = LoadSoundMem("Music/laser.wav");
    enemyBulletSE        = LoadSoundMem("Music/laser2.wav");
    explosionSE          = LoadSoundMem("Music/explosion.wav");
    damageSE             = LoadSoundMem("Music/don.wav");
    ability              = LoadSoundMem("Music/ability.wav");
    item                 = LoadSoundMem("Music/item.wav");
    heal                 = LoadSoundMem("Music/heal.wav");

    assert(playerBulletSE != -1);
    assert(enemyBulletSE != -1);
    assert(explosionSE != -1);
    assert(damageSE != -1);
    assert(ability != -1);
    assert(item != -1);
    assert(heal != -1);
}
