#ifndef PICKUP_H
#define PICKUP_H

#include "Ogre.h"
using namespace Ogre;

class PickUp {
public:
	PickUp(SceneNode * n = 0,Entity * e = 0, Vector3 p = Vector3(0,0,0), String t = "");
	void reset();
	String getType();
	Entity * getEntity();
	Vector3 getPosition();

private:
	SceneNode * node;
	Vector3 position;
	String type;
	Entity * ent;
};
#endif