#include "audio.h"
#include <cstring>

#include <vector> //used to fix "StopAllSound" 
//static int openStreams = 0; 
//SDL_AudioDeviceID sfxDevice; 
//SDL_AudioSpec     sfxSpec; 
#define REPEAT_AUDIO 0
#define ONESHOT_AUDIO 1

static std::vector<SDL_AudioDeviceID> audioDevList;

void SDLCALL AD_callback(void* userdata, Uint8* stream, int len)
{
	SFXdata* d = (SFXdata*)userdata;
     // I have audio data in a global, MyAudioBuffer, that I want to adjust and copy into stream...
     // you have to initialize `stream` to silence first, because we're mixing into it!
     SDL_memset(stream, 0, len);
     
     if (!d->play) return;
     //memcpy(stream,&d->audioBuffer[d->audioPos],len);
     SDL_MixAudioFormat(stream, &d->audioBuffer[d->audioPos], d->format, len, d->vol);
     d->audioPos += len; 
     
     if (d->audioPos >= d->len) //d->audioPos = d->len;
     {
     	if (d->flag == REPEAT_AUDIO)
     	{
     		d->audioPos = 0;
     	}else if (d->flag == ONESHOT_AUDIO)
     	{
     		d->play = false;
     		d->audioPos = d->len; 
     	}
     }
     //printf("mah niega | vol = %d | len = %d\n", d->vol, d->audioPos);
}

void SFX::AudioDeviceInit()
{
	//if (openStreams == 0)
	{
		//sfxSpec.format = AUDIO_S16;
		//sfxSpec.channels = 2; 
		//sfxSpec.samples = 128; 
		//sfxSpec.freq = 8000; 
		//sfxSpec.silence = (int)(128*(vol*0.01f));
		//Uint8 des[sfxLength]; 
		//SDL_MixAudio(des, sfxBuffer, sfxLength, vol);
		//memcpy(sfxBuffer, des, sfxLength);
		//sfxSpec.freq = 44100;
		//sfxSpec.format = AUDIO_S16;
		//sfxSpec.channels = 2;
		sfxSpec.samples = 2048;
		//sfxSpec.silence = (int)(128*(vol*0.01f));
		
		//printf("frag = %d\n", sfxSpec.freq);
		//printf("format = %d\n", sfxSpec.format);
		//printf("channels = %d\n", sfxSpec.channels);
		//printf("sfxSpec = %d\n", sfxSpec.samples);
		callback_data.vol = vol; 
		callback_data.audioBuffer = sfxBuffer;
		callback_data.audioPos = 0;
		callback_data.format = sfxSpec.format; 
		callback_data.len = sfxLength; 
		sfxSpec.callback = AD_callback;
		sfxSpec.userdata = &callback_data;
		
		//printf("vol = %d\n", sfxBuffer[4]);
		sfxDevice = SDL_OpenAudioDevice(NULL, 0, &sfxSpec, &sfxSpec, SDL_AUDIO_ALLOW_ANY_CHANGE); 
		//printf("vol = %d\n", sfxSpec.silence);
		//SDL_MixAudio(sfxBuffer, sfxBuffer, sfxLength, vol);
		printf("AUDIO DEVICE INIT \n"); 
		audioDevList.push_back(sfxDevice); 
	}
	//openStreams++; 
}

SFX::SFX(std::string filename, int vol)
{
	//AudioDeviceInit(vol);
	this->vol = vol;	
	load(filename);
}

SFX::SFX(std::string filename)
{
	//AudioDeviceInit(100);
	this->vol = 100; 
	load(filename);
}

SFX::SFX()
{
	//AudioDeviceInit(100);
	this->vol = 100;
}

SFX::~SFX()
{
	//openStreams--; 
	//if (openStreams == 0)
	//{
	freeMemory();
	// }
}

void SFX::play(bool randomChannel)
{
	if (!randomChannel)
	{
		Uint32 q = SDL_GetQueuedAudioSize(sfxDevice);

		if (q <= sfxLength)
		{
			SDL_QueueAudio(sfxDevice, sfxBuffer, sfxLength);
			SDL_PauseAudioDevice(sfxDevice, 0);  
		}
		callback_data.flag = REPEAT_AUDIO;
		callback_data.play = true;
	}else 
	{
		SDL_ClearQueuedAudio(sfxDevice);
		SDL_QueueAudio(sfxDevice, sfxBuffer, sfxLength);
		SDL_PauseAudioDevice(sfxDevice, 0);  
		
		callback_data.flag = ONESHOT_AUDIO;
		callback_data.audioPos = 0;
		callback_data.play = true;
	}
	
		//callback_data.vol = vol; 
		//callback_data.audioBuffer = sfxBuffer;
		//sfxSpec.callback = AD_callback;
		sfxSpec.userdata = &callback_data;
}

int SFX::load(std::string filename)	
{ 
	if (SDL_LoadWAV(filename.c_str(), &sfxSpec, &sfxBuffer, &sfxLength)==NULL)
	{
		printf("audio file not found\n %s", SDL_GetError());
		return -1; 
	}
	AudioDeviceInit();
	printf("file loaded\n"); 
	return 0; 
}

void SFX::freeMemory()
{	
	if (sfxBuffer == NULL) return; 
	
	SDL_PauseAudioDevice(sfxDevice, 1);
	SDL_ClearQueuedAudio(sfxDevice);
	SDL_CloseAudioDevice(sfxDevice); 
	SDL_FreeWAV(sfxBuffer);
	sfxBuffer = NULL; 
}

void SFX::StopAllSounds()
{
//	for(int i = 0; i < audioDevList.size(); ++i)
//	{
//		SDL_PauseAudioDevice(audioDevList[i], 1);
//		SDL_ClearQueuedAudio(audioDevList[i]);
//	}
}

void SFX::SetAllVolumes(int vol)
{

}

void SFX::setVolume(int vol)
{
	//Uint8 des[sfxLength]; 
	//SDL_MixAudio(des, sfxBuffer, sfxLength, vol);
	//memcpy(sfxBuffer, des, sfxLength);
	this->vol = vol;
	callback_data.vol = vol; 
		//sfxSpec.callback = AD_callback;
	//sfxSpec.userdata = &callback_data;
}
