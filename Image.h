#ifndef IMAGE_H_
#define IMAGE_H_

#include "Game.h"
#include <assert.h>

class DivImage
{   // 3Dに分割Div画像を使うと画像全体が使われてしまうのを回避するための情報
public:
    int XNum = 0;
    int YNum = 0;
    int XSize = 0;
    int YSize = 0;
    int* HandleArray = NULL;
    int AllNum = 0;
    DivImage(int XNum, int YNum, int XSize, int YSize)
    {   // 初期化コンストラクタ
        this->XNum = XNum;
        this->YNum = YNum;
        this->XSize = XSize;
        this->YSize = YSize;
        AllNum = XNum * YNum;
        // ★div分割画像読込ハンドラ保存用のint配列メモリを確保し-1で初期化
        this->HandleArray = new int[AllNum]; // 配列を確保し-1で初期化
        for (int i = 0; i < AllNum; i++) HandleArray[i] = -1;
        //↑演習★初期化後の動的配列をデバッガで見てみよう[ary,256として再評価ボタン]
        // http://visualstudiostudy.blog.fc2.com/blog-entry-17.html
        int* ary = HandleArray;
#ifdef _DEBUG // デバッグ機能(デバッグの時だけ _DEBUG が定義)
        ImagePowCheck((*this)); // *(this)でthisポインタの示す変数内容を表す
#endif
    };
    ~DivImage()
    {   // デストラクタでメモリを解放
        if (this->HandleArray != NULL)
            delete[] this->HandleArray;
    };
#ifdef _DEBUG // デバッグ機能(デバッグの時だけ _DEBUG が定義)
    bool is_pow2(unsigned int x) // 2のべき乗か計算
    {   // https://programming-place.net/ppp/contents/c/rev_res/math012.html
        return (x != 0) && (x & (x - 1)) == 0;
    }
    void ImagePowCheck(DivImage& divImage)
    {   // ★3Dに使う画像は2のべき乗でなければ受け付けないようにする
        // https://yttm-work.jp/gmpg/gmpg_0031.html
        // https://yappy-t.hatenadiary.org/entry/20100110/1263138881
        if (divImage.XSize > 0 && divImage.YSize > 0
            && is_pow2(divImage.XSize) && is_pow2(divImage.YSize)) return;
        else assert("3Dに使うなら2のべき乗の画像サイズにしなきゃ" == "");
    }
#endif
private: // コピーと代入をプライベートにして禁止する
    //コピーコンストラクタ
    DivImage(const DivImage& divImage) {};

    //代入演算子のオーバーロード
    DivImage& operator=(const DivImage& divImage) {};
};

class Image
{
public:
	Image() {}; // 初期コンストラクタの定義だけ
	~Image() {}; // 破棄する処理デストラクタの定義だけ
	static void Load();
    static int LoadDivGraph(const TCHAR* FileName, DivImage& divImage, int NotUse3DFlag = FALSE);

    static int player; // プレイヤー
    static int playerBullet; // プレイヤーの弾
    static int zako0; // ザコ0
    static int zako1; // ザコ1
    static int zako2; // ザコ2
    static int zako3; // ザコ3
    static int enemyBullet16; // 敵弾
    static DivImage explosion; // 爆発エフェクト
    static int boss1; // ボス通常時
    static int boss2; // ボス気絶
    static int boss3; // ボス発狂
    static int back;  // 背景
    static int title; // タイトル
    static int gameover; // ゲームオーバー
    static int gameclear; // ゲームクリア
    static int pushbuttontostart; // スタートボタン
    static int life1; // ライフ
    static int item1; // アイテム
    static int messagewindow; // メッセージウィンドウ
    static int character; // プレイヤー立ち絵
    static int kyokan; // 教官立ち絵
    static int cutin; // カットイン 
};

#endif // !IMAGE_H_

