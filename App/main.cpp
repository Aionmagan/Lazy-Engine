#include <cstdio> 
#include <LazyEngine.h> 
#include <cmath>

#include "level.h" 
#include "player.h"
#include "enemy.h"
#include "gunFlash.h" 

#include "testParticle.h"
#include "leafEffect.h"  
#include "quadDepth.h"

int main(int argc, char*argv[])
{
	//gRenderer.setBGColor(219, 219, 231); 
	//gRenderer.setBGColor(0.65f*255, 0.65f*255, 0.70f*255);
	gRenderer.setBGColor(0, 0, 0);
	
	
#if 1	
	Light lit; 
	lit.setType(LightType::DIRECTIONAL);
	//lit.setColor(1.9f, 1.9f, 1.9f);
	lit.transform.position = Vector3(20.5f, -10.0f, 3.8f);
	lit.transform.lookAt(Vector(0, 0, 0));
	//lit.setColor(255, 0, 0);
	lit.setEnable(true); 
	
	Skybox sb("Assets/Skybox.png");
	//sb.setAmbient(1.78f, 1.78f, 1.78f);
#endif

	//TestEffect te2(1); 
	//TestEffect te(0);
	//LeafEffect le; 
	QDepth qd; 
	
	Levelt testLevel; 
	Player playerObj;
	Enemy enemyObj; 
	GunFlash gunFlash; 
	gunFlash.setTransform(playerObj.getTransform()); 
	
	//le.setCamera(playerObj.getCamera());
	
	Camera cam; 
	float r; 
	Vector3 camPos; 
	while(!gInput.eventQuit())
	{
		gTime.update(); 
		gInput.update();
		
		playerObj.update();
		gunFlash.update();
		
		r += 0.1f;
		
Quaternion q = Quaternion::Euler(0, r*5, 0); 
lit.transform.position = q * Vector::Forward() * 14.5f + Vector::Up() * -10.0f; //* (Mathf::Sin(r)*1.0) + -10.0f; 
//Vector pos(playerObj.getTransform().position.x, 0, playerObj.getTransform().position.z);
//lit.transform.position = Vector3(14.5f, (Mathf::Sin(r/4)*1.0) + -10.0f, 3.8f);// - pos;
lit.transform.lookAt(Vector(0, 0, 0));
qd.update();
		testLevel.levelQueue();
		enemyObj.queue(); 
		
		//le.queueEffect();
		//te.queueEffect();
		//te2.queueEffect();
		
		//qd.queue();
		
		//gRenderer.queue(CommandPath::LE_CLEARDEPTH); 
		playerObj.queue(); 
		gunFlash.queue();
		
		gRenderer.drawQueue();
		gRenderer.removeQueue();//this is very inefficient but good enough for testing
	}
	
	return 0; 
}
