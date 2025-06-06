#include "level.h" 


Levelt::Levelt()
{
	rockMod.load("Assets/level/rock.obj"); 
	treeMod.load("Assets/level/tree.obj"); 
	weetMod.load("Assets/level/weet.obj"); 
	cabinMod.load("Assets/level/cabin.obj"); 
	decalMod.load("Assets/level/decal.obj"); 
	tree2Mod.load("Assets/level/tree2.obj"); 
	floor1Mod.load("Assets/level/floor1.obj"); 
	floor2Mod.load("Assets/level/floor2.obj"); 
	flowerMod.load("Assets/level/flower.obj"); 
	grassbMod.load("Assets/level/grassb.obj"); 
	cabinRampMod.load("Assets/level/cabinRamp.obj"); 
	cabinRoofMod.load("Assets/level/cabinRoof.obj"); 
	potTrunksMod.load("Assets/level/pottrunks.obj"); 
	floorCabinMod.load("Assets/level/floorCabin.obj"); 
	grassBlade1Mod.load("Assets/level/grassblade1.obj"); 
	grassBlade2Mod.load("Assets/level/grassblade2.obj"); 
	
	rockTex.load("Assets/level/rock.png"); 
	treeTex.load("Assets/level/tree.png"); 
	weetTex.load("Assets/level/weet.png"); 
	cabinTex.load("Assets/level/cabin.png"); 
	decalTex.load("Assets/level/decal.png"); 
	tree2Tex.load("Assets/level/tree2.png"); 
	floor1Tex.load("Assets/level/floor1.png"); 
	floor2Tex.load("Assets/level/floor2.png"); 
	flowerTex.load("Assets/level/flower.png"); 
	grassbTex.load("Assets/level/grassblade2.png"); 
	cabinRampTex.load("Assets/proto3.png"); 
	cabinRoofTex.load("Assets/level/cabinRoof.png"); 
	potTrunksTex.load("Assets/level/pottrunks.png"); 
	floorCabinTex.load("Assets/level/floorCabin.png"); 
	grassBlade1Tex.load("Assets/level/grassblade1.png"); 
	grassBlade2Tex.load("Assets/level/grassblade2.png"); 
	
	rockNrm.load("Assets/level/rock_NRM.png"); 
	treeNrm.load("Assets/level/tree_NRM.png"); 
	weetNrm.load("Assets/level/weet_NRM.png"); 
	cabinNrm.load("Assets/level/cabin_NRM.png"); 
	decalNrm.load("Assets/level/decal_NRM.png"); 
	tree2Nrm.load("Assets/level/tree2_NRM.png"); 
	floor1Nrm.load("Assets/level/floor1_NRM.png"); 
	floor2Nrm.load("Assets/level/floor2_NRM.png"); 
	flowerNrm.load("Assets/level/flower_NRM.png"); 
	grassbNrm.load("Assets/level/grassblade2_NRM.png"); 
	//cabinRampNrm.load("Assets/proto3_NRM.png"); 
	cabinRoofNrm.load("Assets/level/cabinRoof_NRM.png"); 
	potTrunksNrm.load("Assets/level/pottrunks_NRM.png"); 
	floorCabinNrm.load("Assets/level/floorCabin_NRM.png"); 
	grassBlade1Nrm.load("Assets/level/grassblade1_NRM.png"); 
	grassBlade2Nrm.load("Assets/level/grassblade2_NRM.png"); 
	
	Shader tmpShader("Shader/shader_vs.glsl", "Shader/shader_fs.glsl");
	Shader gblade("Shader/gblade_vs.glsl", "Shader/gblade_fs.glsl");
	levelMat.ambient = Vector(0.8f);
	levelMat.specular = Vector(0.1f);   
	levelMat.shininess = 12.0f; 
	
	rock.reference(rockMod); 
	rock.reference(rockTex);
	rock.reference(rockNrm); 
	rock.shaders = tmpShader;
	rock.material = levelMat;
	 
	tree.reference(treeMod); 
	tree.reference(treeTex);
	tree.reference(treeNrm);
	tree.shaders = tmpShader;
	tree.material = levelMat;
	
	weet.reference(weetMod);
	weet.reference(weetTex);
	weet.reference(weetNrm);
	weet.shaders = tmpShader; 
	weet.material = levelMat;
	
	cabin.reference(cabinMod);
	cabin.reference(cabinTex);
	cabin.reference(cabinNrm);
	cabin.shaders = tmpShader;
	cabin.material = levelMat;
	
	decal.reference(decalMod);
	decal.reference(decalTex);
	decal.reference(decalNrm);
	decal.shaders = tmpShader;
	decal.material = levelMat;
	
	tree2.reference(tree2Mod);
	tree2.reference(tree2Tex);
	tree2.reference(tree2Nrm);
	//tree2.shaders = gblade;
	tree2.shaders = tmpShader;
	tree2.material = levelMat;
	
	floor1.reference(floor1Mod);
	floor1.reference(floor1Tex);
	floor1.reference(floor1Nrm);
	floor1.shaders = tmpShader;
	floor1.material = levelMat;
	
	floor2.reference(floor2Mod);
	floor2.reference(floor2Tex);
	floor2.reference(floor2Nrm);
	floor2.shaders = tmpShader;
	floor2.material = levelMat;
	
	flower.reference(flowerMod);
	flower.reference(flowerTex);
	flower.reference(flowerNrm);
	flower.shaders = tmpShader;
	flower.material = levelMat;
	
	float random = 17.0f;
	float distance = 7.5f;
	for(int i = 0; i < GRASS_AMOUNT; ++i)
	{
		grassb[i].reference(grassbMod);
		grassb[i].reference(grassbTex);
		grassb[i].reference(grassbNrm);
		grassb[i].shaders = gblade;
		grassb[i].material = levelMat;
		float r1 = Mathf::RandomRangef(-random, random);
		float r2 = Mathf::RandomRangef(-random, random);
		//grassb[i].transform.position = Vector3((rand()%random*2)-random, -0.0f, (rand()%random*2)-random);
		if ((r1 > -distance && r1 < distance) &&
			(r2 > -distance && r2 < distance))
		{
			float l = (r1 >= 0.0f) ? 1.0f : -1.0f; 
			r1 = Mathf::RandomRangef(distance * l, random * l);
			l = (r2 >= 0.0f) ? 1.0f : -1.0f; 
			r2 = Mathf::RandomRangef(distance * l, random * l);
		}
		
		grassb[i].transform.position = Vector3(r1, -0.0f, r2);
		grassb[i].transform.rotation = Quaternion::AxisAngle(0, 1, 0, (float)i*5.0f);
		grassb[i].transform.scale = 0.5f; 
	}
	cabinRamp.reference(cabinRampMod);
	cabinRamp.reference(cabinRampTex);
	//cabinRamp.reference(cabinRampNrm);
	cabinRamp.shaders = tmpShader;
	cabinRamp.material = levelMat;
	
	cabinRoof.reference(cabinRoofMod);
	cabinRoof.reference(cabinRoofTex);
	cabinRoof.reference(cabinRoofNrm);
	cabinRoof.shaders = tmpShader;
	cabinRoof.material = levelMat;
	
	potTrunks.reference(potTrunksMod);
	potTrunks.reference(potTrunksTex);
	potTrunks.reference(potTrunksNrm);
	potTrunks.shaders = tmpShader;
	potTrunks.material = levelMat;
	
	floorCabin.reference(floorCabinMod);
	floorCabin.reference(floorCabinTex);
	floorCabin.reference(floorCabinNrm);
	floorCabin.shaders = tmpShader;
	floorCabin.material = levelMat;
	
	grassBlade1.reference(grassBlade1Mod);
	grassBlade1.reference(grassBlade1Tex);
	grassBlade1.reference(grassBlade1Nrm);
	grassBlade1.shaders = gblade;
	grassBlade1.material = levelMat;
	
	grassBlade2.reference(grassBlade2Mod);
	grassBlade2.reference(grassBlade2Tex);
	grassBlade2.reference(grassBlade2Nrm);
	grassBlade2.shaders = gblade;
	grassBlade2.material = levelMat;
}

