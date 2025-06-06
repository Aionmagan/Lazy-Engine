#include "input.h"

#include "timer.h" 
#include <math.h>

#define JOYPORT_RAY 4
#define JOYPORT_RAX 3

#define JOYDEADZONE 0.1

#define INDEXGP_AMOUNT 24
/*C to C++ translated code not C++ proper*/

const int INDEXGP[INDEXGP_AMOUNT]=
{
	0,   //back button
	1,   //A button
	2,   //d-pad up
	3,   //d-pad right
	4,   //d-pad down 
	5,  //d-pad left
	6, //useless
	7, //useless
	8, //useless
	9, //useless
	10,   //useless
	11,   //b button
	12,   //x button 
	13,   //y button
	14,
	15, 
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
};

int INDEXPC[INDEXGP_AMOUNT]=
{
	SDL_SCANCODE_SPACE,
	SDL_SCANCODE_RSHIFT,
	0x00,        
	0x00,
	0x00,
	0x00,
	SDL_SCANCODE_UP,
	SDL_SCANCODE_ESCAPE,
	SDL_SCANCODE_DOWN,
	SDL_SCANCODE_LSHIFT,
	SDL_SCANCODE_LSHIFT,
	SDL_SCANCODE_LEFT,
	SDL_SCANCODE_SPACE,
	SDL_SCANCODE_RIGHT,
	SDL_SCANCODE_LSHIFT,
	SDL_SCANCODE_LSHIFT,
	SDL_SCANCODE_LSHIFT,
	SDL_SCANCODE_LSHIFT,
	SDL_SCANCODE_LSHIFT,
	SDL_SCANCODE_LSHIFT,
	SDL_SCANCODE_LSHIFT,
	SDL_SCANCODE_LSHIFT,
}; 

Input::Input()
{
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	
	leftX = 0.0f; 
	leftY = 0.0f; 
	rightX = 0.0f; 
	rightY = 0.0f;
	
	isJoystick = false;  
	quit = false; 
	
	for (int i = 0; i < 322; ++i)
	{
		downKeys[i] = false;
		downButtons[i%24] = false; 
		upKeys[i] = false;
		upButtons[i%24] = false; 
		stateKeys[i] = false; //unchanged state by return functions; 
		stateButtons[i%24] = false;//unchanged state by return functions; 
	}
}

Input::~Input()
{

} 
   
