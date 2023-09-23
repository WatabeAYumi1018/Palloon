#pragma once
#include "../engine/GameEngine.h"

class MusicBGM
{
public:

	MusicBGM(const std::string& path);
	~MusicBGM();

private:

	//-----ƒƒ“ƒo•Ï”-----//
	int m_hdl = 0;

public:

	//-----ƒƒ“ƒoŠÖ”-----//
	void Play();
	void Stop();
};
