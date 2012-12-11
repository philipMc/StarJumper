#ifndef COLLISONMANAGER_H
#define COLLISONMANAGER_H
#include <OgreStringConverter.h>
#include <Ogre.h>

using namespace Ogre;

class CollisionManager{

public:
	static CollisionManager * instance(SceneManager * sceneMgr = 0);
	bool checkCollisionsWithPlatforms(Entity const * const entity);
	bool checkCollisionsWithPickUps(Entity * entity, Entity * other);
	Entity getEnt();
	
protected:
	CollisionManager( SceneManager * sceneMgr );

private:
	static CollisionManager * mInstance;

};


#endif