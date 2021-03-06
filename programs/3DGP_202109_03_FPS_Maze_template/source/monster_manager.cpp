#include "monster_manager.h"
#include "read_data.h"
#include "BasicTools.h"
#include "envTools.h"

//Create Monsters here
MONSTER_MANAGER::MONSTER_MANAGER(SceneManager *a_SceneMgr): GAME_OBJ(a_SceneMgr)
{

	mMonstersTarget = 0;
	mCurMonstersNum = mNumMonsters = 3; // 512;

	int range = 200;
	int offset = 0;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		mLifeStateArr[i] = true;
		mMonstersArr[i] = new MONSTER(a_SceneMgr);
		//mMonstersArr[i]->createGameObj("m", "ogrehead.mesh");
		//mMonstersArr[i]->createGameObj("m", "cube.mesh");
		mMonstersArr[i]->createGameObj("m", DATA_READER::getMeshName());
        // Set the initial position 
        // and current position of each monster
        // Set the scale.
        // Use 
		Vector3 pos = Vector3(2000, 0, 2000) + Vector3(Math::Floor(rand() % range) + offset, 100, Math::Floor(rand() % range) + offset);
        mMonstersArr[i]->setInitPosition(pos);
		mMonstersArr[i]->setPosition(pos);
        // mMonstersArr[i]->setInitPosition( ... )
		int scale = DATA_READER::getMeshScale();
        mMonstersArr[i]->scale(scale, scale, scale);
		// 
    }

}
void MONSTER_MANAGER::setMaxMonstersNum(int a_Num)
{
	if (a_Num >= mNumMonsters) 
	{
		a_Num = mNumMonsters;
	}


	mCurMonstersNum = a_Num;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		if (i<mCurMonstersNum) {
			mMonstersArr[i]->setVisible(true);
			mMonstersArr[i]->makeAlive(true);
		} else {
			mMonstersArr[i]->setVisible(false);
			mMonstersArr[i]->makeAlive(false);
		}
	}
}

void MONSTER_MANAGER::setTargetForMonsters(GAME_OBJ *a_Target)
{

	mMonstersTarget = a_Target;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		Vector3 p = mMonstersArr[i]->getInitPosition();
		mMonstersArr[i]->setTarget(a_Target, 0);
	}
}

// The monsters should avoid collision with mMonstersTarget 
void MONSTER_MANAGER::resolveMonsterTargetCollision()
{
	if (mMonstersTarget == 0) return;
	int collision_range = 150;
	int back_unit = 5;
    // For each monster, do
	Vector3 p1 = mMonstersTarget->getPosition();
	p1.y = 0;
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		Vector3 p0 = mMonstersArr[i]->getPosition();
		p0.y = 0;
		// A.15, monster & player collision
		if (p0.distance(p1) <= collision_range) {
			Vector3 dir = p0 - p1;
			dir.normalise();
			mMonstersArr[i]->translate(dir);
		}
    }
}

//
// The monsters do not overlap with each other
//
void MONSTER_MANAGER::resolveMonsterCollision()
{
	int collision_range = 50;
	int back_unit = 5;
    // for each pair of monsters, do
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		for (int j = i+1; j < mCurMonstersNum; ++j) 
		{
			Vector3 p0 = mMonstersArr[i]->getPosition(), np0;
			p0.y = 0;
			Vector3 p1 = mMonstersArr[j]->getPosition(), np1;
			p1.y = 0;
			// A.12, monster collision
			if (p0.distance(p1) <= collision_range) {
				Vector3 dir = p0 - p1;
				dir.normalise();
				mMonstersArr[i]->translate(dir);
				mMonstersArr[j]->translate(-dir);
			}
        }
	}
}


void MONSTER_MANAGER::update(const Ogre::FrameEvent& evt)
{
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		Vector3 p = mMonstersArr[i]->getInitPosition();

		mMonstersArr[i]->update(evt);
	}
	resolveMonsterTargetCollision();
	resolveMonsterCollision();
	/*
	resolveMonsterTargetCollision();
	resolveMonsterCollision();
	resolveMonsterTargetCollision();
	resolveMonsterCollision();
	resolveMonsterTargetCollision();
	resolveMonsterCollision();
	resolveMonsterTargetCollision();
	*/
}



void MONSTER_MANAGER::setParticleSystem(
    const Vector3 &pos,
    int numParticles,
    SceneNode **particleNodes
    )
{
    int particleCount = 0;
	Real distance_threshold = 6400;
    for (int i = 0; i < mCurMonstersNum; ++i)
	{
		Vector3 q = mMonstersArr[i]->getPosition();
        float d = pos.distance(q);
        if (particleCount >= numParticles) break;
        if (d < distance_threshold) {
            particleNodes[particleCount]->setVisible(true);
			particleNodes[particleCount]->setPosition(q);
            setOffParticleSystem(
               particleNodes[particleCount],
               "explosion",
               q);
            ++particleCount;
        }
    }
    for (int i = particleCount; i < numParticles; ++i )
    {
        particleNodes[particleCount]->setVisible(false);
    }
}
