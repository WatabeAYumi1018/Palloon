#include <fstream>
#include "wta_LoadAnim.h"


namespace wta {
    //�摜�t�@�C�������[�h����
    void CsvAnimData::LoadImages(const std::string& basePath) {
        //���[�h�̓x�Ƀ��Z�b�g
        animImage.clear();
        std::string folderPath = basePath + "/" + fileName;
        //WIN32_FIND_DATA�\���́FWindows�Ńt�@�C���������s���ۂɎg�p�����f�[�^�\����
        //Windows API�̃t�@�C�������֐��ł���FindFirstFile��FindNextFile���g�p�����
         //�������ʂ̃t�@�C�������i�[���邽�߂Ɏg����
        WIN32_FIND_DATA findData;
        //�t�@�C���������J�n����
        HANDLE hFind = FindFirstFile((folderPath + "/*").c_str(), &findData);
        //�t�@�C����������Ȃ������ꍇ�͏I������
        if (hFind == INVALID_HANDLE_VALUE) return;
        do {
            //�t�@�C���݂̂��擾(���C�u�����łȂ����)
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                //�t�@�C���̃t���p�X���擾
                std::string fullPath = folderPath + "/" + findData.cFileName;
                //�摜�����[�h���Ĕz��ɒǉ�
                animImage.emplace_back(LoadGraph(fullPath.c_str()));
            }
        } while (FindNextFile(hFind, &findData) != 0);
        //�t�@�C���������I������
        FindClose(hFind);
    }

    std::vector<CsvAnimData> LoadAnimationData(const std::string& csvPath, const std::string& basePath) {
        std::vector<CsvAnimData> anims;
        auto csvData = tnl::LoadCsv(csvPath);
        // �ŏ���0�s�ڂ͓ǂݎ��s�v�̂��ߍ폜
        if (!csvData.empty()) { csvData.erase(csvData.begin()); }
        //�e�s���Ƃɏ���
        for (const auto& row : csvData) {
            //csv�t�@�C���̏����\���̂Ɋi�[
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