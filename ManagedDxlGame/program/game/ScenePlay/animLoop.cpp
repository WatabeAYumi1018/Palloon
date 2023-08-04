#include "aniｍLoop.h"
#include <fstream>


AnimLoop::AnimLoop() :NumImgs(0), LoopFlag(true), currentFrame(0), elapsedTime(0.0f), frameDuration(0.1f) {}

AnimLoop::AnimLoop(const char* pathName) :
    NumImgs(0), LoopFlag(true), currentFrame(0), elapsedTime(0.0f), frameDuration(0.1f)
{
    loadAnimLoopFile(pathName);
}

AnimLoop::~AnimLoop() {
    for (int img : Imgs) {DeleteGraph(img);}
}

//画像ファイルをロードする
void AnimLoop::loadAnimLoopFile(const char* path) {
    std::string folderPath = path;
    //Windowsプラットフォーム向けのファイルシステム操作に使用される構造体
    //ファイルやディレクトリに関する情報を収集
    WIN32_FIND_DATA findData;
    //ファイルやディレクトリの検索に使用
    HANDLE hFind = FindFirstFile((folderPath + "/*").c_str(), &findData);
    //ファイルが見つからなかった場合
    if (hFind == INVALID_HANDLE_VALUE) {return;}
    do {
        //ファイルの属性がディレクトリでない場合
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::string fileName = findData.cFileName;
            std::string fullPath = folderPath + "/" + fileName;
            Imgs.push_back(LoadGraph(fullPath.c_str()));
        }
       //次のファイルを検索
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);

    NumImgs = static_cast<int>(Imgs.size());
}

//画像をループ描画する
void AnimLoop::drawAnimLoopFile(float delta_time, tnl::Vector3 pos, float angle, float scale) {
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
    DrawGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), Imgs[currentFrame], TRUE);
}
