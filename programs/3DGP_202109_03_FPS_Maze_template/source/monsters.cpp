#include "monsters.h"
#include "read_data.h"
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
    // A.17
	double deg = DATA_READER::getDegreeCorrection();
	mSceneNode->lookAt(target_pos, Node::TransformSpace::TS_WORLD);
	mSceneNode->yaw(Radian(deg));
}

//
// Update the position of the monster.
//
void MONSTER::update(const Ogre::FrameEvent& evt)
{
	Vector3 mv = mInitPosition - mTarget->getPosition();
    // A.13, A.14 update monster's velocity
	mv.y = 0.0;
    Real d = mv.length();
	Real distance_threshold = 10000;
	mv.normalise();
    double dt = evt.timeSinceLastFrame;
    if (d < distance_threshold) {
			mVelocity += dt * mv * 1500.0/(d+1);
		} else if (d > 300) {
			mVelocity -= dt * mv * 10;
	}

	mTime += dt+dt*(5*mRandSpeed);
	Vector3 offset(0, 0, 0);
	offset.y = sin(mTime);
	if (mTime > 3.14159*2) {
		mTime -= 3.14159*2;
	}

	mVelocity.normalise();
    mSceneNode->setPosition(mSceneNode->getPosition() + mVelocity + offset);
	updateViewDirection();
}