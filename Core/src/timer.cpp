#include "timer.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

static float delta_time = 0; 
static unsigned int new_time, old_time; 

Time::Time()
{
	srand(time(NULL)); 
	old_time = getTicks(); 
}
 
Time::~Time()
{

}

float Time::deltaTime()
{
	return delta_time/1000.0f; 
}

float Time::frameRate()
{
	return (1.0 / delta_time) * 1000.0f;
}

unsigned long Time::getTicks()
{
	return (unsigned long) SDL_GetTicks(); 
}

void Time::update()
{
	new_time = getTicks(); 
	delta_time = (new_time - old_time); 
	old_time = new_time; 
}

Time gTime; 
