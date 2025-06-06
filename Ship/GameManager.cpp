#include "GameManager.h" 

GameManager::GameManager()
{
	playerLife = 3; 
	
	selectedShip = 0;
}

GameManager::~GameManager()
{

}

void GameManager::DamagePlayer(int damage)
{
	playerLife -= damage;
}

void GameManager::SetSelectedShip(int shipIndex)
{
	selectedShip = shipIndex;
}

int GameManager::GetSelectedShip()
{
	return selectedShip;
}

GameManager gameManager; 
