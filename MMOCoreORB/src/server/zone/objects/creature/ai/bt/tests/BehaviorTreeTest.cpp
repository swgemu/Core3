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

public:
	BehaviorTreeTest()
		: agent(new NiceMock<MockAiAgent>()), aiMap(AiMap::instance()) {}

	void SetUp() {
		ASSERT_TRUE( agent != NULL ) << "AiAgent failed to initialize";
		ASSERT_TRUE( aiMap != NULL ) << "AiMap failed to initialize";

		ConfigManager::instance()->loadConfigData();
		TemplateManager::instance();
		ASSERT_EQ(TemplateManager::ERROR_CODE, 0);

		aiMap->loadTemplates();
		ASSERT_GT( aiMap->getTemplateSize(), 0 ) << "Did not load any AI templates";

		// set and forget the functions that get called a lot
		ON_CALL(*agent, isDead()).WillByDefault(Return(false));
		ON_CALL(*agent, isIncapacitated()).WillByDefault(Return(false));
		ON_CALL(*agent, getZone()).WillByDefault(Return(mockZone));
		ON_CALL(*agent, getFollowObject()).WillByDefault(Return(followMock.get()));
		ON_CALL(*agent, getTemplateRadius()).WillByDefault(Return(0.f));
		ON_CALL(*agent, getWeapon()).WillByDefault(Return(mockWeao));
		ON_CALL(*followMock, asAiAgent()).WillByDefault(Return(followMock));
		ON_CALL(*followMock, asCreatureObject()).WillByDefault(Return(followMock));
		ON_CALL(*followMock, asTangibleObject()).WillByDefault(Return(followMock));
		ON_CALL(*followMock, getTemplateRadius()).WillByDefault(Return(0.f));
		ON_CALL(*mockWeao, getMaxRange()).WillByDefault(Return(0.f));
	}

	~BehaviorTreeTest() {}
};

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

		const Behavior* testB = agent->getBehaviorTree(BehaviorTreeSlot::NONE);
		
		EXPECT_TRUE(testB != NULL);
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

TEST_F(BehaviorTreeTest, GetTargetTest) {
	Locker locker(agent);

	// GetTarget should have the id "gettar0"
	Behavior* gtRoot = aiMap->getTemplate("targetDefault");
	ASSERT_TRUE( gtRoot != NULL );

	agent->setTree(gtRoot, BehaviorTreeSlot::NONE);

	// setup the mock threatmap
	MockThreatMap* mockThreat = new MockThreatMap(followMock.get());
	ON_CALL(*agent, getThreatMap()).WillByDefault(Return(mockThreat));

	// work the tree from left to right to ensure that everything works
	// first make sure getting a target from the map doesn't also get a target from defenders
	EXPECT_CALL(*mockThreat, getHighestThreatCreature()).WillOnce(Return(followMock)); // expect one call
	EXPECT_CALL(*agent, getMainDefender()).Times(0);

	// go ahead and succeed all the checks so UntilSucceed passes -- the end result should be that
	// we DON'T exit combat
	EXPECT_CALL(*agent, isInRange(TypedEq<SceneObject*>(followMock.get()), FloatEq(128.f)))
		.WillOnce(Return(true));
	EXPECT_CALL(*followMock, isAttackableBy(TypedEq<CreatureObject*>(agent.get())))
		.WillOnce(Return(true));
	EXPECT_CALL(*followMock, getPosture())
		.WillOnce(Return(CreaturePosture::UPRIGHT))
		.WillOnce(Return(CreaturePosture::UPRIGHT));
	EXPECT_CALL(*agent, hasDefender(TypedEq<SceneObject*>(followMock.get()))).WillOnce(Return(true));
	EXPECT_CALL(*followMock, hasState(CreatureState::PEACE)).WillOnce(Return(false));
	EXPECT_CALL(*agent, clearCombatState(_)).Times(0);

	agent->doMovement();

	delete mockThreat;
}