Levelt::~Levelt()
{

}

void Levelt::levelQueue()
{
	static float r = 0; 
	r += 0.1f;
	grassb[0].shaders.use();
	grassb[0].shaders.setFloat("gTime", r); 
	for(int i = 0; i < GRASS_AMOUNT; ++i)
		gRenderer.queue(grassb[i], MatrixPath::LE_MAT_3D);
		
	gRenderer.queue(rock, MatrixPath::LE_MAT_3D); 
	gRenderer.queue(tree, MatrixPath::LE_MAT_3D); 
	gRenderer.queue(weet, MatrixPath::LE_MAT_3D);
	gRenderer.queue(cabin, MatrixPath::LE_MAT_3D);
	gRenderer.queue(decal, MatrixPath::LE_MAT_3D);
	gRenderer.queue(tree2, MatrixPath::LE_MAT_3D);
	gRenderer.queue(floor1, MatrixPath::LE_MAT_3D);
	gRenderer.queue(floor2, MatrixPath::LE_MAT_3D);
	gRenderer.queue(flower, MatrixPath::LE_MAT_3D);
		
	gRenderer.queue(cabinRamp, MatrixPath::LE_MAT_3D);
	gRenderer.queue(cabinRoof, MatrixPath::LE_MAT_3D);
	gRenderer.queue(potTrunks, MatrixPath::LE_MAT_3D);
	gRenderer.queue(floorCabin, MatrixPath::LE_MAT_3D);
	gRenderer.queue(grassBlade1, MatrixPath::LE_MAT_3D);
	gRenderer.queue(grassBlade2, MatrixPath::LE_MAT_3D);
}
