/*
 * BehaviorTreeTest.cpp
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/conf/ConfigManager.h"
#include "server/zone/managers/creature/AiMap.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/ai/bt/BehaviorTreeSlot.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

#include "BehaviorMocks.h"

#define TESTBEHAVIOR(name, argString, expectation) { \
	leaf::name b(#name, 0, argString); \
	b.parseArgs(argString); \
	EXPECT_EQ(b.execute(agent), expectation); }

using namespace server::zone::objects::creature::ai::bt;

using ::testing::_;
using ::testing::Return;
using ::testing::Eq;
using ::testing::AtMost;
using ::testing::AtLeast;
using ::testing::FloatEq;
using ::testing::TypedEq;
using ::testing::Mock;
using ::testing::NiceMock;
using ::testing::Invoke;

class BehaviorTreeTest : public ::testing::Test {
protected:
	// These three things are the heart of all tests, so ensure they all
	// get set up in this object
	Reference<NiceMock<MockAiAgent>* > agent;
	Reference<AiMap*> aiMap;

	// some more mocks that get used most tests
	Reference<NiceMock<MockZone>* > mockZone = new NiceMock<MockZone>();
	Reference<NiceMock<MockAiAgent>* > followMock = new NiceMock<MockAiAgent>();
	Reference<NiceMock<MockWeaponObject>* > mockWeao = new NiceMock<MockWeaponObject>();
	Reference<NiceMock<MockWeaponObject>* > mockDefaultWeao = new NiceMock<MockWeaponObject>();

public:
	BehaviorTreeTest()
		: agent(new NiceMock<MockAiAgent>()), aiMap(AiMap::instance()) {}

	void SetUp() {
		ASSERT_TRUE( agent != NULL ) << "AiAgent failed to initialize";
		ASSERT_TRUE( aiMap != NULL ) << "AiMap failed to initialize";

		agent->setPvpStatusBit(CreatureFlag::ATTACKABLE);
		followMock->setPvpStatusBit(CreatureFlag::ATTACKABLE);
		agent->setFollowObject(followMock);

		// set and forget the functions that get called a lot
		ON_CALL(*agent, isDead()).WillByDefault(Return(false));
		ON_CALL(*agent, isIncapacitated()).WillByDefault(Return(false));
		ON_CALL(*agent, getZone()).WillByDefault(Return(mockZone));
		ON_CALL(*agent, getTemplateRadius()).WillByDefault(Return(0.f));
		ON_CALL(*agent, getWeapon()).WillByDefault(Return(mockWeao));
		ON_CALL(*agent, getNumberOfPlayersInRange()).WillByDefault(Return(1));
		ON_CALL(*followMock, asAiAgent()).WillByDefault(Return(followMock));
		ON_CALL(*followMock, asCreatureObject()).WillByDefault(Return(followMock));
		ON_CALL(*followMock, asTangibleObject()).WillByDefault(Return(followMock));
		ON_CALL(*followMock, getTemplateRadius()).WillByDefault(Return(0.f));
		ON_CALL(*mockWeao, getMaxRange()).WillByDefault(Return(0.f));
	}

	void TearDown() {
		// force the order of clearing, or else gmock introduces a deadlock
		Mock::VerifyAndClear(agent);
		Mock::VerifyAndClear(mockWeao);
		Mock::VerifyAndClear(mockDefaultWeao);
	}

	~BehaviorTreeTest() {}
};

TEST_F(BehaviorTreeTest, LoadTemplatesTest) {
		ConfigManager::instance()->loadConfigData();
		TemplateManager::instance();
		ASSERT_EQ(TemplateManager::ERROR_CODE, 0);

		aiMap->loadTemplates();
		ASSERT_GT( aiMap->getTemplateSize(), 0 ) << "Did not load any AI templates";
}

TEST_F(BehaviorTreeTest, ParentChildDuplicateTest) {
	HashTableIterator<String, Reference<Behavior*> > s_it(&(aiMap->aiMap));

	s_it.resetIterator();
	while (s_it.hasNext()) {
		String k = "";
		Reference<Behavior*> b = NULL;
		s_it.getNextKeyAndValue(k, b);
		ASSERT_TRUE( b != NULL ) << k.toCharArray() << " has a NULL behavior!";

		Vector<const Behavior*> childList = b->getRecursiveChildList();

		for (int idx = 0; idx < childList.size(); ++idx) {
			const Behavior* localChild = childList.get(idx);
			ASSERT_TRUE(localChild != NULL);

			Behavior* localParent = localChild->getParent();
			while (localParent != NULL) {
				EXPECT_TRUE(!localChild->hasChild(localParent));
				localParent = localParent->getParent();
			}
		}
	}
}

TEST_F(BehaviorTreeTest, LoadTemplateTest) {
	Locker locker(agent);

	// set the base behavior
	Behavior* root = aiMap->getTemplate("rootDefault");
	ASSERT_TRUE( root != NULL ) << "Failed to load rootDefault";
	agent->setTree(root, BehaviorTreeSlot::NONE);

	// first test the direct lookup functionality
	Behavior* wdRoot = aiMap->getTemplate("wanderDefault");
	ASSERT_TRUE( wdRoot != NULL ) << "Failed to load wanderDefault";
	agent->setTree(wdRoot, BehaviorTreeSlot::IDLE);
	Behavior* sucRoot = aiMap->getTemplate("succeedTest");
	ASSERT_TRUE( sucRoot != NULL ) << "Failed to load successTest";
	agent->setTree(sucRoot, BehaviorTreeSlot::MOVE);
	// now traverse the tree to make sure that we have idlewander set and accessible
	// possibly just run AI and test for a condition
	EXPECT_CALL(*agent, setWait(TypedEq<int>(10000))).Times(1);
	agent->doMovement();

	// drop each of the previous trees one at a time and ensure they are unset
	agent->removeTree(BehaviorTreeSlot::IDLE);
	agent->doMovement();
}

TEST_F(BehaviorTreeTest, LoadBitmaskTest) {
	Locker locker(agent);

	for (int mask = CreatureFlag::NONE; mask < CreatureFlag::LASTAIMASK; mask == 0 ? ++mask : mask = mask << 1) {
		agent->setCreatureBitmask(mask);
		agent->setAITemplate();

		for (auto treeID : BehaviorTreeSlot()) {
			const Behavior* testB = agent->getBehaviorTree(treeID);
			EXPECT_TRUE(testB != NULL);
		}
	}
}

TEST_F(BehaviorTreeTest, LoadBitmaskExecutionTest) {
	Locker locker(agent);

	// With the test flag set, we should succeed at idling, and therefore never proceed to generating patrols
	agent->setCreatureBitmask(CreatureFlag::TEST);
	agent->setAITemplate();

	EXPECT_CALL(*agent, generatePatrol(_, _)).Times(0);

	agent->doMovement();
}

TEST_F(BehaviorTreeTest, CombatTest) {
	Locker locker(agent);

	agent->setCreatureBitmask(CreatureFlag::NONE);
	agent->setAITemplate();

	// setup the mock threatmap
	MockThreatMap* mockThreat = new MockThreatMap(followMock.get());
	ON_CALL(*agent, getThreatMap()).WillByDefault(Return(mockThreat));
	ON_CALL(*followMock, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*followMock, isAttackableBy(TypedEq<CreatureObject*>(agent.get())))
		.WillByDefault(Return(true));

	ON_CALL(*mockThreat, getHighestThreatCreature()).WillByDefault(Return(followMock));
	ON_CALL(*followMock, isInRange(TypedEq<SceneObject*>(agent.get()), _))
		.WillByDefault(Return(true));
	ON_CALL(*followMock, hasState(CreatureState::PEACE)).WillByDefault(Return(false));
	ON_CALL(*agent, getDistanceTo(TypedEq<SceneObject*>(followMock)))
		.WillByDefault(Return(5.f));

	// setup ready weapon calls
	ON_CALL(*agent, getReadyWeapon()).WillByDefault(Return(mockWeao));
	ON_CALL(*mockWeao, getMaxRange()).WillByDefault(Return(10.f));
	ON_CALL(*mockWeao, getIdealRange()).WillByDefault(Return(10.f));

	// setup default weapon calls
	ON_CALL(*agent, getSlottedObject(TypedEq<const String&>("default_weapon")))
		.WillByDefault(Return(mockDefaultWeao.get()));
	ON_CALL(*mockDefaultWeao, getIdealRange()).WillByDefault(Return(5.f));
	ON_CALL(*mockDefaultWeao, getMaxRange()).WillByDefault(Return(10.f));

	// TODO: this should be un-mocked -- just set the weapon and test to make sure the right one got set
	EXPECT_CALL(*agent, setWeapon(_)).Times(0);
	EXPECT_CALL(*agent, setWeapon(TypedEq<uint32>(static_cast<uint32>(DataVal::DEFAULT)))).Times(1);

	// The first call to SelectAttack will either be Default or Special, and the second will always be
	// Default. Therefore, we can count number of times called. We expect it to be a total of 2, and 
	// Default should be called at least once.
	struct AttackTracker {
		bool defaultAttack() {
			++n;
			++def;
			return true;
		}

		bool specialAttack(int) {
			++n;
			return true;
		}

		int n = 0;
		int def = 0;
	};
	AttackTracker attackTracker;

	ON_CALL(*agent, selectDefaultAttack()).WillByDefault(Invoke(&attackTracker, &AttackTracker::defaultAttack));
	ON_CALL(*agent, selectSpecialAttack(Eq(-1))).WillByDefault(Invoke(&attackTracker, &AttackTracker::specialAttack));

	// setup the queue command
	MockQueueCommand* qCommand = new MockQueueCommand();
	ON_CALL(*agent, getNextAction()).WillByDefault(Return(qCommand));
	ON_CALL(*qCommand, getMaxRange()).WillByDefault(Return(10.f));
	ON_CALL(*agent, validateStateAttack()).WillByDefault(Return(false));
	
	agent->doMovement();

	EXPECT_EQ( attackTracker.n, 2);
	EXPECT_GT( attackTracker.def, 0);

	delete mockThreat;
	delete qCommand;
}

TEST_F(BehaviorTreeTest, MoveTest) {
	Locker locker(agent);

	agent->setCreatureBitmask(CreatureFlag::NONE);
	agent->setAITemplate();

	MockThreatMap* mockThreat = new MockThreatMap(followMock.get());
	ON_CALL(*agent, getThreatMap()).WillByDefault(Return(mockThreat));
	ON_CALL(*mockThreat, getHighestThreatCreature())
		.WillByDefault(Return(static_cast<CreatureObject*>(NULL)));

	ON_CALL(*agent, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*agent, setDestination()).WillByDefault(Return(1));
	ON_CALL(*agent, isRetreating()).WillByDefault(Return(false));
	ON_CALL(*agent, getCurrentSpeed()).WillByDefault(Return(1.f));
	ON_CALL(*agent, completeMove()).WillByDefault(Return(true));
	ON_CALL(*agent, getMaxDistance()).WillByDefault(Return(10.f));

	NiceMock<MockPatrolPoint>* pPoint = new NiceMock<MockPatrolPoint>();
	ON_CALL(*agent, getHomeLocation()).WillByDefault(Return(pPoint));
	ON_CALL(*pPoint, isInRange(TypedEq<SceneObject*>(followMock), FloatEq(256.f)))
		.WillByDefault(Return(true));

	EXPECT_CALL(*agent, findNextPosition(FloatEq(10.f), TypedEq<bool>(true)))
		.WillOnce(Return(true));
	EXPECT_CALL(*agent, setWait(_)).Times(0);

	agent->doMovement();

	delete mockThreat;
	delete pPoint;
}

TEST_F(BehaviorTreeTest, WaitTest) {
	Locker locker(agent);
	// wait is kind of boring since it's only one behavior. Let's use this opportunity to test the
	// running chain logic since Wait should return RUNNING.
	agent->setCreatureBitmask(CreatureFlag::NONE);
	agent->setAITemplate();

	MockThreatMap* mockThreat = new MockThreatMap(followMock.get());
	ON_CALL(*agent, getThreatMap()).WillByDefault(Return(mockThreat));
	ON_CALL(*mockThreat, getHighestThreatCreature())
		.WillByDefault(Return(static_cast<CreatureObject*>(NULL)));

	// okay, now our expectation is to move somewhere, and then wait. During the wait, we should set it
	// as a running task, so it should skip executing the movement part of the tree and go straight to the
	// wait.
	ON_CALL(*agent, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*agent, setDestination()).WillByDefault(Return(1));
	ON_CALL(*agent, isRetreating()).WillByDefault(Return(false));
	NiceMock<MockPatrolPoint>* pPoint = new NiceMock<MockPatrolPoint>();
	ON_CALL(*agent, getHomeLocation()).WillByDefault(Return(pPoint));
	ON_CALL(*pPoint, isInRange(TypedEq<SceneObject*>(followMock), FloatEq(256.f)))
		.WillByDefault(Return(true));
	ON_CALL(*agent, getCurrentSpeed()).WillByDefault(Return(1.f));
	ON_CALL(*agent, completeMove()).WillByDefault(Return(true));
	ON_CALL(*agent, getMaxDistance()).WillByDefault(Return(10.f));

	// this doubles to make sure that the default move operation is WALK
	EXPECT_CALL(*agent, findNextPosition(FloatEq(10.f), TypedEq<bool>(true)))
		.WillOnce(Return(false));

	// That series of calls equates to a single move tree traversal, now see if wait gets hit twice.
	EXPECT_CALL(*agent, setWait(TypedEq<int>(10000))).Times(2);

	// use two movements to simulate the btree getting run through twice
	agent->doMovement();
	agent->doMovement();

	delete mockThreat;
	delete pPoint;
}

TEST_F(BehaviorTreeTest, PetFollowTest) {
	Locker locker(agent);

	agent->setCreatureBitmask(CreatureFlag::PET);
	agent->setAITemplate();

	Reference<NiceMock<MockPetControlDevice>* > cd = new NiceMock<MockPetControlDevice>();
	agent->setControlDevice(cd);

	ON_CALL(*cd, getLastCommand()).WillByDefault(Return(PetManager::FOLLOW));

	MockThreatMap* mockThreat = new MockThreatMap(followMock.get());
	ON_CALL(*agent, getThreatMap()).WillByDefault(Return(mockThreat));
	ON_CALL(*mockThreat, getHighestThreatCreature())
		.WillByDefault(Return(static_cast<CreatureObject*>(NULL)));

	ON_CALL(*agent, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*agent, setDestination()).WillByDefault(Return(1));
	ON_CALL(*agent, getCurrentSpeed()).WillByDefault(Return(1.f));
	ON_CALL(*agent, completeMove()).WillByDefault(Return(true));
	ON_CALL(*agent, getMaxDistance()).WillByDefault(Return(10.f));

	// TODO: Is this all we need to test here?
	EXPECT_CALL(*agent, findNextPosition(FloatEq(10.f), TypedEq<bool>(false)))
		.WillOnce(Return(true));
	EXPECT_CALL(*agent, setWait(_)).Times(0);

	agent->doMovement();

	delete mockThreat;
}

TEST_F(BehaviorTreeTest, PetPatrolTest) {
	Locker locker(agent);

	agent->setCreatureBitmask(CreatureFlag::PET);
	agent->setAITemplate();

	Reference<NiceMock<MockPetControlDevice>* > cd = new NiceMock<MockPetControlDevice>();
	agent->setControlDevice(cd);

	agent->setFollowState(AiAgent::PATROLLING);
	ON_CALL(*cd, getLastCommand()).WillByDefault(Return(PetManager::PATROL));

	MockThreatMap* mockThreat = new MockThreatMap(followMock.get());
	ON_CALL(*agent, getThreatMap()).WillByDefault(Return(mockThreat));
	ON_CALL(*mockThreat, getHighestThreatCreature())
		.WillByDefault(Return(static_cast<CreatureObject*>(NULL)));

	ON_CALL(*agent, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*agent, setDestination()).WillByDefault(Return(1));
	ON_CALL(*agent, getCurrentSpeed()).WillByDefault(Return(1.f));
	ON_CALL(*agent, completeMove()).WillByDefault(Return(true));
	ON_CALL(*agent, getMaxDistance()).WillByDefault(Return(10.f));

	// TODO: Is this all we need to test here?
	EXPECT_CALL(*agent, findNextPosition(FloatEq(10.f), TypedEq<bool>(true)))
		.WillOnce(Return(true))
		.WillOnce(Return(false));
	EXPECT_CALL(*agent, setWait(_)).Times(0);
	EXPECT_CALL(*agent, setWait(5000)).Times(1);

	agent->doMovement();
	agent->doMovement();

	delete mockThreat;
}

TEST_F(BehaviorTreeTest, PetAttackTest) {
	Locker locker(agent);

	agent->setCreatureBitmask(CreatureFlag::PET);
	agent->setAITemplate();

	Reference<NiceMock<MockPetControlDevice>* > cd = new NiceMock<MockPetControlDevice>();
	agent->setControlDevice(cd);

	Reference<NiceMock<MockAiAgent>* > attackMock = new NiceMock<MockAiAgent>();

	ON_CALL(*cd, getLastCommand()).WillByDefault(Return(PetManager::ATTACK));
	ON_CALL(*cd, getLastCommandTarget()).WillByDefault(Return(attackMock.get()));
	ON_CALL(*followMock, isAttackableBy(TypedEq<CreatureObject*>(agent.get())))
		.WillByDefault(Return(false));

	ON_CALL(*attackMock, asCreatureObject()).WillByDefault(Return(attackMock));
	ON_CALL(*attackMock, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*attackMock, isAttackableBy(TypedEq<CreatureObject*>(agent.get())))
		.WillByDefault(Return(true));
	ON_CALL(*attackMock, isInRange(TypedEq<SceneObject*>(agent.get()), FloatEq(128.f)))
		.WillByDefault(Return(true));

	// TODO: get rid of this stuff, It's just to prevent the tree from getting to places
	// where we don't have things defined -- will be fixed by de-mockification
	ON_CALL(*agent, getDistanceTo(TypedEq<SceneObject*>(attackMock)))
		.WillByDefault(Return(5.f));
	ON_CALL(*agent, getReadyWeapon()).WillByDefault(Return(mockWeao));
	ON_CALL(*mockWeao, getMaxRange()).WillByDefault(Return(1.f));
	ON_CALL(*agent, getSlottedObject(TypedEq<const String&>("default_weapon")))
		.WillByDefault(Return(mockDefaultWeao.get()));
	ON_CALL(*mockDefaultWeao, getMaxRange()).WillByDefault(Return(1.f));

	agent->doMovement();

	EXPECT_TRUE( agent->getFollowState() == AiAgent::FOLLOWING );
	EXPECT_TRUE( agent->getFollowObject() == attackMock );
	EXPECT_TRUE( agent->getMainDefender() == attackMock );
}

TEST_F(BehaviorTreeTest, PetGuardTest) {
	Locker locker(agent);

	agent->setCreatureBitmask(CreatureFlag::PET);
	agent->setAITemplate();

	Reference<NiceMock<MockPetControlDevice>* > cd = new NiceMock<MockPetControlDevice>();
	agent->setControlDevice(cd);

	Reference<NiceMock<MockAiAgent>* > attackMock = new NiceMock<MockAiAgent>();

	{
		Locker fLocker(followMock, agent);
		followMock->setDefender(attackMock);
	}

	ON_CALL(*cd, getLastCommand()).WillByDefault(Return(PetManager::GUARD));
	ON_CALL(*cd, getLastCommandTarget()).WillByDefault(Return(followMock.get()));
	ON_CALL(*followMock, isAttackableBy(TypedEq<CreatureObject*>(agent.get())))
		.WillByDefault(Return(false));

	ON_CALL(*attackMock, asCreatureObject()).WillByDefault(Return(attackMock));
	ON_CALL(*attackMock, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*attackMock, isAttackableBy(TypedEq<CreatureObject*>(agent.get())))
		.WillByDefault(Return(true));
	ON_CALL(*attackMock, isInRange(TypedEq<SceneObject*>(agent.get()), FloatEq(128.f)))
		.WillByDefault(Return(true));

	// TODO: get rid of this stuff, It's just to prevent the tree from getting to places
	// where we don't have things defined -- will be fixed by de-mockification
	ON_CALL(*agent, getDistanceTo(TypedEq<SceneObject*>(attackMock)))
		.WillByDefault(Return(5.f));
	ON_CALL(*agent, getReadyWeapon()).WillByDefault(Return(mockWeao));
	ON_CALL(*mockWeao, getMaxRange()).WillByDefault(Return(1.f));
	ON_CALL(*agent, getSlottedObject(TypedEq<const String&>("default_weapon")))
		.WillByDefault(Return(mockDefaultWeao.get()));
	ON_CALL(*mockDefaultWeao, getMaxRange()).WillByDefault(Return(1.f));

	agent->doMovement();

	EXPECT_TRUE( agent->getFollowState() == AiAgent::FOLLOWING );
	EXPECT_TRUE( agent->getFollowObject() == attackMock );
	EXPECT_TRUE( agent->getMainDefender() == attackMock );
}

// Now we do overall tree tests
TEST_F(BehaviorTreeTest, LookTest) {
	Locker locker(agent);
	// Make sure we get a target when we previously have none
	//
	// In order to aggro, we need that we have a follow object, and that we are WATCHING it and it
	// is in range
	agent->setCreatureBitmask(CreatureFlag::NONE);
	agent->setAITemplate();

	MockThreatMap* mockThreat = new MockThreatMap(followMock.get());
	ON_CALL(*agent, getThreatMap()).WillByDefault(Return(mockThreat));
	EXPECT_CALL(*mockThreat, getHighestThreatCreature()).WillOnce(Return(static_cast<CreatureObject*>(NULL)));

	agent->setOblivious();
	agent->addInRangeObject(followMock);

	ON_CALL(*agent, isInRange(TypedEq<SceneObject*>(followMock.get()), _)).WillByDefault(Return(true));
	ON_CALL(*agent, isAggressiveTo(TypedEq<CreatureObject*>(followMock.get())))
		.WillByDefault(Return(true));
	ON_CALL(*agent, checkLineOfSight(TypedEq<SceneObject*>(followMock.get())))
		.WillByDefault(Return(true));
	ON_CALL(*agent, isAttackableBy(TypedEq<CreatureObject*>(followMock.get())))
		.WillByDefault(Return(true));
	ON_CALL(*followMock, isAttackableBy(TypedEq<CreatureObject*>(agent.get())))
		.WillByDefault(Return(true));
	ON_CALL(*agent, getLevel()).WillByDefault(Return(10));
	ON_CALL(*followMock, getLevel()).WillByDefault(Return(50));
	ON_CALL(*followMock, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*followMock, getLocomotion()).WillByDefault(Return(CreatureLocomotion::RUNNING));

	agent->doMovement();

	EXPECT_TRUE( agent->getFollowState() == AiAgent::WATCHING )
		<< "FollowState should be 1, got " << agent->getFollowState();
	EXPECT_TRUE( agent->getFollowObject() == followMock )
		<< "FollowObject should be " << followMock.get() << ", got " << agent->getFollowObject().get();

	delete mockThreat;
}

TEST_F(BehaviorTreeTest, AggroTest) {
	Locker locker(agent);
	// The basic idea of this test is to ensure that by default, aggroing with a full tree works
	// properly. We also need to make sure that we don't aggro when we aren't supposed to.
	//
	// In order to aggro, we need that we have a follow object, and that we are WATCHING it and it
	// is in range
	agent->setCreatureBitmask(CreatureFlag::NONE);
	agent->setAITemplate();

	MockThreatMap* mockThreat = new MockThreatMap(followMock.get());
	ON_CALL(*agent, getThreatMap()).WillByDefault(Return(mockThreat));
	EXPECT_CALL(*mockThreat, getHighestThreatCreature()).WillOnce(Return(static_cast<CreatureObject*>(NULL)));

	agent->setWatchObject(followMock);

	ON_CALL(*agent, isInRange(TypedEq<SceneObject*>(followMock.get()), _)).WillByDefault(Return(true));
	ON_CALL(*agent, isAggressiveTo(TypedEq<CreatureObject*>(followMock.get())))
		.WillByDefault(Return(true));
	ON_CALL(*agent, checkLineOfSight(TypedEq<SceneObject*>(followMock.get())))
		.WillByDefault(Return(true));

	agent->doMovement();

	EXPECT_TRUE( agent->getFollowState() == AiAgent::FOLLOWING );
	EXPECT_TRUE( agent->getFollowObject() == followMock );
	EXPECT_TRUE( agent->getMainDefender() == followMock );

	delete mockThreat;
}

TEST_F(BehaviorTreeTest, ScareTest) {
	Locker locker(agent);

	agent->setCreatureBitmask(CreatureFlag::NONE);
	agent->setAITemplate();

	MockThreatMap* mockThreat = new MockThreatMap(followMock.get());
	ON_CALL(*agent, getThreatMap()).WillByDefault(Return(mockThreat));
	EXPECT_CALL(*mockThreat, getHighestThreatCreature()).WillOnce(Return(static_cast<CreatureObject*>(NULL)));

	agent->setWatchObject(followMock);

	ON_CALL(*agent, getParent()).WillByDefault(Return(static_cast<SceneObject*>(NULL)));
	ON_CALL(*agent, getLevel()).WillByDefault(Return(1));
	
	ON_CALL(*agent, isInRange(TypedEq<SceneObject*>(followMock.get()), _)).WillByDefault(Return(true));
	ON_CALL(*agent, isAggressiveTo(TypedEq<CreatureObject*>(followMock.get())))
		.WillByDefault(Return(false));
	ON_CALL(*agent, checkLineOfSight(TypedEq<SceneObject*>(followMock.get())))
		.WillByDefault(Return(true));

	NiceMock<MockPatrolPoint>* pPoint = new NiceMock<MockPatrolPoint>();
	ON_CALL(*agent, getHomeLocation()).WillByDefault(Return(pPoint));
	ON_CALL(*pPoint, isInRange(TypedEq<SceneObject*>(agent), FloatEq(128.f)))
		.WillByDefault(Return(false));

	ON_CALL(*followMock, getLevel()).WillByDefault(Return(2));
	ON_CALL(*followMock, isAggressiveTo(TypedEq<CreatureObject*>(agent.get())))
		.WillByDefault(Return(true));
	ON_CALL(*followMock, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*followMock, getLocomotion()).WillByDefault(Return(CreatureLocomotion::RUNNING));
	ON_CALL(*followMock, isFacingObject(TypedEq<SceneObject*>(agent.get())))
		.WillByDefault(Return(true));
	
	agent->doMovement();

	EXPECT_TRUE( agent->getFollowState() == AiAgent::FLEEING )
		<< "FollowState should be 5, got " << agent->getFollowState();
	EXPECT_TRUE( agent->getFollowObject() == followMock )
		<< "FollowObject should be " << followMock.get() << ", got " << agent->getFollowObject().get();

	delete pPoint;
	delete mockThreat;
}
