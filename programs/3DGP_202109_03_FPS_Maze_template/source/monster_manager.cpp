#include "monster_manager.h"
#include "read_data.h"
#include "BasicTools.h"

//Create Monsters here
MONSTER_MANAGER::MONSTER_MANAGER(SceneManager *a_SceneMgr): GAME_OBJ(a_SceneMgr)
{

	mMonstersTarget = 0;
	//mCurMonstersNum = mNumMonsters = 512;
    //
    //
    mCurMonstersNum = mNumMonsters = 10;
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
        //
        // mMonstersArr[i]->setPosition( ... )
        // mMonstersArr[i]->setInitPosition( ... )
        // mMonstersArr[i]->scale( sx, sy, sz )

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
    // For each monster, do
	Vector3 p1 = mMonstersTarget->getPosition();
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		Vector3 p0 = mMonstersArr[i]->getPosition();
        //
        // Add your own stuff
        //
    }
}

//
// The monsters do not overlap with each other
//
void MONSTER_MANAGER::resolveMonsterCollision()
{
    // for each pair of monsters, do
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		for (int j = i+1; j < mCurMonstersNum; ++j) 
		{
			Vector3 p0 = mMonstersArr[i]->getPosition();
			Vector3 p1 = mMonstersArr[j]->getPosition();
            // Add your own stuff
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
    //for (int i = 0; i < mCurMonstersNum; ++i) 
    for (int i = 0; i < 1; ++i) 
	{
		Vector3 q = mMonstersArr[i]->getInitPosition();
        float d = pos.distance(q);
        if (particleCount >= numParticles) break;
        if (d < 0) {
            /*
            particleNodes[particleCount]->setVisible(true);
            setOffParticleSystem(
               particleNodes[particleCount],
               "explosion",
               q);
            ++particleCount;
            */
        }
    }
    for (int i = particleCount; i < numParticles; ++i )
    {
            particleNodes[particleCount]->setVisible(false);

    }
}
