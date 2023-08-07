//#include "wta_Animation.h"
//#include <fstream>
//#include <time.h>
//#include <string>
//#include "../dxlib_ext/dxlib_ext.h"
//
//namespace wta {
//
//    std::vector<int> Imgs;	    //読み込んだpng画像のハンドルを格納する配列  
//    int NumImgs;				//画像の枚数
//    bool LoopFlag; 			    //ループするかどうか
//    int currentFrame;			//現在のフレーム
//    float elapsedTime;			//経過時間
//    float frameDuration;		//1フレームの時間（あsにメーション描画のスピード調整）
//
//    //画像ファイルをロードする
//    int loadAnimLoopFile(const char* path) {
//        std::string folderPath = path;
//        //WIN32_FIND_DATA構造体：Windowsでファイル検索を行う際に使用されるデータ構造体
//        //Windows APIのファイル検索関数であるFindFirstFileやFindNextFileを使用する際
//        //検索結果のファイル情報を格納するために使われる
//        WIN32_FIND_DATA findData;
//        //ファイル検索を開始する
//        HANDLE hFind = FindFirstFile((folderPath + "/*").c_str(), &findData);
//        //ファイルが見つからなかった場合は終了する
//        if (hFind == INVALID_HANDLE_VALUE) { return 1; }
//        do {
//            //ファイルのみを取得(ライブラリでなければ)
//            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
//                //ファイル名を取得
//                std::string fileName = findData.cFileName;
//                //ファイルのフルパスを取得
//                std::string fullPath = folderPath + "/" + fileName;
//                //画像をロード
//                Imgs.emplace_back(LoadGraph(fullPath.c_str()));
//            }
//        } while (FindNextFile(hFind, &findData) != 0);
//        //ファイル検索を終了する
//        FindClose(hFind);
//        //画像の枚数を取得
//        NumImgs = static_cast<int>(Imgs.size());
//
//        return 0;
//    }
//
//    //画像をループ描画する
//    int drawAnimLoopFile(float delta_time, tnl::Vector3 pos, int path_hdl, float angle, float scale) {
//        elapsedTime += delta_time;
//        //経過時間がフレーム時間を超えた場合
//        if (elapsedTime >= frameDuration) {
//            elapsedTime -= frameDuration;
//            ++currentFrame;
//            //ループする(余りの数でループ)
//            if (LoopFlag) { currentFrame %= NumImgs; }
//            //ループしない
//            else if (currentFrame >= NumImgs) { currentFrame = NumImgs - 1; }
//        }
//        DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), 1.0f, tnl::ToRadian(-45), Imgs[currentFrame], TRUE);
//
//        return 0;
//    }
//}