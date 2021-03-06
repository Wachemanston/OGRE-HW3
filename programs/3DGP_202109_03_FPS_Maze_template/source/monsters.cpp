#include "monsters.h"
#include "read_data.h"
#include "BasicTools.h"
#include "envtools.h"

MONSTER::MONSTER(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
}

//
// Make the monster look at mTarget
//
void MONSTER::updateViewDirection()
{
	if (mTarget == 0) return;
	Vector3 pos = mSceneNode->getPosition();
	Vector3 target_pos = mTarget->getPosition();
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
	Real distance_threshold = 300;
	mv.normalise();
    double dt = evt.timeSinceLastFrame;
    if (d < distance_threshold) {
		mVelocity += dt * mv * 1500.0/(d+1);
	} else {
		mVelocity -= dt * mv * 200;
	}

	mTime += dt+dt*(5*mRandSpeed);
	Vector3 offset(0, 0, 0);
	offset.y = mAmplitude * (1 + sin(mTime));
	if (mTime > 3.14159*2) {
		mTime -= 3.14159*2;
	}

	mVelocity.normalise();
	mSceneNode->translate(mVelocity);
	Vector3 pos = mSceneNode->getPosition(), new_pos;
	clampToEnvironment(pos, 0.1, new_pos);
	mSceneNode->setPosition(new_pos + offset);
	mInitPosition = new_pos;
	updateViewDirection();
}