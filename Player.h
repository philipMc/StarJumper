#ifndef _Player_H
#define _Player_H

#include "Ogre.h"
using namespace Ogre;

class Player
{
public:
	Player( SceneManager *scene ,Real groundPos);	
	void update( Real const & timeSinceLastFrame );
	void setJump(bool jump);
	void setPosition(Vector3 NodePos);
	bool getJump();
	void setMove(int);
	void turn(int);
	Vector3 getDirection();
	Vector3 getPosition();
	Entity * getEnt();
	bool onPlatform(Vector3 const & pos, Real height, Ogre::String  const & objectName);
	bool getGoingRight();
	void setGoingRight(bool);
	SceneNode* getParentNode();	
	void setJumpMod();
	float getJumpMod();
	void resetJumpMod();
	void setMoveMod();
	float getMoveMod();
	void resetMoveMod();
	float getTimeLeft();
	int getLives();
	void setLives(int);
	void setCurrentPickUp(String);
	String getCurrentPickUp();
	void Respawn();
	void setSpawns(Vector3[]);
	void selectSpawn();

protected :
	SceneNode *mParentNode;
	String mBodyNode;
	Vector3 mDirection;	// direcetion player is facing
	Entity * mBody; // a  reference to the body mesh
	SceneManager *mSceneMgr;// scean manager
	//static Real const sGRAVITY;// gravity
	Real mAccel;
	bool mJump;
	bool intersects;
	Vector3 mPosition;
	Vector3 oldPos;
	Vector3 newPos;
	Real mGroundPos;// player Y pos
    static Real const sGRAVITY;
	static Real const sMOVE_SPEED;
	RaySceneQuery *mRaySceneQuery;
	int mLives;
	//for turning the model
	bool mGoingRight;
	//modifier for jumping
	float mJumpMod;
	//modifier for jumping
	float mMoveMod;
	//time left for pick ups
	float timeLeft;
	String currentPickUp;
	Vector3 mSpawnPositions[4];
};

#endif