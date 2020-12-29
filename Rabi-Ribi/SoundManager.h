#pragma once
#include "Singleton.h"

#include "pch.h"
#include "Volume.h"
// FMOD
#ifdef _WIN64
#pragma comment (lib,"lib/fmodex64_vc.lib")
#elif _WIN32
#pragma comment (lib,"lib/fmodex_vc.lib")
#endif // _WIN64
#include "inc/fmod.hpp"




using namespace FMOD;
const UINT MaxChannels = 10;
class SoundManager : public Singleton<SoundManager>
{
	SUPER(Singleton<SoundManager>)
public:
	SoundManager();
	virtual ~SoundManager();

	HRESULT Init();
	void Release();
	void Update();


	void AddSound(string key, string fileName, bool isBGM = false, bool isLoop = false);
	void Play(string key, Volume volume = 1.0f);  // 볼륨 0.0f~ 1.0f;
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);


	void SetVolume(string key, Volume volume = 1.0f);
	Volume GetVolume(string key);
private:
	// FMOD라이브러리 제어;
	System* system;
	// 음원
	Sound** sound; 
	// 출력 사운드 관리
	Channel** channels;

	map<string, Sound**> mapSoundData;
	UINT soundCount;
};



