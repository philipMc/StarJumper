#ifndef _Platforms_H
#define _Platforms_H

#include <OgreStringConverter.h>
#include <Ogre.h>
#include <vector>

using namespace Ogre;


class Platforms
{

private:
	std::vector<Entity *> mPlatforms;
	static Platforms * m_pInstance;
	Platforms( SceneManager * sceneMgr );

public:
	

	Entity * getPlatforms();

	~Platforms();
	
	static Platforms * instance(SceneManager * sceneMgr = 0);


	Ogre::Entity* platform1;
	Ogre::SceneNode* Plat1Node;

	//Platforms(SceneManager *scene, Vector3 platPos);
	//bool CheckForPlatform();
	//bool CheckForCollision(Entity const * const entity, Entity const * const entity1);
//protected: 
	//SceneManager *mSceneMgr;
	///SceneNode *PlatNode;
	//Vector3 platPos;
	//Entity *mPlatform;
};


#endif