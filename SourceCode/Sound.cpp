#include "Game.h"
#include "Sound.h"
#include <tchar.h>
Sound* Sound::__Instance = NULL;

Sound::Sound()
{
	Init();
	LoadResourceSound();
}



void Sound::LoadResourceSound()
{
	AddSound(eSound::sound_ThrowApple, Convert("Resources/Sound/ThrowApple.wav"));
	AddSound(eSound::sound_AppleCollect, Convert("Resources/Sound/AppleCollect.wav"));
	AddSound(eSound::sound_GemCollect, Convert("Resources/Sound/GemCollect.wav"));
	AddSound(eSound::sound_HighSword, Convert("Resources/Sound/HighSword.wav"));
	AddSound(eSound::sound_ExtraHealth, Convert("Resources/Sound/ExtraHealth.wav"));
	AddSound(eSound::sound_GuardHit, Convert("Resources/Sound/GuardHit.wav"));	
	AddSound(eSound::sound_AppleSplat, Convert("Resources/Sound/AppleSplat.wav"));
	AddSound(eSound::sound_Skeleton, Convert("Resources/Sound/SKeleton.wav"));
	AddSound(eSound::sound_StoneRumble, Convert("Resources/Sound/StoneRumble.wav"));
	AddSound(eSound::sound_BonesTinkle, Convert("Resources/Sound/BonesTinkle.wav"));
	AddSound(eSound::sound_AladinPush, Convert("Resources/Sound/AladdinPush.wav"));
	AddSound(eSound::sound_GuardBeckon, Convert("Resources/Sound/GuardBeckon.wav"));
	AddSound(eSound::sound_Storyline, Convert("Resources/Sound/Storyline.wav"));
	AddSound(eSound::sound_Wow, Convert("Resources/Sound/Wow!.wav"));
	AddSound(eSound::sound_ContinuePoint, Convert("Resources/Sound/ContinuePoint.wav"));
	AddSound(eSound::sound_Iiee, Convert("Resources/Sound/Iiee.wav"));
	AddSound(eSound::sound_BossTune, Convert("Resources/Sound/BossTune.wav"));
	AddSound(eSound::sound_LevelComplete, Convert("Resources/Sound/LevelComplete.wav"));
	AddSound(eSound::sound_JafarLaugh, Convert("Resources/Sound/JafarLaugh.wav"));
	AddSound(eSound::sound_JafarSnake, Convert("Resources/Sound/JafarSnake.wav"));
	AddSound(eSound::sound_AladinHurt, Convert("Resources/Sound/AladdinHurt.wav"));
	
}

bool Sound::isPlaying(eSound type)
{
	return _ArrSound[type]->IsSoundPlaying();
}

LPTSTR Sound::Convert(LPCSTR path)
{
	const char* c_str = path;
	LPTSTR str = const_cast<LPTSTR>(c_str);
	return str;
}

void Sound::StopAll()
{
	for (auto& x : _ArrSound)
	{
		if (x.second->IsSoundPlaying())
			x.second->Stop();
	}
}


void Sound::AddSound(eSound type, LPTSTR filename)
{
	CSound *wave;
	HRESULT result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		return;
	}
	_ArrSound[type] = wave;
}

void Sound::Play(eSound type, bool isLoop, LONG lVolume)
{
	_ArrSound[type]->Play(0, isLoop, lVolume);
	//DSBPLAY_LOOPING             0x00000001 -> int = 1

}

void Sound::Stop(eSound type)
{
	_ArrSound[type]->Stop();
}



void Sound::Init()
{
	dsound = new CSoundManager();
	dsound->Initialize(CGame::GetInstance()->hWnd, DSSCL_PRIORITY);
	dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Sound * Sound::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Sound();
	return __Instance;
}