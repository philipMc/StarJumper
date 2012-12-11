#include "CollisionManager.h"
#include "Platforms.h"
using namespace Ogre;

CollisionManager * CollisionManager::mInstance = 0;

CollisionManager::CollisionManager( SceneManager * sceneMgr )
{
}


CollisionManager * CollisionManager::instance(SceneManager * sceneMgr) {
	if (mInstance == 0)  {  
	mInstance = new CollisionManager( sceneMgr );
	}
    return mInstance;
}
bool CollisionManager::checkCollisionsWithPlatforms(Entity const * const entity )
{

	///Platforms  * mPlatform = Platforms::instance();
	bool collided = false;
	AxisAlignedBox entityBox = entity->getBoundingBox();
	//Entity * entity1 = mPlatform->getPlatforms();

	//AxisAlignedBox entityBox1 = entity1->getBoundingBox();
	//collided = entityBox.intersects( entityBox1 );

	return collided;
}
//bool checkCollisionsWithPickUps(Entity * entity, Entity * other);
bool CollisionManager::checkCollisionsWithPickUps(Entity * player, Entity * pickUp)
{
	bool collided = false;	
	AxisAlignedBox playerBox = player->getWorldBoundingBox();	
	AxisAlignedBox pickUpBox = pickUp->getWorldBoundingBox();
	if(playerBox.intersects(pickUpBox))
	{
		collided = true;
	}
	return collided;
}