TEST_F(BehaviorTreeTest, SelectWeaponTest) {
	Locker locker(agent);

	Behavior* swRoot = aiMap->getTemplate("equipDefault");
	ASSERT_TRUE( swRoot != NULL );

	agent->setTree(swRoot, BehaviorTreeSlot::NONE);

	// and a mock default weao
	Reference<NiceMock<MockWeaponObject>* > mockDefaultWeao = new NiceMock<MockWeaponObject>();

	// expect Update range (where we test blackboard writing)
	ON_CALL(*agent, getDistanceTo(TypedEq<SceneObject*>(followMock)))
		.WillByDefault(Return(5.f)); // use 5 to compare to BlackboardData

	// then inweaponrange (ranged), which succeeds
	ON_CALL(*agent, getReadyWeapon()).WillByDefault(Return(mockWeao));
	ON_CALL(*mockWeao, getMaxRange()).WillByDefault(Return(10.f));
	ON_CALL(*mockWeao, getIdealRange()).WillByDefault(Return(10.f));

	// then closestidealrange (ranged) which fails
	ON_CALL(*agent, getSlottedObject(TypedEq<const String&>("default_weapon")))
		.WillByDefault(Return(mockDefaultWeao.get()));
	ON_CALL(*mockDefaultWeao, getIdealRange()).WillByDefault(Return(5.f));
	// then inweaponrange (melee) which succeeds
	ON_CALL(*mockDefaultWeao, getMaxRange()).WillByDefault(Return(10.f));
	// closestidealrange (melee) succeeds
	// stageweapon succeeds
	// equipweapon succeeds
	EXPECT_CALL(*agent, setWeapon(_)).Times(0);
	EXPECT_CALL(*agent, setWeapon(TypedEq<uint32>(static_cast<uint32>(DataVal::DEFAULT)))).Times(1);
	// eraseBB x2 (once for fR and once for sW)
	agent->doMovement();

	// force the order of clearing, or else gmock introduces a deadlock
	Mock::VerifyAndClear(agent);
	Mock::VerifyAndClear(mockWeao);
	Mock::VerifyAndClear(mockDefaultWeao);
}

TEST_F(BehaviorTreeTest, SelectAttackTest) {
	Locker locker(agent);

	Behavior* saRoot = aiMap->getTemplate("attackDefault");
	ASSERT_TRUE( saRoot != NULL );

	agent->setTree(saRoot, BehaviorTreeSlot::NONE);

	// Either selectDefaultAttack or selectSpecialAttack(-1) called
	// TODO: how do I set up an either/or relationship?
	EXPECT_CALL(*agent, selectDefaultAttack())
		.Times(AtMost(2))
		.WillRepeatedly(Return(true));
	EXPECT_CALL(*agent, selectSpecialAttack(Eq(-1)))
		.Times(AtMost(1))
		.WillRepeatedly(Return(true));
	// getNextAction()
	MockQueueCommand* qCommand = new MockQueueCommand();
	EXPECT_CALL(*agent, getNextAction())
		.WillOnce(Return(qCommand));
	// qCommand->getMaxRange() x 3
	EXPECT_CALL(*qCommand, getMaxRange())
		.Times(3)
		.WillRepeatedly(Return(10.f));
	// follow->isInRange()
	EXPECT_CALL(*followMock, isInRange(TypedEq<SceneObject*>(agent.get()), FloatEq(10.f)))
		.WillOnce(Return(true));
	// agent->validateStateAttack() (false)
	EXPECT_CALL(*agent, validateStateAttack())
		.WillOnce(Return(false));
	// agent->selectDefaultAttack()
	
	agent->doMovement();

	delete qCommand;
}

TEST_F(BehaviorTreeTest, MoveTest) {
	Locker locker(agent);

	Behavior* cmRoot = aiMap->getTemplate("moveDefault");
	ASSERT_TRUE( cmRoot != NULL );

	agent->setTree(cmRoot, BehaviorTreeSlot::NONE);

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

	EXPECT_CALL(*agent, leash()).Times(0); // make sure leash doesn't get called
	EXPECT_CALL(*agent, findNextPosition(FloatEq(10.f), TypedEq<bool>(false)))
		.WillOnce(Return(true));

	agent->writeBlackboard("moveMode", static_cast<uint32>(DataVal::RUN));

	agent->doMovement();

	agent->eraseBlackboard("moveMode");

	delete pPoint;
}

