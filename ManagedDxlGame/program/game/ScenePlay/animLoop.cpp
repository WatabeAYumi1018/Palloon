#include "aniｍLoop.h"
#include <fstream>


AnimLoop::AnimLoop() :NumImgs(0), LoopFlag(true), currentFrame(0), elapsedTime(0.0f), frameDuration(100.0f) {}

AnimLoop::AnimLoop(const char* pathName) :
    NumImgs(0), LoopFlag(true), currentFrame(0), elapsedTime(0.0f), frameDuration(100.0f)
{
    loadAnimLoopFile(pathName);
}

AnimLoop::~AnimLoop() {
    for (int img : Imgs) {DeleteGraph(img);}
}

//画像ファイルをロードする
void AnimLoop::loadAnimLoopFile(const char* path) {
    string folderPath = path;
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile((folderPath + "/*").c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) {return;}
    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            string fileName = findData.cFileName;
            string fullPath = folderPath + "/" + fileName;
            Imgs.push_back(LoadGraph(fullPath.c_str()));
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);

    NumImgs = static_cast<int>(Imgs.size());
}

//画像をループ描画する
void AnimLoop::drawAnimLoopFile(float delta_time, Vector3 pos, float angle, float scale) {
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
