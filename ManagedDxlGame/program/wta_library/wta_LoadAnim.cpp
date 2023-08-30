#include <fstream>
#include "wta_LoadAnim.h"


namespace wta
{
    //画像ファイルをロードする
    void CsvAnimData::LoadImages(const std::string& basePath)
    {
        //ロードの度にリセット
        animImage.clear();
        std::string folderPath = basePath + "/" + fileName;
        //WIN32_FIND_DATA構造体：Windowsでファイル検索を行う際に使用されるデータ構造体
        //Windows APIのファイル検索関数であるFindFirstFileやFindNextFileを使用する際
         //検索結果のファイル情報を格納するために使われる
        WIN32_FIND_DATA findData;
        //ファイル検索を開始する
        HANDLE hFind = FindFirstFile((folderPath + "/*").c_str(), &findData);
        //ファイルが見つからなかった場合は終了する
        if (hFind == INVALID_HANDLE_VALUE) return;
        do {
            //ファイルのみを取得(ライブラリでなければ)
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                //ファイルのフルパスを取得
                std::string fullPath = folderPath + "/" + findData.cFileName;
                //画像をロードして配列に追加
                animImage.emplace_back(LoadGraph(fullPath.c_str()));
            }
        } while (FindNextFile(hFind, &findData) != 0);
        //ファイル検索を終了する
        FindClose(hFind);
    }

    std::vector<CsvAnimData> LoadAnimationData(const std::string& csvPath, const std::string& basePath)
    {
        std::vector<CsvAnimData> anims;
        auto csvData = tnl::LoadCsv(csvPath);
        // 最初の0行目は読み取り不要のため削除
        if (!csvData.empty())
        { 
            csvData.erase(csvData.begin());
        }
        //各行ごとに処理
        for (const auto& row : csvData)
        {
            //csvファイルの情報を構造体に格納
            CsvAnimData anim;
            anim.id = row[0].getInt();
            anim.characterName = row[1].getString();
            anim.action = row[2].getString();
            anim.direction = row[3].getInt();
            anim.fileName = row[4].getString();
            anim.loop = row[5].getBool();
            anim.LoadImages(basePath);
            anims.emplace_back(anim);
        }
        return anims;
    }

}