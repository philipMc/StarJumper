#include "Player.h"
#include "CollisionManager.h"
#include "DebugDrawer.h"


Real const Player::sGRAVITY = 9.81f;
Real const Player::sMOVE_SPEED = 2.5;

Player::Player( SceneManager *scene ,Real groundPos):

 mSceneMgr(scene),
 mGroundPos(groundPos),
 mBody(scene->getEntity("body")),
 mJump(false),
 intersects(false),
 mAccel(0.8f),
 mDirection(Vector3::ZERO),
 mParentNode(scene->getSceneNode("bodyParentNode")),
 oldPos (mParentNode->getPosition()),
 newPos (mParentNode->getPosition()),
 mPosition(mParentNode->getPosition()), 
 mBodyNode("playerBodyNode"),
 mGoingRight(true),
 mJumpMod(1.0f),
 mMoveMod(1.0f),
 timeLeft(0.0f),
 mLives(3),
 mRaySceneQuery ( scene->createRayQuery( Ray() ) )
   
{
	mSpawnPositions[0] = Vector3(0,5,0);
	mSpawnPositions[1] = Vector3(0,5,40);
	mSpawnPositions[2] = Vector3(0,15,80);
	mSpawnPositions[3] = Vector3(0,5,170);
	mSpawnPositions[4] = Vector3(0,5,210);
}

 void Player::setJump(bool jump)
{     
	if(jump == true)
	{
 		mDirection.y = mJumpMod * 10;		
		newPos = (mParentNode->getPosition());
	}
	mJump = jump;
}
bool Player::getJump() {
	return mJump;
}

void Player::update(Real const & timeSinceLastFrame)
{	
	newPos = (mParentNode->getPosition());
	intersects  = false;
	bool maxHeight = false;

	if (abs(newPos.y )- abs(oldPos.y) >= (mJumpMod * 25))
		mJump =false;		
	
	if(mParentNode->getPosition().y <= 0)
		Respawn();	 	

	if (timeLeft > 0)
		timeLeft -= timeSinceLastFrame;
	else if(timeLeft < 0)
	{
		timeLeft = 0.0f;
		if (currentPickUp == "jump")
		{
			resetJumpMod();
			currentPickUp = "";
		}
		if (currentPickUp == "move")
		{
			resetMoveMod();
			currentPickUp = "";
		}		
	}

	//ray casting 	
	Vector3 rayDir = Vector3(0,-1,0) ;
	int height = 0;

	Ray originRay( Vector3(mParentNode->getPosition().x, mParentNode->getPosition().y + height, mParentNode->getPosition().z ), rayDir );
	// Visualise the ray by drawing a line.	
	Ogre::Vector3 lineEnd( ( 2 * rayDir.x + mParentNode->getPosition().x ),  
							mParentNode->getPosition().y + height, 
							( 2 * rayDir.z + mParentNode->getPosition().z ) ); 
	DebugDrawer::getSingleton().drawLine( Vector3( mParentNode->getPosition().x, mParentNode->getPosition().y + height,mParentNode->getPosition().z ), lineEnd, Ogre::ColourValue::Red );
	DebugDrawer::getSingleton().build();
	mRaySceneQuery->setRay( originRay );
		
	RaySceneQueryResult & result = mRaySceneQuery->execute();
	RaySceneQueryResult::iterator iter = result.begin();
		
	for ( iter = result.begin(); iter != result.end()&& intersects == false; ++iter ) {
		Ogre::String n = iter->movable->getName();

		if (iter->movable && iter->movable->getName().compare("platform1") == 0||
			iter->movable && iter->movable->getName().compare("platform2") == 0
				  ||iter->movable && iter->movable->getName().compare("platform3") == 0
				  ||iter->movable && iter->movable->getName().compare("platform4") == 0) {
			if(iter->distance <= 0.0f && mJump== false){
				intersects = true;	
				mAccel  = 1.0;
				mDirection.y= 0;	
			}
		}
		else 
		{
			if(mJump == false)
			{
				intersects = false;
				mAccel = sGRAVITY;
				mDirection.y = mAccel * -0.9;
			}
			else
				mDirection.y = 10;			
		}
	}
	mParentNode->translate(mDirection * timeSinceLastFrame *(mMoveMod * sMOVE_SPEED), Node::TS_LOCAL );
	mPosition = mParentNode->getPosition();	 
}
void Player::setMove(int move)
{
	mDirection.z = move;
	//move is pos then going right
	if (move > 0)
	{
		if(mGoingRight == false)
		{
			turn(180);
			mGoingRight = true;
		}		
	}
	else if(move < 0)
	{
		if(mGoingRight == true)
		{
			mGoingRight = false;
			turn(-180);
		}		
	}	
}
void Player::Respawn()
{
	if (mLives > 0)
	{		
		selectSpawn();
		mJump = false;
		intersects = false;
		mDirection = Vector3::ZERO;
		mLives--;
	}	
}

void Player::selectSpawn()
{
	bool spawned = false;
	if(mPosition.z < mSpawnPositions[0].z) {
		mPosition = mSpawnPositions[0];
		spawned = true;
	}
	else
	{
		for (int i = 0; i < 5 && spawned == false; i++)
		{
			if(i + 1 < 5)
			{
				if (mPosition.z > mSpawnPositions[i].z && mPosition.z < mSpawnPositions[i+1].z)
				{
					mPosition = mSpawnPositions[i];
					mParentNode->setPosition(mPosition);
					spawned = true;
				}
			}
			else {
				mPosition = mSpawnPositions[i];
				mParentNode->setPosition(mPosition);
				spawned = true;
			}
		}
	}	
}

void Player::turn(int rotate) {
	mParentNode->getChild(mBodyNode)->yaw(Ogre::Degree(rotate));
}

////////////	GETTERS AND SETTERS	/////////////////////////////////////////////////////////////////
Vector3 Player::getDirection() {
	return mDirection;
}

void Player::setPosition(Vector3 nodePos) {
	mPosition = nodePos;
}

Entity* Player::getEnt() {
	return mBody;
}
Vector3 Player::getPosition() {
	return mPosition;
}

//bool getGoingRight();
bool Player::getGoingRight() {
	return mGoingRight;
}
//void setGoingRight(bool);
void Player::setGoingRight(bool goRight) {
	mGoingRight = goRight;
}
//SceneNode* getParentNode();
SceneNode * Player::getParentNode() {
	return mParentNode;
}
void Player::setJumpMod() {
	mJumpMod = 2.0f;
	timeLeft = 10.0f;
}
void Player::resetJumpMod() {
	mJumpMod = 1.0f;
}
float Player::getTimeLeft() {
	return timeLeft;
}
//void setMoveMod();
void Player::setMoveMod() {
	mMoveMod = 1.5f;
	timeLeft = 10.0f;
}
//void resetMoveMod();
void Player::resetMoveMod() {
	mMoveMod = 1.0f;
}
//int getLives();
int Player::getLives() {
	return mLives;
}
//void setLives(int);
void Player::setLives(int i) {
	mLives += i;
}
//void setCurrentPickUp(String);
void Player::setCurrentPickUp(String p) {
	currentPickUp = p;
}
//String getCurrentPickUp();
String Player::getCurrentPickUp() {
	return currentPickUp;
}
float Player::getJumpMod() {
	return mJumpMod;
}
float Player::getMoveMod() {
	return mMoveMod;
}
//void setSpawns(Vector3[]);
void Player::setSpawns(Vector3 spawns[5])
{
	for (int i = 0; i < 5; i++)
	{
		mSpawnPositions[i] = spawns[i];
	}
}

