#include "player.h" 

Player::Player()
{
	playerMod.load("Assets/arm.obj"); 
	playerTex.load("Assets/arm.png"); 
	playerNrm.load("Assets/arm_NRM.png", false); 
	
	gunMod.load("Assets/gun.obj"); 
	gunTex.load("Assets/gun.png"); 
	gunNrm.load("Assets/gun_NRM.png", false); 
	
	Shader tmp("Shader/player_vs.glsl", "Shader/player_fs.glsl");
	
	//playerMat.ambient = Vector3(1.6f);
	playerMat.specular = Vector3(0.1f);
	playerMat.shininess = 12.3f; 
	
	player.reference(playerMod); 
	player.reference(playerTex); 
	player.reference(playerNrm); 
	//player.shaders.load("Shader/player_vs.glsl", "Shader/player_fs.glsl"); 
	player.shaders = tmp; 
	player.material = playerMat; 
	
	gun.reference(gunMod); 
	gun.reference(gunTex); 
	gun.reference(gunNrm); 
	//gun.shaders.load("Shader/player_vs.glsl", "Shader/player_fs.glsl");
	gun.shaders = tmp;
	gunMat.shininess = 32.0f; 
	gun.material = gunMat; 
	//player.transform.scale = 1.0f;
	player.transform.position.y = 1.0f;
	playerHeight = 1.0f; 
	player.transform.position.z = 10.75f;
	origin.position.z = -10.75f;
	//player.transform.rotation = Quaternion::Euler(0, 0, 0);  
	//player.transform.setParent(playerCam.transform);
	gun.transform.setParent(player.transform); 
	playerCam.transform.position.y = 2.0f;
	
	playerState = CharacterState::IDLE; 
}

Player::~Player()
{

}

void Player::update()
{	
	//need to add collision later
	switch(playerState)
	{
		default:
		case CharacterState::IDLE:
			IdleState();
			break;
		case CharacterState::WALK:
			WalkState();
			break;
		case CharacterState::RUN:
			RunState();
			break;
		case CharacterState::CROUCH:
			CrouchState();
			break;
		case CharacterState::SLIDING:
			SlidingState();			
			break;
	}
	//player.transform.rotation = (playerCam.transform.rotation); 
	//player.transform.setParent(playerCam.transform);
#if 0	
	float speed = 3.0f * gTime.deltaTime();  
	static Transform localPlayer; 
 
	Vector force = localPlayer.forward() *  gInput.lxAxis() * speed +
	               localPlayer.right()   *  gInput.lyAxis() * speed; 
	player.transform.position -= Vector3(force.x, 0, force.z);
#endif 
#if 0
	printf("pos %f, %f, %f\n", player.transform.position.x,
							   player.transform.position.y, 
							   player.transform.position.z);
#endif							   
	static float force = 1.0f; 
 		force = Mathf::Lerp(force, 1.0f, 5.0f * gTime.deltaTime());
 		if (gInput.buttonDown(BN_R1))
 			force = 0.5f;
 			
	static Vector3 offset;
 	if (gInput.button(BN_L1))
 	{

		offset = player.transform.right() * -0.25f * force + 
				 player.transform.forward() * 0.0f + 
				 player.transform.up() * 0.16f;  	
 	}else
 	{
 		Vector3 v(gInput.lxAxis(), 0, gInput.lyAxis()); 
 		static float bubble = 0; 
 		bubble += gTime.deltaTime() * v.magnitude() * speed * 185.0f;
		offset = player.transform.right() * -0.35f * force + 
				 player.transform.forward() * 0.1f + 
				 player.transform.up() * 0.25f * (0.07f * Mathf::Min(Mathf::Sin(bubble), 0)+1.0f); 
	}
	
	static Vector3 lerpOffset; 
	lerpOffset = Vector3::Lerp(lerpOffset, player.transform.position + offset, 60.0f * gTime.deltaTime()); 
	
	//Vector3 camPos = lerpOffset;  
	//camPos.y = -camPos.y; 
	
	//Vector3 offset(0.1f, 0.18f, -0.55f);
	playerCam.transform.position = lerpOffset;
	
	float rotSpeed = 100.0f * gTime.deltaTime(); 
	static Vector3 camRot;
	camRot.x -= gInput.ryAxis() * rotSpeed; 
	camRot.y += gInput.rxAxis() * rotSpeed; 
	camRot.x = Mathf::Clamp(camRot.x, -89, 89);

	localForward.rotation = Quaternion::AxisAngle(0.0f, 1.0f, 0.0f, -camRot.y);
	//localPlayer.rotation = Quaternion::AxisAngle(0.0f, 1.0f, 0.0f, -camRot.y);//Quaternion::Euler(0, -camRot.y, 0); 
	 player.transform.position = Vector3(origin.position.x, player.transform.position.y, origin.position.z); 
	//Quaternion q1 = Quaternion::Euler(camRot.x, 0, 0); 
	//Quaternion q = q1 * Quaternion::Euler(0, camRot.y, 0); 
	Quaternion q = Quaternion::Euler(-camRot.x, -camRot.y, 0); 
	
	//playerCam.transform.position += Vector3(gInput.lxAxis(), 0, gInput.lyAxis()); 
	player.transform.rotation = Quaternion::Slerp(player.transform.rotation, q, 9.0f * gTime.deltaTime()); 
 	//playerCam.transform.rotation = Quaternion::Euler(-camRot.x, -camRot.y, 0);
#if 0
	Quaternion lastValue = Quaternion::Conjugate(player.transform.rotation) * Quaternion::AxisAngle(0, 1, 0, 180.0f);
 	Quaternion lerpValue = Quaternion::Slerp(playerCam.transform.rotation,  
 						   					 lastValue, 15.0f * gTime.deltaTime());
 	playerCam.transform.rotation = lerpValue;  
#else
	playerCam.transform.rotateZYX(-camRot.x, camRot.y+180, 0); 	 
 	//playerCam.transform.rotation = Quaternion::Conjugate(player.transform.rotation) * Quaternion::Euler(0, 180, 0); 
 	//playerCam.transform.rotation = Quaternion::Euler(0, 180, 0);
#endif
	player.transform.position.y = Mathf::MoveTowards(player.transform.position.y, playerHeight, 5.0f * gTime.deltaTime());

	playerCam.applyView(); 
}

