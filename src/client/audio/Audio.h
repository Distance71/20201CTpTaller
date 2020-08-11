#ifndef AUDIO_H_
#define AUDIO_H_

#include "SDL2/SDL_mixer.h"
#include "../common/services/Logger.h"
#include "../../common/types.h"
#include <string>

class Audio {

private:
	//The sound effects that will be used
	Mix_Chunk *explosionEnemy = NULL;
	Mix_Chunk *shotImpacts = NULL;
	Mix_Chunk *enemyShot = NULL;

	Mix_Chunk *playerShot = NULL;
	Mix_Chunk *explosionPlayer = NULL;
	Mix_Chunk *shotImpactsPlayer = NULL;

	Mix_Chunk *explosionBoss = NULL;
	Mix_Chunk *bossShot = NULL;
	Mix_Chunk *shotImpactsBoss = NULL;

	Mix_Chunk *reconexionPlayer = NULL;

	static Audio* instance;
	Mix_Music* mixMusicSDL;
	bool isPaused = false;
	bool isInitMusic = false;
	static const int VOLUME_DEFAULT = 60;
	static const int VOLUME_SOUNDS_DEFAULT = 110;

	Audio(int volumen);

public:
	static Audio* getInstance();
	void setSong(const std::string& path);
	void playMusic();
	void playEffect(musicType_t musicType);
	void pause();
	void stop();
	void gradualStop(int milisegundos);
	~Audio();
};

#endif