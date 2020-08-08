#ifndef AUDIO_H_
#define AUDIO_H_

#include "SDL2/SDL_mixer.h"
#include "../common/services/Logger.h"
#include "../../common/types.h"
#include <string>

class Audio {

private:
	//The sound effects that will be used
	Mix_Chunk *explosion = NULL;
	Mix_Chunk *laser1 = NULL;
	Mix_Chunk *laser2 = NULL;

	static Audio* instance;
	Mix_Music* mixMusicSDL;
	bool isPaused = false;
	bool isInitMusic = false;

	Audio(int volumen);

public:
	static Audio* getInstance();
	void setSong(const std::string& path);
	void playMusic();
	void playEffect(soundType_t soundType);
	void pause();
	void stop();
	void gradualStop(int milisegundos);
	~Audio();
};

#endif