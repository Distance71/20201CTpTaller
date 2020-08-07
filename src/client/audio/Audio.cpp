#include "Audio.h"

Audio* Audio::instance = nullptr;

Audio* Audio::getInstance()
{
  if (instance == nullptr)
    instance = new Audio(80); //valores validos(0-128)
  return instance;
}

Audio::Audio(int volumen){
	//Inicializa SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		Logger::getInstance()->log(ERROR, "Error al inicializar SDL_mixer" );
	}
	Mix_VolumeMusic(volumen);

	//Precarga de todos los sonidos
	if ( (this->explosion = Mix_LoadWAV("assets/Sounds/explosion.wav")) == NULL ){
		Logger::getInstance()->log(ERROR,"Error al cargar el sonido 'explosion.wav'" );		
	}
	Mix_VolumeChunk(this->explosion, volumen);

	if ( (this->laser1 = Mix_LoadWAV("assets/Sounds/laser1.wav")) == NULL ){
		Logger::getInstance()->log(ERROR,"Error al cargar el sonido 'laser1.wav'" );		
	}
	Mix_VolumeChunk(this->laser1, volumen);

	if ( (this->laser2 = Mix_LoadWAV("assets/Sounds/explosion.wav")) == NULL ){
		Logger::getInstance()->log(ERROR,"Error al cargar el sonido 'laser2.wav'" );		
	}
	Mix_VolumeChunk(this->laser2, volumen);
	this->isPaused = false;
}

void Audio::setSong(const std::string& path){
	if( !(this->mixMusicSDL = Mix_LoadMUS(path.c_str())) )
		Logger::getInstance()->log(ERROR,"Error al cargar la musica" );
}

void Audio::playMusic(){
	if (Mix_PlayMusic(this->mixMusicSDL, -1) == -1){
		Logger::getInstance()->log(ERROR,"Error al reproducir la musica");
	}
}

void Audio::playEffect(soundType_t soundType){
	if (!this->isPaused) {
		switch (soundType)
		{
		case EXPLOSION:
			//-1 por q no importa el canal y 0 por que se debe repetir una sola vez el sonido
			if(this->explosion) Mix_PlayChannel(-1, this->explosion, 0);
			break;
		case LASER_1:
			if(this->laser1) Mix_PlayChannel(-1, this->laser1, 0);
			break;
		case LASER_2:
			if(this->laser2) Mix_PlayChannel(-1, this->laser2, 0);
			break;
		default:
			break;
		}
	}
}

void Audio::pause(){
    //If the music is paused
    if( Mix_PausedMusic() == 1){
        //Resume the music
        Mix_ResumeMusic();
		this->isPaused = false;
    }
    //If the music is playing
    else{
        //Pause the music
        Mix_PauseMusic();
		this->isPaused = true;
    }
}

void Audio::stop(){
	if (this->mixMusicSDL) Mix_HaltMusic();
}

void Audio::gradualStop(int milisegundos){
	if (this->mixMusicSDL) Mix_FadeOutMusic(milisegundos);
}

Audio::~Audio(){
	if (this->mixMusicSDL){
		Mix_FreeMusic(this->mixMusicSDL);
		this->mixMusicSDL = NULL;
	}
	if (this->explosion){
		Mix_FreeChunk(this->explosion);
	}
	if (this->laser1){
		Mix_FreeChunk(this->laser1);
	}
	if (this->laser2){
		Mix_FreeChunk(this->laser2);
	}
}