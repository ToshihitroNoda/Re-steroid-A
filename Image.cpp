#include "Image.h"

int Image::player{ -1 }; // Load終わっても-1（初期値）のままだと画像ロードが失敗してますね
int Image::playerBullet{ -1 };
int Image::zako0{ -1 };
int Image::zako1{ -1 };
int Image::zako2{ -1 };
int Image::zako3{ -1 };
int Image::enemyBullet16{ -1 };
DivImage Image::explosion(8, 2, 64, 64);
int Image::boss1{ -1 };
int Image::boss2{ -1 };
int Image::boss3{ -1 };
int Image::back{ -1 };
int Image::title{ -1 };
int Image::gameover{ -1 };
int Image::gameclear{ -1 };
int Image::pushbuttontostart{ -1 };
int Image::life1{ -1 };
int Image::item1{ -1 };
int Image::messagewindow{ -1 };
int Image::character{ -1 };
int Image::kyokan{ -1 };
int Image::cutin{ -1 };

// DXライブラリのLoadDivGraphを使いやすくラッピング
// ★関数に参照渡しを行う
// 関数の引数に参照渡しを行うことでdivImageの中身を書き換えることができる(値渡しでは書換不可)
//　https://qiita.com/agate-pris/items/05948b7d33f3e88b8967
//  https://qiita.com/RuthTaro/items/f35c3a26779c0ca1a41a
int Image::LoadDivGraph(const TCHAR* FileName, DivImage& divImage, int NotUse3DFlag)
{
    return DxLib::LoadDivGraph(FileName, divImage.XNum * divImage.YNum,
        divImage.XNum, divImage.YNum, divImage.XSize, divImage.YSize, divImage.HandleArray);
};

void Image::Load()
{
	player = LoadGraph("Image/player.png");
	playerBullet = LoadGraph("Image/player_bullet.png");
	zako0 = LoadGraph("Image/zako0.png");
	zako1 = LoadGraph("Image/zako1.png");
	zako2 = LoadGraph("Image/zako2.png");
	zako3 = LoadGraph("Image/zako3.png");
	enemyBullet16 = LoadGraph("Image/enemy_bullet_16.png");
    Image::LoadDivGraph("Image/explosion.png", explosion);
    boss1 = LoadGraph("Image/boss1.png");
    boss2 = LoadGraph("Image/boss2.png");
    boss3 = LoadGraph("Image/boss3.png");
    back = LoadGraph("Image/back.jpg");
    title = LoadGraph("Image/title.jpg");
    gameover = LoadGraph("Image/gameover.png");
    gameclear = LoadGraph("Image/gameclear.png");
    pushbuttontostart = LoadGraph("Image/pushbuttontostart.png");
    life1 = LoadGraph("Image/life1.png");
    item1 = LoadGraph("Image/item1.png");
    messagewindow = LoadGraph("Image/messagewindow.png");
    character = LoadGraph("Image/character.png");
    kyokan = LoadGraph("Image/kyokan.png");
    cutin = LoadGraph("Image/cutin.png");


	assert(player != -1);// 画像読み込み失敗、ファイル名かフォルダ名が間違ってる
	assert(playerBullet != -1); 
    assert(zako0 != -1);
    assert(zako1 != -1);
    assert(zako2 != -1);
    assert(zako3 != -1);
    assert(enemyBullet16 != -1);
    assert(boss1 != -1);
    assert(boss2 != -1);
    assert(boss3 != -1);
    assert(back != -1);
    assert(title != -1);
    assert(gameover != -1);
    assert(gameclear != -1);
    assert(pushbuttontostart != -1);
    assert(life1 != -1);
    assert(item1 != -1);
    assert(messagewindow != -1);
    assert(character != -1);
    assert(kyokan != -1);
    assert(cutin != -1);
	
}
