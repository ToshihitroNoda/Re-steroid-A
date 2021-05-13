#ifndef DATACSV_H_
#define DATACSV_H_

#include <memory>
#include <vector>
#include <string>

#include <fstream> // ファイル読み出しifstreamに必要
#include <string> //文字列に必要
#include <sstream> // 文字列ストリームに必要

#include <assert.h> // マップ読込み失敗表示用

// CSVファイルを読込み幅や高さとデータ本体を保持するデータ型
struct DataCsv
{   // 読込んだデータファイルの情報
    std::string FilePath = "";
    int Width = 0; // csvファイルの表の幅
    int Height = 0;// csvファイルの表の高さ
    std::vector<std::vector<int>> Data;// csvデータ
    // ★スムーズに[][]でアクセスできるように[]演算子を独自定義する
    std::vector<int>& operator[](std::size_t index) { // ★ &参照にしないといちいちデータのコピーを返すので遅くなるよ
        return Data[index]; // 書き込み
    }
    std::vector<int> operator[](std::size_t index) const { // ★constは添え字[]読み取りの処理を定義
        return Data[index]; // 読み取り
    }

    std::size_t size()
    {   // size()関数の名前をvectorと被らせることで使う側はvectorインvectorのままのコードで使える
        return Data.size();
    }
    // 初期化コンストラクタでファイル名を指定して初期化と同時にファイル読込
    DataCsv(std::string FilePath = "") :FilePath{ FilePath }
    {// csvファイルの読込み★【初期化と同時なのでファイルとデータ型が一心同体で使いやすい】
        if (FilePath != "") Load(FilePath); // ファイル読込み
    };
    virtual ~DataCsv()
    {// 仮想デストラクタ
        Data.clear();// 2次元配列データのお掃除
    };

    // データをクリアしてメモリを節約する
    virtual void clear()
    {   // データをクリアしてメモリを節約する
        Data.clear();// 2次元配列データのお掃除
    }

    // csvファイルの読み込み
    void Load(std::string filePath)
    {
        if (filePath == "") return; //ファイル名がない
        FilePath = filePath; // ファイル名を保管
        Data.clear(); //データを一旦クリア
        // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
        std::ifstream ifs_csv_file(filePath);
        std::string line; //1行単位の読込み文字列

        int readWidth = 0; //読込みデータの幅
        int maxWidth = 0; //今から読み込んだ時のMAXの幅
        int readHeight = 0; //初期化
        while (std::getline(ifs_csv_file, line)) // ファイルを行ごとに読み込む
        {
            std::vector<int> numlist; // 1行の数字リスト
            std::istringstream linestream(line); // 各行の文字列ストリーム
            std::string splitted; // カンマ分割文字列
            int widthCount = 0; //この行の幅をカウント
            while (std::getline(linestream, splitted, { ',' }))
            {
                std::istringstream ss; //文字列ストリームの初期化
                ss = std::istringstream(splitted); //文字列ストリーム
                int num; // 数字単体
                ss >> num; // 文字列ストリームから数字への変換
                numlist.push_back(num); // 数字を数字のリスト(1行リスト)に追加
                widthCount++; //この行の幅をカウントアップ
            }
            if (widthCount > maxWidth) maxWidth = widthCount; //暫定Max幅を更新

            // 1行分をvectorに追加
            if (numlist.size() != 0) Data.push_back(numlist);
            readHeight++; //マップの高さをカウントアップ
        }
        readWidth = maxWidth; //MAX幅の王者を確定

        assert(readWidth > 0); // マップ幅がおかしい
        assert(readHeight > 0); // マップ高さがおかしい

        this->Width = readWidth; // 読込み成功したデータの幅を記録
        this->Height = readHeight; // 読込み成功したデータの高さを記録

        return;
    }
};

#endif // !DATACSV_H_
