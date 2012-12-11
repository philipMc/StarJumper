#ifndef PICKUPMANAGER_H
#define PICKUPMANAGER_H

#include "Ogre.h"
#include "PickUp.h"

class PickUpManager {
public:
	PickUpManager(SceneManager *);
	PickUp * getPickUp(int);	

private:
	PickUp mPickUps[5];
};
#endif