void Player::queue()
{
	gRenderer.queue(player, MatrixPath::LE_MAT_3D_TRS);
	gRenderer.queue(gun, MatrixPath::LE_MAT_3D_TRS); 
}

Transform & Player::getTransform()
{
	return player.transform; 
}
 	
Camera & Player::getCamera()
{
	return playerCam;
}

void Player::IdleState()
{
	playerHeight = 1.0f; 
	
	if (gInput.lxAxis() != 0 || gInput.lyAxis() != 0)
		playerState = CharacterState::WALK; 
		
	if (gInput.buttonDown(BN_CIRCLE))
		playerState = CharacterState::CROUCH;
}

void Player::WalkState()
{
	speed = 3.0f * gTime.deltaTime();  

	Vector force = localForward.forward() *  gInput.lxAxis() * speed +
	               localForward.right()   *  gInput.lyAxis() * speed; 
	//player.transform.position -= Vector3(force.x, 0, force.z);
	origin.position -= Vector3(force.x, 0, force.z);
	
	
	if (gInput.lxAxis() == 0 && gInput.lyAxis() == 0)
		playerState = CharacterState::IDLE; 
		
	if (gInput.buttonDown(BN_L3))
	{
		if (gInput.lyAxis() < -0.3f)
		{
			playerState = CharacterState::RUN;
			playerLookDir = player.transform.right(); 
		}
	}
	
	if (gInput.buttonDown(BN_CIRCLE))
		playerState = CharacterState::CROUCH;	
}

void Player::RunState()
{
	speed = 7.0f * gTime.deltaTime();  

	Vector force = localForward.forward() *  gInput.lxAxis() * speed +
	               localForward.right()   *  gInput.lyAxis() * speed; 
	origin.position -= Vector3(force.x, 0, force.z);
	
	float dforward = Vector3::Dot(playerLookDir, player.transform.right());
	
	if (dforward < 0.78f || gInput.button(BN_L1) ||
		gInput.lxAxis() == 0 && gInput.lyAxis() == 0)
			playerState = CharacterState::WALK;
		
	if (gInput.button(BN_CIRCLE))
	{
		playerState = CharacterState::SLIDING;
		slidingTimer = gTime.getTicks()+700;
	}
}

void Player::CrouchState()
{
	playerHeight = 0.5f; 
	
	speed = 1.0f * gTime.deltaTime();  

	Vector force = localForward.forward() *  gInput.lxAxis() * speed +
	               localForward.right()   *  gInput.lyAxis() * speed; 
	origin.position -= Vector3(force.x, 0, force.z);
	
	if (gInput.buttonDown(BN_CIRCLE))
		playerState = CharacterState::IDLE;
}

void Player::SlidingState()
{
	//run a timer and after that check for input 
	playerHeight = 0.25f;
	
	//float speed = 7.0f * gTime.deltaTime();  
	speed = 0; 
	
	Vector force = localForward.right() * -7.0f * gTime.deltaTime(); 
	origin.position -= Vector3(force.x, 0, force.z);
	
	if (slidingTimer > gTime.getTicks()) return; 
	
	if (gInput.button(BN_CIRCLE))
		playerState = CharacterState::CROUCH;
	else 
		playerState = CharacterState::IDLE;
}
