#include "SoundManager.h"

SoundManager * SoundManager::m_instance = 0;
 FMOD::System *SoundManager::m_system = 0;

SoundManager * SoundManager::instance() {
	if(!m_instance)
		m_instance = new SoundManager();
	return m_instance;
}

//static FMOD::System * System();
FMOD::System * SoundManager::System() {
	return m_system;
}

SoundManager::SoundManager() {
	FMOD_RESULT result;

		//create main system object
		result = FMOD::System_Create(&m_system);

		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (%d) %s\n" <<result;// << FMOD_ErrorString(result);
			exit(-1);
		}

		result = m_system->init(100, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (%d) %s\n" << result;// << FMOD_ErrorString(result);
			exit(-1);
		}
		loadSounds();
		FMOD_REVERB_PROPERTIES revProp = FMOD_PRESET_UNDERWATER;
		m_system->setReverbAmbientProperties(&revProp);
}

//void loadSounds();
void SoundManager::loadSounds() {
	FMOD_RESULT result = m_system->createSound("C:/Users/lab422/Dropbox/projects/Sounds/powerup.wav", FMOD_DEFAULT, 0, &powerUp);
	result = m_system->createStream("C:/Users/lab422/Dropbox/projects/Sounds/bg.wav", FMOD_LOOP_NORMAL|FMOD_3D, 0, &background);
	result = m_system->createSound("C:/Users/lab422/Dropbox/projects/Sounds/constant.wav", FMOD_LOOP_NORMAL|FMOD_3D, 0, &constant);
	result = m_system->createSound("C:/Users/lab422/Dropbox/projects/Sounds/jump.wav", FMOD_DEFAULT, 0, &jump);	
}

//void playSound();
void SoundManager::powerUpSound() {	
	m_system->playSound(FMOD_CHANNEL_FREE, powerUp, false, 0);
}

void SoundManager::playJump()
{
	m_system->playSound(FMOD_CHANNEL_FREE, jump, false, 0);
}

//void playBackground(FMOD::Channel *);
void SoundManager::playBackground()
{	
	m_system->playSound(FMOD_CHANNEL_FREE, background, false, &channelBG);	
	channelBG->set3DMinMaxDistance(10000,100000);
}

FMOD::Sound * SoundManager::getConst()
{
	return constant;
}

//FMOD::Channel * getBGChannel();
FMOD::Channel * SoundManager::getBGChannel()
{
	return channelBG;
}

void SoundManager::update() {
	m_system->update();
}

//void setReverb(PickUp *);
void SoundManager::setReverb(PickUp * rev)
{
	m_system->createReverb(&reverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_PADDEDCELL;
	reverb->setProperties(&prop);
	Vector3 revSource = rev->getPosition();
	FMOD_VECTOR revPos = {revSource.x, revSource.y, revSource.z};	
	float mindist = 100.0f;
	float maxdist = 250.0f;
	reverb->set3DAttributes(&revPos, mindist, maxdist);
	reverb->setActive(true);
}

//FMOD::Reverb * getReverb();
FMOD::Reverb * SoundManager::getReverb()
{
	return reverb;
}