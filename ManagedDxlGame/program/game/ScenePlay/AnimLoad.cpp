#include "AnimLoad.h"
#include <fstream>

AnimLoad::AnimLoad(const std::string pathName,bool isLoop) :
    numImgs(0),loopFlag(isLoop), currentFrame(0), elapsedTime(0.0f), frameDuration(0.2f)
{
    loadAnimFile(pathName);
}

AnimLoad::~AnimLoad() {
    for (int img : Imgs) {DeleteGraph(img);}
}

//画像ファイルをロードする
void AnimLoad::loadAnimFile(const std::string folderPath) {
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
    numImgs = static_cast<int>(Imgs.size());
}

//画像を描画する
void AnimLoad::drawAnimFile(float delta_time,tnl::Vector3 pos,float angle, float scale) {
    elapsedTime += delta_time;
    //経過時間がフレーム時間を超えた場合
    if (elapsedTime >= frameDuration) {
        elapsedTime -= frameDuration;
        ++currentFrame;
        //ループする(余りの数でループ)
        if (loopFlag) {currentFrame %= numImgs;}
        //ループしない
        else if (!loopFlag && currentFrame >= numImgs) {
            currentFrame = numImgs - 1;
        	//最後のフレームに達したらアニメーション終了
			animFinished = true;
        }
    }
    DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), 1.0f, tnl::ToRadian(0), Imgs[currentFrame], TRUE);
}

void AnimLoad::resetAnim(){
    currentFrame = 0; 
    elapsedTime = 0.0f; 
    animFinished = false; 
}


//何かあった時のため保持
//AnimLoadLoop::AnimLoadLoop(const char* pathName) :
//    NumImgs(0), LoopFlag(true), currentFrame(0), elapsedTime(0.0f), frameDuration(0.2f)
//{
//    loadAnimLoopFile(pathName);
//}
//
//void AnimLoadLoop::loadAnimLoopFile(const char* path) {
//    std::string folderPath = path;
//    //WIN32_FIND_DATA構造体：Windowsでファイル検索を行う際に使用されるデータ構造体
//    //Windows APIのファイル検索関数であるFindFirstFileやFindNextFileを使用する際
//    //検索結果のファイル情報を格納するために使われる
//    WIN32_FIND_DATA findData;
//    //ファイル検索を開始する
//    HANDLE hFind = FindFirstFile((folderPath + "/*").c_str(), &findData);
//    //ファイルが見つからなかった場合は終了する
//    if (hFind == INVALID_HANDLE_VALUE) { return; }
//    do {
//        //ファイルのみを取得(ライブラリでなければ)
//        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
//            //ファイル名を取得
//            std::string fileName = findData.cFileName;
//            //ファイルのフルパスを取得
//            std::string fullPath = folderPath + "/" + fileName;
//            //画像をロード
//            Imgs.emplace_back(LoadGraph(fullPath.c_str()));
//        }
//    } while (FindNextFile(hFind, &findData) != 0);
//    //ファイル検索を終了する
//    FindClose(hFind);
//    //画像の枚数を取得
//    NumImgs = static_cast<int>(Imgs.size());
//}
