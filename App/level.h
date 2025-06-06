#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <LazyEngine.h>
#define GRASS_AMOUNT 200

class Levelt
{
public: 
	Levelt(); 
   ~Levelt(); 
   
  	void levelQueue();
  	
private:
	//int grassAmount = 200;	
	
	Model rockMod; 
	Model treeMod; 
	Model weetMod; 
	Model cabinMod; 
	Model decalMod; 
	Model tree2Mod; 
	Model floor1Mod; 
	Model floor2Mod; 
	Model flowerMod; 
	Model grassbMod; 
	Model cabinRampMod; 
	Model cabinRoofMod; 
	Model potTrunksMod; 
	Model floorCabinMod; 
	Model grassBlade1Mod; 
	Model grassBlade2Mod; 
	
	Texture rockTex; 
	Texture treeTex; 
	Texture weetTex; 
	Texture cabinTex; 
	Texture decalTex; 
	Texture tree2Tex; 
	Texture floor1Tex; 
	Texture floor2Tex; 
	Texture flowerTex; 
	Texture grassbTex; 
	Texture cabinRampTex; 
	Texture cabinRoofTex; 
	Texture potTrunksTex; 
	Texture floorCabinTex; 
	Texture grassBlade1Tex; 
	Texture grassBlade2Tex;
	
	Texture rockNrm; 
	Texture treeNrm; 
	Texture weetNrm; 
	Texture cabinNrm; 
	Texture decalNrm; 
	Texture tree2Nrm; 
	Texture floor1Nrm; 
	Texture floor2Nrm; 
	Texture flowerNrm; 
	Texture grassbNrm; 
	Texture cabinRampNrm; 
	Texture cabinRoofNrm; 
	Texture potTrunksNrm; 
	Texture floorCabinNrm; 
	Texture grassBlade1Nrm; 
	Texture grassBlade2Nrm;	
	
	Material levelMat; 
	
	GameObject rock; 
	GameObject tree; 
	GameObject weet;
	GameObject cabin;
	GameObject decal;
	GameObject tree2;
	GameObject floor1;
	GameObject floor2;
	GameObject flower;
	GameObject grassb[GRASS_AMOUNT];
	GameObject cabinRamp;
	GameObject cabinRoof;
	GameObject potTrunks;
	GameObject floorCabin;
	GameObject grassBlade1;
	GameObject grassBlade2;
}; 

#endif/*__LEVEL_H__*/