TEST_F(BehaviorTreeTest, WaitTest) {
	Locker locker(agent);
	// wait is kind of boring since it's only one behavior. Let's use this opportunity to test the
	// running chain logic since Wait should return RUNNING.

	// now grab the entire wander tree so we can test the running chain (which should trigger on wait)
	// we have an extra level of sequences that will act as "root" for the purpose of this test
	Behavior* wanderRoot = aiMap->getTemplate("wanderDefault");
	ASSERT_TRUE( wanderRoot != NULL );
	agent->setTree(wanderRoot, BehaviorTreeSlot::NONE);

	Behavior* moveRoot = aiMap->getTemplate("moveDefault");
	ASSERT_TRUE ( moveRoot != NULL );
	agent->setTree(moveRoot, BehaviorTreeSlot::MOVE);

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

	EXPECT_CALL(*agent, leash()).Times(0); // make sure leash doesn't get called
	// this doubles to make sure that the default move operation is WALK
	EXPECT_CALL(*agent, findNextPosition(FloatEq(10.f), TypedEq<bool>(true)))
		.WillOnce(Return(true));

	// That series of calls equates to a single move tree traversal, now see if wait gets hit twice.
	EXPECT_CALL(*agent, setWait(TypedEq<int>(10000))).Times(2);

	// use two movements to simulate the btree getting run through twice
	agent->doMovement();
	agent->doMovement();

	agent->removeTree(BehaviorTreeSlot::MOVE);

	delete pPoint;
}

TEST_F(BehaviorTreeTest, LookTest) {
	Locker locker(agent);

	Behavior* lookRoot = aiMap->getTemplate("lookDefault");
	ASSERT_TRUE( lookRoot != NULL );
	agent->setTree(lookRoot, BehaviorTreeSlot::NONE);

	ON_CALL(*agent, getFollowState()).WillByDefault(Return(AiAgent::OBLIVIOUS));
	ON_CALL(*agent, checkLineOfSight(TypedEq<SceneObject*>(followMock.get())))
		.WillByDefault(Return(true));

	// these should give a speed of FAST
	CreaturePosture::instance()->loadMovementData();
	ON_CALL(*followMock, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*followMock, getLocomotion()).WillByDefault(Return(CreatureLocomotion::RUNNING));
	
	EXPECT_CALL(*agent, setWatchObject(TypedEq<SceneObject*>(followMock.get()))).Times(1);

	agent->doMovement();
}

TEST_F(BehaviorTreeTest, AggroTest) {
	Locker locker(agent);

	Behavior* aggroRoot = aiMap->getTemplate("aggroDefault");
	ASSERT_TRUE( aggroRoot != NULL );
	agent->setTree(aggroRoot, BehaviorTreeSlot::NONE);

	ON_CALL(*agent, isAggressiveTo(TypedEq<CreatureObject*>(followMock.get())))
		.WillByDefault(Return(true));
	ON_CALL(*agent, checkLineOfSight(TypedEq<SceneObject*>(followMock.get())))
		.WillByDefault(Return(true));

	EXPECT_CALL(*agent, setDefender(TypedEq<SceneObject*>(followMock.get())))
		.Times(1);

	agent->doMovement();
}

TEST_F(BehaviorTreeTest, ScareTest) {
	Locker locker(agent);

	Behavior* scareRoot = aiMap->getTemplate("scareDefault");
	ASSERT_TRUE( scareRoot != NULL );
	agent->setTree(scareRoot, BehaviorTreeSlot::NONE);

	ON_CALL(*agent, getParent()).WillByDefault(Return(static_cast<SceneObject*>(NULL)));
	ON_CALL(*agent, getLevel()).WillByDefault(Return(1));
	ON_CALL(*agent, checkLineOfSight(TypedEq<SceneObject*>(followMock.get())))
		.WillByDefault(Return(true));

	ON_CALL(*followMock, getLevel()).WillByDefault(Return(2));
	ON_CALL(*followMock, isAggressiveTo(TypedEq<CreatureObject*>(agent.get())))
		.WillByDefault(Return(true));
	ON_CALL(*followMock, getPosture()).WillByDefault(Return(CreaturePosture::UPRIGHT));
	ON_CALL(*followMock, getLocomotion()).WillByDefault(Return(CreatureLocomotion::RUNNING));
	ON_CALL(*followMock, isFacingObject(TypedEq<SceneObject*>(agent.get())))
		.WillByDefault(Return(true));

	EXPECT_CALL(*agent, runAway(TypedEq<CreatureObject*>(followMock.get()), FloatEq(40.f)))
		.Times(1);
	
	agent->doMovement();
}

