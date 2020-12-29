#include "SoundManager.h"


SoundManager::SoundManager()
	: system(nullptr) , sound(nullptr) , channels(nullptr), soundCount(0)
{
	this->Init();
}

SoundManager::~SoundManager()
{
}

HRESULT SoundManager::Init()
{
	// 사운드 시스템 생성
	System_Create(&system);
	// 채널 설정
	system->init(MaxChannels, FMOD_INIT_NORMAL, NULL);
	// 사운드 채널 동적할당
	sound =  new Sound*[MaxChannels];
	channels = new Channel*[MaxChannels];


	memset(sound,0, sizeof(Sound*) * MaxChannels);
	memset(channels, 0, sizeof(Channel*) * MaxChannels);
	return S_OK;
}

void SoundManager::Release()
{
	SAFE_ARR_DELETE(sound);
	SAFE_ARR_DELETE(channels);

	system->close();
	system->release();
	Super::ReleaseSingleton();
}

void SoundManager::Update()
{
	if (system)
		system->update();
}

void SoundManager::AddSound(string key, string fileName, bool isBGM, bool isLoop)
{
	if (soundCount == MaxChannels)
		return;
	if (isLoop)
	{
		if (isBGM)
			// 하나의 사운드만 재생이 된다.
			system->createStream(fileName.c_str(), FMOD_LOOP_NORMAL, 0, &sound[soundCount]);
		else
			system->createSound(fileName.c_str(), FMOD_LOOP_NORMAL, 0, &sound[soundCount]);
	}
	else
		// 사운드 옵션을 확인하자
		system->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &sound[soundCount]);
	if (sound[soundCount])
	{
		mapSoundData.insert(make_pair(key, &sound[soundCount]));
		soundCount++;
	}
	//system->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &sound[mapSoundData.size()]);
	//mapSoundData.insert(make_pair( key, &sound[mapSoundData.size()]));

}

void SoundManager::Play(string key, Volume volume)
{
	map<string, Sound**>::const_iterator c_it;
	int count = 0;
	for (c_it = mapSoundData.begin(); c_it != mapSoundData.end(); c_it++, count++)
	{
		if (c_it->first == key)
		{
			system->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_FREE, (*mapSoundData[key]), false, &channels[count]);
			channels[count]->setVolume(volume.c_float());
			break;
		}
		
	}


	//map<string, Sound**>::const_iterator c_it;
	//c_it = mapSoundData.find(key);
	//if (c_it == mapSoundData.end())
	//	return;
	//system->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_FREE, *c_it->second, false , channels[c_it->first]);
}

void SoundManager::Stop(string key)
{
	map<string, Sound**>::const_iterator c_it;
	int count = 0;
	for (c_it = mapSoundData.begin(); c_it != mapSoundData.end(); c_it++ , count++)
	{
		if (c_it->first == key)
		{
		
			channels[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string key)
{
	map<string, Sound**>::const_iterator c_it;
	int count = 0;
	bool isPlay = false;
	for (c_it = mapSoundData.begin(); c_it != mapSoundData.end(); c_it++, count++)
	{
		if (c_it->first == key)
		{
			channels[count]->isPlaying(&isPlay);
			if (isPlay)
				channels[count]->setPaused(true);
			
			break;
		}
	}
}

void SoundManager::Resume(string key)
{
	map<string, Sound**>::const_iterator c_it;
	int count = 0;
	bool isPlay = false;
	for (c_it = mapSoundData.begin(); c_it != mapSoundData.end(); c_it++, count++)
	{
		if (c_it->first == key)
		{
			channels[count]->isPlaying(&isPlay);
			if (isPlay)
				channels[count]->setPaused(false);

			break;
		}
	}
}

void SoundManager::SetVolume(string key, Volume volume)
{
	map<string, Sound**>::const_iterator c_it;
	int count = 0;
	bool isPlay = false;
	for (c_it = mapSoundData.begin(); c_it != mapSoundData.end(); c_it++, count++)
	{
		if (c_it->first == key)
		{
			channels[count]->isPlaying(&isPlay);
			if (isPlay)
				channels[count]->setVolume(volume.c_float());
			break;
		}
	}
}

Volume SoundManager::GetVolume(string key)
{
	float voluem;
	map<string, Sound**>::const_iterator c_it;
	int count = 0;
	bool isPlay = false;
	for (c_it = mapSoundData.begin(); c_it != mapSoundData.end(); c_it++, count++)
	{
		if (c_it->first == key)
		{
			channels[count]->isPlaying(&isPlay);
			if (isPlay)
				channels[count]->getVolume(&voluem);
			break;
		}
	}
	Volume returnVolume = voluem;
	return returnVolume;
}
