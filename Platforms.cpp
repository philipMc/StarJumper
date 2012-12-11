#include "Platforms.h"
#include <Ogre.h>
#include <OgreSceneQuery.h>
using namespace Ogre;


Platforms * Platforms::m_pInstance = 0;


Platforms::Platforms( SceneManager * sceneMgr ) {
     platform1 = sceneMgr->createEntity("platform1", "Cube.mesh");
	
	 Plat1Node = sceneMgr->getRootSceneNode()->createChildSceneNode("Plat1Node");
    Plat1Node->attachObject(platform1);
	Plat1Node->scale(0.2,0.1,0.2);
	Plat1Node->setPosition(0,0,0);



}
Platforms * Platforms::instance(SceneManager * sceneMgr) {
	if (m_pInstance == 0)  {  
		m_pInstance = new Platforms( sceneMgr );
	}
    return m_pInstance;
}


Entity* Platforms::getPlatforms(){
	return platform1;
}


/*Platforms::Platforms(SceneManager *scene, Vector3 platPos):

mSceneMgr(scene),
platPos(platPos),
mPlatform(scene->getEntity("platform1"))
{
}

/*bool Platforms::CheckForPlatform(Vector3 const & pos, Real height, Ogre::String const & objectName, Vector3 const & rayDir)
{
	bool intersects = false;
	// Setup the scene query
    Ray originRay( Vector3( pos.x, pos.y + height, pos.z ), rayDir );
	mRaySceneQuery->setRay( originRay );
	// Perform the scene query
    RaySceneQueryResult & result = mRaySceneQuery->execute();
	RaySceneQueryResult::iterator iter = result.begin();
	// Get results...
    for ( iter = result.begin(); iter != result.end(); ++iter ) {
		//Ogre::String n = iter->movable->getName();
		if (iter->movable && iter->movable->getName().compare( objectName ) == 0 && 
			iter->distance < 1.0f ) {
			intersects = true;
		}
	}
	return intersects;

}

bool Platforms::CheckForCollision(Entity const * const entity,Entity const * const entity1 )
{
	bool collided = false;
	AxisAlignedBox entityBox = entity->getBoundingBox();
	AxisAlignedBox entityBox1 = mPlatform->getBoundingBox();
	collided = entityBox.intersects( entityBox1 );

	return collided;
}*/
