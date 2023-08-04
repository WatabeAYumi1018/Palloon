#include "Aniｍ.h"
#include <fstream>


Anim::Anim(const char* pathName) :
    NumImgs(0), LoopFlag(true), currentFrame(0), elapsedTime(0.0f), frameDuration(0.1f)
{
    loadAnimLoopFile(pathName);
}

Anim::~Anim() {
    for (int img : Imgs) {DeleteGraph(img);}
}

//画像ファイルをロードする
void Anim::loadAnimLoopFile(const char* path) {
    std::string folderPath = path;
    //WIN32_FIND_DATA構造体：Windowsでファイル検索を行う際に使用されるデータ構造体
    //Windows APIのファイル検索関数であるFindFirstFileやFindNextFileを使用する際
    //検索結果のファイル情報を格納するために使われる
    WIN32_FIND_DATA findData;
    //ファイル検索を開始する
    HANDLE hFind = FindFirstFile((folderPath + "/*").c_str(), &findData);
    //ファイルが見つからなかった場合は終了する
    if (hFind == INVALID_HANDLE_VALUE) {return;}
    do {
        //ファイルのみを取得(ライブラリでなければ)
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            //ファイル名を取得
            std::string fileName = findData.cFileName;
            //ファイルのフルパスを取得
            std::string fullPath = folderPath + "/" + fileName;
            //画像をロード
            Imgs.emplace_back(LoadGraph(fullPath.c_str()));
        }
    } while (FindNextFile(hFind, &findData) != 0);
    //ファイル検索を終了する
    FindClose(hFind);
    //画像の枚数を取得
    NumImgs = static_cast<int>(Imgs.size());
}

//画像をループ描画する
void Anim::drawAnimLoopFile(float delta_time, tnl::Vector3 pos, float angle, float scale) {
    elapsedTime += delta_time;
    if (elapsedTime >= frameDuration) {
        elapsedTime -= frameDuration;
        ++currentFrame;
        if (LoopFlag) {
            currentFrame %= NumImgs;
        }
        else if (currentFrame >= NumImgs) {
            currentFrame = NumImgs - 1;
        }
    }
    DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), 1.0f, tnl::ToRadian(-45), Imgs[currentFrame], TRUE);
}
