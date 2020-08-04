#ifndef MUSIC_H_
#define MUSIC_H_

#include "SDL2/SDL_mixer.h"
#include "../common/services/Logger.h"
#include <string>
class Music {

private:
/* 	//The music that will be played
	Mix_Music *gMusic = NULL;

	//The sound effects that will be used
	Mix_Chunk *gScratch = NULL;
	Mix_Chunk *gHigh = NULL;
	Mix_Chunk *gMedium = NULL;
	Mix_Chunk *gLow = NULL; */

	static Music* instance;
	Mix_Music* mixMusicSDL;

	Music(int volumen);

public:
	static Music* getInstance();
	void setSong(const std::string& path);
	void play();
	void pause();
	void stop();
	void gradualStop(int milisegundos);
	~Music();
};

#endif