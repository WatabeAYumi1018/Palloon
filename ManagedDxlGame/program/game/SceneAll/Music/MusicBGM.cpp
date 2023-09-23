#include "MusicBGM.h"

MusicBGM::MusicBGM(const std::string& path)
{
	m_hdl = LoadSoundMem(path.c_str());
}

MusicBGM::~MusicBGM()
{
	DeleteSoundMem(m_hdl);
}

void MusicBGM::Play()
{
	PlaySoundMem(m_hdl, DX_PLAYTYPE_LOOP);
}

void MusicBGM::Stop()
{
	StopSoundMem(m_hdl);
}