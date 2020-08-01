#ifndef __SOUND_H__
#define __SOUND_H__

#include "dsutil.h"
#include <unordered_map>



enum eSound
{
	sound_ThrowApple = 1,
	sound_AppleCollect=2,
	sound_HighSword=3,
	sound_GemCollect=4,
	sound_ExtraHealth=5,
	sound_GuardHit=6,
	sound_AppleSplat=7,
	sound_Skeleton=8,
	sound_StoneRumble=9,
	sound_BonesTinkle=10,
	sound_AladinPush=11,
	sound_GuardBeckon=12,
	sound_Storyline=13,
	sound_Story=14,
	sound_Wow=15,
	sound_ContinuePoint=16,
	sound_Iiee=17,
	sound_BossTune=18,
	sound_LevelComplete=19,
	sound_JafarLaugh=20,
	sound_JafarSnake = 21,
	sound_AladinHurt=22
};


class Sound
{
private:
	unordered_map<eSound, CSound* > _ArrSound;

public:
	static Sound * __Instance;
	static Sound * GetInstance();


	CSoundManager *dsound;

	void Init();
	Sound();

	void AddSound(eSound type, LPTSTR filename);
	void Play(eSound type, bool isLoop = false, LONG lVolume = 0L);
	void Stop(eSound type);
	void LoadResourceSound();

	bool isPlaying(eSound type);

	LPTSTR Convert(LPCSTR path);
	void StopAll();

};

#endif

