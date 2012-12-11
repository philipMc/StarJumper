#include "PickUp.h"

PickUp::PickUp(Ogre::SceneNode * n,Ogre::Entity * e, Ogre::Vector3 pos, String t)
{
	node = n;
	ent = e;
	position = pos;
	type = t;		
}
void PickUp::reset() 
{
	position = Vector3(position.x, 80, position.z);
	node->setPosition(position);
}

//String getType();
String PickUp::getType() {
	return type;
}

Entity * PickUp::getEntity() {
	return ent;
}

//Vector3 getPosition();
Vector3 PickUp::getPosition() {
	return position;
}