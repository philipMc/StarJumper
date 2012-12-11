#include "PickUpManager.h"

//PickUpManager(SceneManager *);
PickUpManager::PickUpManager(SceneManager * scene) 
{
	for (int i = 0; i < 5; i++)
	{
		SceneNode * n = scene->getRootSceneNode()->createChildSceneNode("pickup" + i);
		String type;
		Vector3 pos;
		Entity * e = scene->createEntity("pickup" + i, "cube.mesh");
		if (i == 0) {
			type = "jump";
			pos = Vector3(0, 8, 35);
			e->setMaterialName("Examples/jump");
		}
		else if (i == 1) {
			type = "move";
			pos = Vector3(0, 55, 70);
			e->setMaterialName("Examples/sprint");
		}
		else if (i == 2){
			type = "health";
			pos = Vector3(0, 8, 120);
			e->setMaterialName("Examples/chicken");
		}
		else if (i == 3) {
			type = "constant";
			pos = Vector3(0, 15, 250);
			e->setMaterialName("Examples/RustySteel");
		}
		else {
			type = "reverb";
			pos = Vector3(0, 8, 300);
			e->setMaterialName("Examples/Chrome");
		}
		n->attachObject( e );
		if (i <= 3)
		{
			float cubeModelLength = 100;
			float cubeLength = 4;	
			double cubeScale = cubeLength/cubeModelLength;
			n->scale(cubeScale, cubeScale, cubeScale);
		}
		else
			n->scale(0.3, 0.3, 0.3);		
		
		n->setPosition(pos);		
		//init pick up
		mPickUps[i] = PickUp(n, e, pos, type);
	}
}

//PickUp * getPickUp(int);
PickUp * PickUpManager::getPickUp(int p)
{
	return &mPickUps[p];
}