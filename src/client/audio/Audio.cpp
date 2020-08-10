#include "Audio.h"

Audio* Audio::instance = nullptr;

Audio* Audio::getInstance()
{
  if (instance == nullptr)
    instance = new Audio(VOLUME_DEFAULT); //valores validos(0-128)
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

	if ( (this->playerShot = Mix_LoadWAV("assets/Sounds/playerShot.wav")) == NULL ){
		Logger::getInstance()->log(ERROR,"Error al cargar el sonido 'playerShot.wav'" );		
	}
	Mix_VolumeChunk(this->playerShot, volumen);

	if ( (this->shotImpacts = Mix_LoadWAV("assets/Sounds/impacto.wav")) == NULL ){
		Logger::getInstance()->log(ERROR,"Error al cargar el sonido 'impacto.wav'" );		
	}
	Mix_VolumeChunk(this->shotImpacts, volumen);

	// if ( (this->stageOne = Mix_LoadWAV("assets/Sounds/explosion.wav")) == NULL ){
	// 	Logger::getInstance()->log(ERROR,"Error al cargar el sonido 'laser2.wav'" );		
	// }
	// Mix_VolumeChunk(this->stageOne, volumen);

	// if ( (this->stageTwo = Mix_LoadWAV("assets/Sounds/explosion.wav")) == NULL ){
	// 	Logger::getInstance()->log(ERROR,"Error al cargar el sonido 'laser2.wav'" );		
	// }
	// Mix_VolumeChunk(this->stageTwo, volumen);

	// if ( (this->stageThree = Mix_LoadWAV("assets/Sounds/explosion.wav")) == NULL ){
	// 	Logger::getInstance()->log(ERROR,"Error al cargar el sonido 'laser2.wav'" );		
	// }
	// Mix_VolumeChunk(this->stageThree, volumen);

	// if ( (this->stageFour = Mix_LoadWAV("assets/Sounds/explosion.wav")) == NULL ){
	// 	Logger::getInstance()->log(ERROR,"Error al cargar el sonido 'laser2.wav'" );		
	// }
	// Mix_VolumeChunk(this->stageFour, volumen);


	this->isPaused = false;
	this->isInitMusic = false;
}

void Audio::setSong(const std::string& path){
	if( !(this->mixMusicSDL = Mix_LoadMUS(path.c_str())) )
		Logger::getInstance()->log(ERROR,"Error al cargar la musica" );
}

void Audio::playMusic(){
	if (!this->isPaused) {
		if (Mix_PlayMusic(this->mixMusicSDL, -1) == -1){
			Logger::getInstance()->log(ERROR,"Error al reproducir la musica");
		}
		this->isInitMusic = true;
	}
}

void Audio::playEffect(musicType_t soundType){
	if (!this->isPaused) {
		switch (soundType) {
		case EXPLOSION:
			//-1 por q no importa el canal y 0 por que se debe repetir una sola vez el sonido
			if(this->explosion) Mix_PlayChannel(-1, this->explosion, 0);
			break;
		case PLAYER_SHOT:
			if(this->playerShot) Mix_PlayChannel(-1, this->playerShot, 0);
			break;
		case SHOT_IMPACTS:
			if(this->shotImpacts) Mix_PlayChannel(-1, this->shotImpacts, 0);
			break;
		
		// case SOUND_STAGE_ONE:
		// 	if(this->stageOne) Mix_PlayChannel(-1, this->stageOne, 0);
		// 	break;
		// case SOUND_STAGE_TWO:
		// 	if(this->stageTwo) Mix_PlayChannel(-1, this->stageTwo, 0);
		// 	break;
		
		// case SOUND_STAGE_THREE:
		// 	if(this->stageThree) Mix_PlayChannel(-1, this->stageThree, 0);
		// 	break;
		
		// case SOUND_STAGE_FOUR:
		// 	if(this->stageFour) Mix_PlayChannel(-1, this->stageFour, 0);
		// 	break;

		default:
			break;
		}
	}
}

void Audio::pause(){
    //If the music is paused
	 //if( Mix_PausedMusic() == 1){
    if(this->isPaused){
		this->isPaused = false;
/*  		if (this->isInitMusic){
			//Resume the music
			//Mix_ResumeMusic();
			Mix_VolumeMusic(VOLUME_DEFAULT);
		}else{
			//Inicia el nuevo tema
			this->playMusic();
			Mix_VolumeMusic(VOLUME_DEFAULT);

			//Mix_SetMusicPosition(60.0); ejemplo de setPosition
		} */
		Mix_VolumeMusic(VOLUME_DEFAULT);
    }
    //If the music is playing
    else{
        //Pause the music
        //Mix_PauseMusic();
		Mix_VolumeMusic(0);
		this->isPaused = true;
    }
}

void Audio::stop(){
	if (this->mixMusicSDL) Mix_HaltMusic();
	this->isInitMusic = false;
}

void Audio::gradualStop(int milisegundos){
	if (!this->isPaused) {
		if (this->mixMusicSDL) Mix_FadeOutMusic(milisegundos);
	} else {
		this->stop();
	}
	this->isInitMusic = false;
}

Audio::~Audio(){
	if (this->mixMusicSDL){
		Mix_FreeMusic(this->mixMusicSDL);
		this->mixMusicSDL = NULL;
	}
	if (this->explosion){
		Mix_FreeChunk(this->explosion);
	}
	if (this->playerShot){
		Mix_FreeChunk(this->playerShot);
	}
	if (this->shotImpacts){
		Mix_FreeChunk(this->shotImpacts);
	}
	// if (this->stageOne){
	// 	Mix_FreeChunk(this->stageOne);
	// }
	// if (this->stageTwo){
	// 	Mix_FreeChunk(this->stageTwo);
	// }
	// if (this->stageThree){
	// 	Mix_FreeChunk(this->stageThree);
	// }
	// if (this->stageFour){
	// 	Mix_FreeChunk(this->stageFour);
	// }
}