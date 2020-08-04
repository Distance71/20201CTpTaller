#include "Music.h"

Music* Music::instance = nullptr;

Music* Music::getInstance()
{
  if (instance == nullptr)
    instance = new Music(80); //valores validos(0-128)
  return instance;
}

Music::Music(int volumen){
	//Inicializa SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		Logger::getInstance()->log(ERROR, "Error al inicializar SDL_mixer" );
	}
	Mix_VolumeMusic(volumen);
}

void Music::setSong(const std::string& path){
	if( !(this->mixMusicSDL = Mix_LoadMUS(path.c_str())) )
		Logger::getInstance()->log(ERROR,"Error al cargar la musica" );
}

void Music::play(){
	if (Mix_PlayMusic(this->mixMusicSDL, -1) == -1){
		Logger::getInstance()->log(ERROR,"Error al reproducir la musica");
	}
}

void Music::pause(){
    //If the music is paused
    if( Mix_PausedMusic() == 1){
        //Resume the music
        Mix_ResumeMusic();
    }
    //If the music is playing
    else{
        //Pause the music
        Mix_PauseMusic();
    }
}

void Music::stop(){
	if (this->mixMusicSDL) Mix_HaltMusic();
}

void Music::gradualStop(int milisegundos){
	if (this->mixMusicSDL) Mix_FadeOutMusic(milisegundos);
}

Music::~Music(){
	if (this->mixMusicSDL){
		Mix_FreeMusic(this->mixMusicSDL);
		this->mixMusicSDL = NULL;
	}
}