void Input::update()
{
	if (SDL_NumJoysticks() > 0)
	{
		if (gamepad == NULL)
		{
			for(int i = 0; i < SDL_NumJoysticks(); ++i)
			{
				gamepad = SDL_JoystickOpen(i);
				
				if (gamepad != NULL) break; 
			}
		}
	}

	//REMEMBER THIS !!!	
	for(int i = 0; i < INDEXGP_AMOUNT; ++i)
	{
		downButtons[i] = false;
		downKeys[i] = false;
		upKeys[i] = false;
		upButtons[i] = false; 
	}
	
	if (isJoystick == false)
	{
		//rightX = rightX * gTime.deltaTime(); 
		//rightY = rightY * gTime.deltaTime();
				int x, y; 
				SDL_GetRelativeMouseState(&x, &y);
				//printf("x %d | y %d\n", x, y);
				rightX = x*0.0752f;
				rightY = y*0.0752f;
	}
	
	//static int prev_x, prev_y;
	//static int curr_x, curr_y; 
	
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				quit = true; 
				break; 
				
			case SDL_MOUSEMOTION:
				isJoystick = false; 
				
				//rightX = event.motion.xrel;//*12.0f;
				//rightY = event.motion.yrel;//*12.0f;
				//rightX = event.motion.xrel*0.52f;
				//rightY = event.motion.yrel*0.52f;
				
				//int x, y; 
				//SDL_GetRelativeMouseState(&x, &y);
				
				//rightX = x*0.52f;
				//rightY = y*0.52f;
				//if((x+y)!=0)
				
				//printf("x %d | y %d\n", x, y);
				//printf("x2 %d | y2 %d\n", event.motion.xrel, event.motion.yrel);
				break;
				
			case SDL_KEYDOWN:
				isJoystick = false;
				
				//if (event.key.repeat == 0)
					downKeys[event.key.keysym.scancode] = true;
					//currentKeys[event.key.keysym.scancode] = (stateKeys[event.key.keysym.scancode] != true) ? true : false;
					stateKeys  [event.key.keysym.scancode] = true;
					
				if (event.key.keysym.scancode == SDL_SCANCODE_A)
					leftX = -1.0f; 
				if (event.key.keysym.scancode == SDL_SCANCODE_D)
					leftX =  1.0f;
				
				if (event.key.keysym.scancode == SDL_SCANCODE_W)
					leftY = -1.0f; 
				if (event.key.keysym.scancode == SDL_SCANCODE_S)
					leftY =  1.0f;				
				break; 
				
			case SDL_KEYUP:
				isJoystick = false; 
				
				upKeys[event.key.keysym.scancode] = true;
				//currentKeys[event.key.keysym.scancode] = (stateKeys[event.key.keysym.scancode] != false) ? false : true;
				stateKeys  [event.key.keysym.scancode] = false;
				
				if (event.key.keysym.scancode == SDL_SCANCODE_A && leftX < 0.0f)
					leftX = 0; 
				if (event.key.keysym.scancode == SDL_SCANCODE_D && leftX > 0.0f)
					leftX = 0; 
						
				if (event.key.keysym.scancode == SDL_SCANCODE_W && leftY < 0.0f)
					leftY = 0; 
				if (event.key.keysym.scancode == SDL_SCANCODE_S && leftY > 0.0f)
					leftY = 0; 
				break;
				
			case SDL_JOYBUTTONDOWN:
				isJoystick = true; 
				
				if (event.jbutton.button < 16)
				{
					downButtons[event.jbutton.button] = true;
					//currentButtons[event.jbutton.button] = (stateButtons[event.jbutton.button] != true) ? true : false;
					//printf("CB = %d | SB = %d\n", currentButtons[event.jbutton.button],stateButtons  [event.jbutton.button]  );
					stateButtons  [event.jbutton.button] = true;
					
					//printf("button = %d\n", event.jbutton.button);
					//printf("scancode = %d\n", event.key.keysym.scancode); 
				//printf("curButton = %d\n", currentButtons[event.jbutton.button]);
					//printf("satButton = %d\n", stateButtons[event.jbutton.button]);
				}
				break; 
				
			case SDL_JOYBUTTONUP:
				isJoystick = true; 
				
				if (event.jbutton.button < 16)
				{
					upButtons[event.jbutton.button] = true;
					//currentButtons[event.jbutton.button] = (stateButtons[event.jbutton.button] != false) ? false : true;
					stateButtons  [event.jbutton.button] = false;
					
					//printf("button = %d\n", event.jbutton.button);
					//printf("scancode = %d\n", event.key.keysym.scancode); 
				 //printf("curButton = %d\n", currentButtons[event.jbutton.button]);
					//printf("satButton = %d\n", stateButtons[event.jbutton.button]);
				}
				break;
				
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED:
				printf("Device update\n");
				break;
				
			case SDL_JOYAXISMOTION:
				isJoystick = true;
				
				if (event.jaxis.which == 0)
				{
					if( event.jaxis.axis == 0 )
                		leftX = event.jaxis.value/32767.0f; 
						
						
					if( event.jaxis.axis == 1)				
						leftY = event.jaxis.value/32767.0f; 
						
						
					if( event.jaxis.axis == JOYPORT_RAX )                		
						rightX = event.jaxis.value/32767.0f; 
						
						
					if( event.jaxis.axis == JOYPORT_RAY)
						rightY = event.jaxis.value/32767.0f; 
						
#if 0					
					for(int i = 0; i < 16; ++i)
					{
						if (event.jaxis.axis == i)
					printf("event.jaxis.axis = %d | %d\n", i, event.jaxis.value);
					}					
#endif				
				}
				break;
				
			case SDL_JOYHATMOTION:
				isJoystick = true; 
				static int diagonalCheck = 0; 
				
				if (event.jhat.which == 0)
				{
					if (event.jhat.hat == 0)
					{
					//printf("hat value %d\n", event.jhat.value);
						switch(event.jhat.value)
						{
							case 0: //dpad is centere (no buttons pressed)
								for(int i = 19; i < 24; ++i)
								{
									if (stateButtons[i])
										upButtons[i] = true; 
										
									 downButtons[i] = false;
									 stateButtons[i] = false;
								}
								break;
							case 1: //dpad is up
								downButtons [INDEXGP[BN_UP]] = true;
								stateButtons[INDEXGP[BN_UP]] = true;
								
								if (diagonalCheck == 3)
									upButtons[INDEXGP[BN_RIGHT]] = true; 
								else if (diagonalCheck == 9)
									upButtons[INDEXGP[BN_LEFT]] = true;
									
								break;
							case 2: //dpad is right
								downButtons [INDEXGP[BN_RIGHT]] = true;
								stateButtons[INDEXGP[BN_RIGHT]] = true;	
								
								if (diagonalCheck == 3)
									upButtons[INDEXGP[BN_UP]] = true; 
								else if (diagonalCheck == 6)
									upButtons[INDEXGP[BN_DOWN]] = true;
															
								break;
							case 4: //dpad is down
								downButtons [INDEXGP[BN_DOWN]] = true;
								stateButtons[INDEXGP[BN_DOWN]] = true;
								
								if (diagonalCheck == 6)
									upButtons[INDEXGP[BN_RIGHT]] = true; 
								else if (diagonalCheck == 12)
									upButtons[INDEXGP[BN_LEFT]] = true;
									
								break;
							case 8: //dpad is left
								downButtons [INDEXGP[BN_LEFT]] = true;
								stateButtons[INDEXGP[BN_LEFT]] = true;							
								
								if (diagonalCheck == 9)
									upButtons[INDEXGP[BN_UP]] = true; 
								else if (diagonalCheck == 12)
									upButtons[INDEXGP[BN_DOWN]] = true;
									
								break;
							case 3: //dpad is up right
								downButtons [INDEXGP[BN_UP]] = true;
								stateButtons[INDEXGP[BN_UP]] = true;
								downButtons [INDEXGP[BN_RIGHT]] = true;
								stateButtons[INDEXGP[BN_RIGHT]] = true;
								break;
							case 6: //dpad is down right 
								downButtons [INDEXGP[BN_DOWN]] = true;
								stateButtons[INDEXGP[BN_DOWN]] = true;
								downButtons [INDEXGP[BN_RIGHT]] = true;
								stateButtons[INDEXGP[BN_RIGHT]] = true;							
								break;
							case 12: //dpad is down left 
								downButtons [INDEXGP[BN_DOWN]] = true;
								stateButtons[INDEXGP[BN_DOWN]] = true;
								downButtons [INDEXGP[BN_LEFT]] = true;
								stateButtons[INDEXGP[BN_LEFT]] = true;							
								break;
							case 9: //dpad is up left 
								downButtons [INDEXGP[BN_UP]] = true;
								stateButtons[INDEXGP[BN_UP]] = true;
								downButtons [INDEXGP[BN_LEFT]] = true;
								stateButtons[INDEXGP[BN_LEFT]] = true;							
								break;
							default:break;
						}
						diagonalCheck = event.jhat.value; 
					
					/*
						switch(event.jhat.value)
						{
								case 1:
									currentButtons[7] = true;
									break;
								case 2:
									currentButtons[8] = true; 
									break;
								case 4:
									currentButtons[9] = true; 
									break;
								case 8:
									currentButtons[10]= true; 
									break;
								default:break; 
						} 
					*/
					}
				}
				break;
		   default:break;
		}
	}
}   

