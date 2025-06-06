#include "Player.h" 
#include <cstdio>

#include "GameManager.h" 

Player::Player()
{
	char str[512];
	sprintf(str, "Assets/Ship%d.obj", gameManager.GetSelectedShip());
	std::string filename(str);
	playerMod.load(filename); 
	
	sprintf(str, "Assets/Ship%d.png", gameManager.GetSelectedShip());
	filename = str; 
	playerTex.load(filename); 
	
	playerShader.load("Shader/mm_normal_vs.glsl", "Shader/mm_normal_fs.glsl");
	player.reference(playerMod, playerTex, playerShader);
	
	auto q = Quaternion::Euler(-90, 0, 0);
	player.transform.rotation = Quaternion::Euler(0, 180, 0) * q;
	
	gRenderer.queue(player);
}

Player::~Player()
{

}

void Player::update()
{
	auto v = Vector3(gInput.lxAxis(), -gInput.lyAxis(), 0);	
	player.transform.position += v; 
	
	if (player.transform.position.x < -67.0f)
		player.transform.position.x = -67.0f;
	if (player.transform.position.x > 67.0f)
		player.transform.position.x = 67.0f;
		
	if (player.transform.position.y > -11.0f)
		player.transform.position.y = -11.0f; 
	if (player.transform.position.y < -32.0f)
		player.transform.position.y = -32.0f;
	//X = -67 67
	//Y = -11 -32
	float offsetX = 20 * gInput.lyAxis();
	float offsetY = 30 * gInput.lxAxis();
	auto q = Quaternion::Euler(-90-offsetX, 0, 0);
	q = Quaternion::Euler(0, 180+offsetY, 0) * q;
	player.transform.rotation = q;
	
	//printf("Pos %f, %f, %f\n", player.transform.position.x, 
	//						 player.transform.position.y,
	//						 player.transform.position.z);
}

Vector3 & Player::getPosition()
{
	return player.transform.position;
}

