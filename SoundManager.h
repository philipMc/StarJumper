#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#pragma comment(lib, "fmodex_vc.lib")
#include "fmod.hpp"
#include <iostream>
#include "PickUp.h"

class SoundManager {
public:
	static SoundManager * instance();
	static FMOD::System * System();
	void update();
	void loadSounds();
	void setReverb(PickUp *);
	void powerUpSound();
	void playBackground();
	void playJump();
	FMOD::Sound * getConst();
	FMOD::Channel * getBGChannel();
	FMOD::Reverb * getReverb();

private:
	static SoundManager * m_instance;
	static FMOD::System * m_system;
	FMOD::Sound * powerUp;
	FMOD::Sound * background;
	FMOD::Sound * constant;
	FMOD::Sound * jump;
	FMOD::Channel * channelBG;
	FMOD::Reverb * reverb;
	SoundManager();
};
#endif