float Input::lxAxis()
{
	leftX = (fabs(leftX) < JOYDEADZONE) ? 0 : leftX;
	return leftX; 
}

float Input::lyAxis()
{
	leftY = (fabs(leftY) < JOYDEADZONE) ? 0 : leftY;
	return leftY; 
}

float Input::rxAxis()
{
	rightX = (fabs(rightX) < JOYDEADZONE) ? 0 : rightX; 
	return rightX; 
}

float Input::ryAxis() 
{
	rightY = (fabs(rightY) < JOYDEADZONE) ? 0 : rightY; 
	return rightY; 
}
    
bool Input::button(ButtonIds button)
{
	if (stateButtons[INDEXGP[button]])return true;
	if (stateKeys   [INDEXPC[button]])return true;
	
	return false;
}

bool Input::buttonDown(ButtonIds button)
{
//printf("%d\n", button);
//printf("button id = %d\n", currentButtons[INDEXGP[button]]); 
	if (downButtons[INDEXGP[button]])
	{
		//currentButtons[INDEXGP[button]] = false;
		return true;
		//return currentButtons[INDEXGP[button]];
	}
	
	if (downKeys   [INDEXPC[button]])
	{
		//currentKeys   [INDEXPC[button]] = false;
		return true;
	}
	
	return false;
}

bool Input::buttonUp(ButtonIds button)
{
	if (upButtons[INDEXGP[button]])
	{
		//currentButtons[INDEXGP[button]] = false;
		return true;
		//return currentButtons[INDEXGP[button]];
	}
	
	if (upKeys   [INDEXPC[button]])
	{
		//currentKeys   [INDEXPC[button]] = false;
		return true;
	}
	
	return false;
}
    
bool Input::eventQuit()
{
	return quit; 
}

Input gInput; 
