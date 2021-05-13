#ifndef _SCREEN_H_
#define _SCREEN_H_
// #ifndefは「_SCREEN_H」がifもしもn(not)def(定義)されていないなら#endifに挟まれたコードを有効化する（だから2度目以降は無効になる）
// 二重定義を防止するために#から始まる【プリプロセッサ】を使っている
// たとえば
// ・ファイルの読み込み（including）→#includeがこれ
// ・マクロの展開（シンボルを、あらかじめ定義された規則に従って置換する）
// ・コンパイル条件によるソースコードの部分的選択→【#ifndef ～ #endifに囲まれた部分】は一度（#defineで）定義されると無効化
// ・コメントの削除【 // 】のコメント削除も【プリプロセス=前段階で行われる】

// 画面解像度
class Screen
{
public: // punlicはC#と違いpubli:以下にまとめて書かれるスタイル
	static const int Width = 960; // 横
	static const int Height = 540; // 高さ C#と違いstaticクラスではなく個々の【全ての変数にstaticをつけて】staticなクラスとする
}; // C#と違ってクラスの定義も;セミコロンで終わる

#endif // !_SCREEN_H_
