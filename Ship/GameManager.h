#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

class GameManager
{
public: 
	GameManager();
   ~GameManager();

	void DamagePlayer(int damage);
	void SetSelectedShip(int shipIndex);
	int GetSelectedShip();
private:
   int playerLife; 
   int selectedShip; 
};

extern GameManager gameManager;

#endif/*__GAME_MANAGER_H__*/
