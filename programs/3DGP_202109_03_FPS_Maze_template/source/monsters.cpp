#include "monsters.h"
#include "BasicTools.h"

MONSTER::MONSTER(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
}

//
// Make the monster look at mTarget
//
void MONSTER::updateViewDirection()
{
	if (mTarget == 0) return;
	Vector3 pos = mTarget->getPosition();
	Vector3 target_pos = mSceneNode->getPosition();
    //
    // Add your own stuff
    // 
}

//
// Update the position of the monster.
//
void MONSTER::update(const Ogre::FrameEvent& evt)
{
	Vector3 mv = mInitPosition - mTarget->getPosition();
    double dt = evt.timeSinceLastFrame;

    Vector3 new_pos;

    // Add your own stuff
    // mSceneNode->setPosition(new_pos);
    //
updateViewDirection();
}