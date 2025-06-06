#ifndef __LE_AUDIO_H__
#define __LE_AUDIO_H__

#include <string>

#include <SDL2/SDL.h>

struct SFXdata
{
	int vol; 
	int audioPos; 
	int flag; 
	bool play; 
	Uint32 len;
	Uint8* audioBuffer; 
	SDL_AudioFormat format; 
};


class SFX
{
public: 
	SFX(std::string filename, int vol);
	SFX(std::string filename);
	SFX();
   ~SFX(); 
   
   	void freeMemory(); 
   	void play(bool randomChannel); 
   	void setVolume(int vol);
   	int load(std::string filename); 
   	
	static void StopAllSounds(); 
	static void SetAllVolumes(int vol);
private:

	void AudioDeviceInit(); 
	SFXdata callback_data; 
	//void SDLCALL AD_callback(void* userdata, Uint8* stream, int len); 
	int vol;
	Uint32 sfxLength; 
	Uint8* sfxBuffer; 
	SDL_AudioDeviceID sfxDevice; 
	SDL_AudioSpec     sfxSpec; 
};

#endif/*__LE_AUDIO_H__*/
