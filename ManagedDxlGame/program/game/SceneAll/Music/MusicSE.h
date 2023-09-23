#pragma once
#include "../engine/GameEngine.h"

class MusicSE
{
public:

	MusicSE(const std::string& path);
	~MusicSE();

private:

	//-----ƒƒ“ƒo•Ï”-----//
	int m_hdl = 0;

public:

	//-----ƒƒ“ƒoŠÖ”-----//
	void Play();
	void Stop();


};
