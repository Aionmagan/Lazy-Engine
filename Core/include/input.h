#ifndef __INPUT_H__
#define __INPUT_H__

#include <SDL2/SDL.h>

enum ButtonIds
{
	BN_LEFT     = 19,
	BN_DOWN     = 20,
	BN_RIGHT    = 21,
	BN_UP       = 22,
	BN_START    = 7,
	BN_R3       = 10,
	BN_L3       = 9,
	BN_SELECT   = 6,
	BN_SQUARE   = 2,
	BN_CROSS    = 0,
	BN_CIRCLE   = 1,
	BN_TRIANGLE = 3,
	BN_R1       = 5,
	BN_L1       = 4,
	BN_R2       = 11,
	BN_L2       = 12
};

class Input
{
public: 
	Input(); 
   ~Input(); 
	
	void  setPort(int p);    
    void  update(); 
    
    float lxAxis(); 
    float lyAxis(); 
    float rxAxis(); 
    float ryAxis(); 
    
    bool button(ButtonIds button); 
    bool buttonDown(ButtonIds button);
    bool buttonUp(ButtonIds button); //implement later
    
    bool eventQuit(); //should be it's own thing
    
    void Init(); 
    //void PS2Mode(); 
    
private: 
	bool  quit; 
	int   isDown;
	int   isUp;
		
	SDL_Event event; 	
	SDL_Joystick* gamepad = NULL; //for later
	float leftX; 
	float leftY; 
	float rightX; 
	float rightY;
	
	bool isJoystick;  
	
	bool downKeys[322];
	bool downButtons[24];
	bool upKeys[322];
	bool upButtons[24]; 
	bool stateKeys[322]; //unchanged state by return functions; 
	bool stateButtons[24];//unchanged state by return functions; 
};

extern Input gInput; 

#endif/*__INPUT_H__*/
