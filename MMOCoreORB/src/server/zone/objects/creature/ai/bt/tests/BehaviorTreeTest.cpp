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
	Reference<node::Composite*> root;

	// some more mocks that get used most tests
	Reference<MockZone*> mockZone = new MockZone();
	Reference<NiceMock<MockCreatureObject>* > followMock = new NiceMock<MockCreatureObject>();
	Reference<MockWeaponObject* > mockWeao = new MockWeaponObject();

public:
	BehaviorTreeTest()
		: agent(new NiceMock<MockAiAgent>()), aiMap(AiMap::instance()), root(NULL) {}

	void SetUp() {
		ASSERT_TRUE( agent != NULL ) << "AiAgent failed to initialize";
		ASSERT_TRUE( aiMap != NULL ) << "AiMap failed to initialize";

		aiMap->loadTemplates();
		ASSERT_GT( aiMap->getTemplateSize(), 0 ) << "Did not load any AI templates";

		// ensure that aiMap is initialized before trying to load the example template
		root = cast<node::Composite*>(aiMap->getTemplate("example"));
		ASSERT_TRUE( root != NULL ) << "Failed to load example behavior tree";

		// set and forget the functions that get called a lot
		ON_CALL(*agent, isDead()).WillByDefault(Return(false));
		ON_CALL(*agent, isIncapacitated()).WillByDefault(Return(false));
		ON_CALL(*agent, getZone()).WillByDefault(Return(mockZone));
		ON_CALL(*agent, getFollowObject()).WillByDefault(Return(followMock.get()));
		ON_CALL(*agent, getTemplateRadius()).WillByDefault(Return(0.f));
		ON_CALL(*agent, getWeapon()).WillByDefault(Return(mockWeao));
		ON_CALL(*followMock, asCreatureObject()).WillByDefault(Return(followMock));
		ON_CALL(*followMock, asTangibleObject()).WillByDefault(Return(followMock));
		ON_CALL(*followMock, getTemplateRadius()).WillByDefault(Return(0.f));
		ON_CALL(*mockWeao, getMaxRange()).WillByDefault(Return(0.f));
	}

	~BehaviorTreeTest() {}
};

TEST_F(BehaviorTreeTest, ParentChildDuplicateTest) {
	HashTableIterator<String, Reference<Behavior*> > s_it(&(aiMap->aiMap));
	HashTableIterator<unsigned int, Reference<Behavior*> > b_it(&(aiMap->bitmaskMap));

	s_it.resetIterator();
	while (s_it.hasNext()) {
		Vector<const Behavior*> childList = s_it.getNextValue()->getRecursiveChildList();

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

	b_it.resetIterator();
	while (b_it.hasNext()) {
		Vector<const Behavior*> childList = b_it.getNextValue()->getRecursiveChildList();

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

TEST_F(BehaviorTreeTest, ExecuteBehaviorsTest) {
	// this test is for checking to ensure all behaviors perform their intended individual actions
	Reference<MockCreatureObject*> mockCreo = new MockCreatureObject();
	ManagedWeakReference<SceneObject*> scnoWeak = mockCreo.get();
	Reference<TangibleObject*> tano = mockCreo.get();

	EXPECT_CALL(*agent, generatePatrol(Eq(5),FloatEq(3.f)))
		.WillOnce(Return(true))
		.WillOnce(Return(false));
	TESTBEHAVIOR(GeneratePatrol, "numPoints=5:distFromHome=3", Behavior::SUCCESS);
	TESTBEHAVIOR(GeneratePatrol, "numPoints=5:distFromHome=3", Behavior::FAILURE);

	EXPECT_CALL(*agent, getFollowObject())
		.WillOnce(Return(followMock.get()))
		.WillOnce(Return(followMock.get()));
	EXPECT_CALL(*agent, isInRange(TypedEq<SceneObject*>(followMock), FloatEq(128.f)))
		.WillOnce(Return(true))
		.WillOnce(Return(false));
	TESTBEHAVIOR(CheckFollowInRange, "condition=128", Behavior::SUCCESS);
	TESTBEHAVIOR(CheckFollowInRange, "condition=128", Behavior::FAILURE);

	EXPECT_CALL(*agent, getFollowObject())
		.WillOnce(Return(followMock.get()))
		.WillOnce(Return(followMock.get()));
	EXPECT_CALL(*followMock, isAttackableBy(TypedEq<CreatureObject*>(agent.get())))
		.WillOnce(Return(true))
		.WillOnce(Return(false));
	TESTBEHAVIOR(CheckFollowAttackable, "", Behavior::SUCCESS);
	TESTBEHAVIOR(CheckFollowAttackable, "", Behavior::FAILURE);
}

TEST_F(BehaviorTreeTest, GetTargetTest) {
	// GetTarget should have the id "gettar0"
	ASSERT_TRUE( root->getChild(STRING_HASHCODE("attack")) != NULL );
	Behavior* gtRoot = root->getChild(STRING_HASHCODE("attack"))->getChild(STRING_HASHCODE("gettar0"));
	ASSERT_TRUE( gtRoot != NULL );

	agent->setRootBehavior(gtRoot);

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

	Locker locker(agent);
	agent->doMovement();

	delete mockThreat;
}

TEST_F(BehaviorTreeTest, SelectWeaponTest) {
	// SelectWeapon should have the id "selwep0"
	ASSERT_TRUE( root->getChild(STRING_HASHCODE("attack")) != NULL );
	Behavior* swRoot = root->getChild(STRING_HASHCODE("attack"))->getChild(STRING_HASHCODE("selwep0"));
	ASSERT_TRUE( swRoot != NULL );

	agent->setRootBehavior(swRoot);

	// and a mock default weao
	Reference<MockWeaponObject* > mockDefaultWeao = new MockWeaponObject();
	SceneObject* mockDefaultWeaoScno = mockDefaultWeao.get();

	// expect Update range (where we test blackboard writing)
	EXPECT_CALL(*agent, getDistanceTo(TypedEq<SceneObject*>(followMock)))
		.WillOnce(Return(5.f)); // use 5 to compare to BlackboardData
	// then inweaponrange (ranged), which succeeds
	EXPECT_CALL(*agent, getReadyWeapon())
		.WillOnce(Return(mockWeao))
		.WillOnce(Return(mockWeao))
		.WillOnce(Return(mockDefaultWeao))
		.WillOnce(Return(mockDefaultWeao));
	EXPECT_CALL(*mockWeao, getMaxRange())
		.WillOnce(Return(10.f));
	// then closestidealrange (ranged) which fails
	EXPECT_CALL(*agent, getSlottedObject(TypedEq<const String&>("default_weapon")))
		.WillOnce(Return(mockDefaultWeaoScno))
		.WillOnce(Return(mockDefaultWeaoScno));
	EXPECT_CALL(*mockWeao, getIdealRange())
		.WillOnce(Return(10.f));
	EXPECT_CALL(*mockDefaultWeao, getIdealRange())
		.WillOnce(Return(5.f))
		.WillOnce(Return(5.f))
		.WillOnce(Return(5.f));
	// then inweaponrange (melee) which succeeds
	EXPECT_CALL(*mockDefaultWeao, getMaxRange())
		.WillOnce(Return(10.f));
	// closestidealrange (melee) succeeds
	// stageweapon succeeds
	// equipweapon succeeds
	EXPECT_CALL(*agent, setWeapon(TypedEq<uint32>(AiAgent::WEAPONMELEE))).Times(1);
	// eraseBB x2 (once for fR and once for sW)
	Locker locker(agent);
	agent->doMovement();

	// force the order of clearing, or else gmock introduces a deadlock
	Mock::VerifyAndClear(agent);
	Mock::VerifyAndClear(mockWeao);
	Mock::VerifyAndClear(mockDefaultWeao);
}

TEST_F(BehaviorTreeTest, SelectAttackTest) {
	// SelectAttack should have the id "selatt0"
	ASSERT_TRUE( root->getChild(STRING_HASHCODE("attack")) != NULL );
	Behavior* saRoot = root->getChild(STRING_HASHCODE("attack"))->getChild(STRING_HASHCODE("selatt0"));
	ASSERT_TRUE( saRoot != NULL );

	agent->setRootBehavior(saRoot);

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
	
	Locker locker(agent);
	agent->doMovement();

	delete qCommand;
}

TEST_F(BehaviorTreeTest, CombatMoveTest) {
	// CombatMove should have the id "commove0"
	ASSERT_TRUE( root->getChild(STRING_HASHCODE("attack")) != NULL );
	Behavior* cmRoot = root->getChild(STRING_HASHCODE("attack"))->getChild(STRING_HASHCODE("commove0"));
	ASSERT_TRUE( cmRoot != NULL );

	agent->setRootBehavior(cmRoot);

	EXPECT_CALL(*agent, getPosture())
		.WillOnce(Return(CreaturePosture::UPRIGHT));
	EXPECT_CALL(*agent, setDestination())
		.WillOnce(Return(1));
	EXPECT_CALL(*agent, isRetreating()).WillOnce(Return(false));
	MockPatrolPoint* pPoint = new MockPatrolPoint();
	EXPECT_CALL(*agent, getHomeLocation())
		.WillOnce(Return(pPoint));
	EXPECT_CALL(*pPoint, isInRange(TypedEq<SceneObject*>(followMock), FloatEq(256.f)))
		.WillOnce(Return(true));
	EXPECT_CALL(*agent, leash()).Times(0); // make sure leash doesn't get called
	EXPECT_CALL(*agent, getCurrentSpeed()).WillOnce(Return(1.f));
	EXPECT_CALL(*agent, completeMove()).WillOnce(Return(true));
	EXPECT_CALL(*agent, getMaxDistance()).WillOnce(Return(10.f));
	EXPECT_CALL(*agent, findNextPosition(FloatEq(10.f), TypedEq<bool>(false)))
		.WillOnce(Return(true));

	Locker locker(agent);
	agent->doMovement();

	delete pPoint;
}

TEST_F(BehaviorTreeTest, WalkMoveTest) {
	// WalkMove should have the id "walkmove0"
	ASSERT_TRUE( root->getChild(STRING_HASHCODE("wander")) != NULL );
	ASSERT_TRUE( root->getChild(STRING_HASHCODE("wander"))->getChild(STRING_HASHCODE("wander0")) != NULL );
	Behavior* wmRoot = root->getChild(STRING_HASHCODE("wander"))->getChild(STRING_HASHCODE("wander0"))->getChild(STRING_HASHCODE("walkmove0"));
	ASSERT_TRUE( wmRoot != NULL );

	agent->setRootBehavior(wmRoot);

	EXPECT_CALL(*agent, getPosture())
		.WillOnce(Return(CreaturePosture::UPRIGHT));
	EXPECT_CALL(*agent, setDestination())
		.WillOnce(Return(1));
	EXPECT_CALL(*agent, isRetreating()).WillOnce(Return(false));
	MockPatrolPoint* pPoint = new MockPatrolPoint();
	EXPECT_CALL(*agent, getHomeLocation())
		.WillOnce(Return(pPoint));
	EXPECT_CALL(*pPoint, isInRange(TypedEq<SceneObject*>(followMock), FloatEq(256.f)))
		.WillOnce(Return(true));
	EXPECT_CALL(*agent, leash()).Times(0); // make sure leash doesn't get called
	EXPECT_CALL(*agent, getCurrentSpeed()).WillOnce(Return(1.f));
	EXPECT_CALL(*agent, completeMove()).WillOnce(Return(true));
	EXPECT_CALL(*agent, getMaxDistance()).WillOnce(Return(10.f));
	EXPECT_CALL(*agent, findNextPosition(FloatEq(10.f), TypedEq<bool>(true)))
		.WillOnce(Return(true));

	Locker locker(agent);
	agent->doMovement();

	delete pPoint;
}

TEST_F(BehaviorTreeTest, WaitTest) {
	// Wait should have the id "wait0"
	ASSERT_TRUE( root->getChild(STRING_HASHCODE("wander")) != NULL );

	// wait is kind of boring since it's only one behavior. Let's use this opportunity to test the
	// running chain logic since Wait should return RUNNING.

	// now grab the entire wander tree so we can test the running chain (which should trigger on wait)
	// we have an extra level of sequences that will act as "root" for the purpose of this test
	Behavior* wanderRoot = root->getChild(STRING_HASHCODE("wander")); // already been null checked
	agent->setRootBehavior(wanderRoot);

	// okay, now our expectation is to move somewhere, and then wait. During the wait, we should set it
	// as a running task, so it should skip executing the movement part of the tree and go straight to the
	// wait.
	EXPECT_CALL(*agent, getPosture())
		.WillOnce(Return(CreaturePosture::UPRIGHT));
	EXPECT_CALL(*agent, setDestination())
		.WillOnce(Return(1));
	EXPECT_CALL(*agent, isRetreating()).WillOnce(Return(false));
	MockPatrolPoint* pPoint = new MockPatrolPoint();
	EXPECT_CALL(*agent, getHomeLocation())
		.WillOnce(Return(pPoint));
	EXPECT_CALL(*pPoint, isInRange(TypedEq<SceneObject*>(followMock), FloatEq(256.f)))
		.WillOnce(Return(true));
	EXPECT_CALL(*agent, leash()).Times(0); // make sure leash doesn't get called
	EXPECT_CALL(*agent, getCurrentSpeed()).WillOnce(Return(1.f));
	EXPECT_CALL(*agent, completeMove()).WillOnce(Return(true));
	EXPECT_CALL(*agent, getMaxDistance()).WillOnce(Return(10.f));
	EXPECT_CALL(*agent, findNextPosition(FloatEq(10.f), TypedEq<bool>(true)))
		.WillOnce(Return(true));

	// That series of calls equates to a single move tree traversal, now see if wait gets hit twice.
	EXPECT_CALL(*agent, setWait(TypedEq<int>(10000))).Times(2);

	Locker locker(agent);
	// use two movements to simulate the btree getting run through twice
	agent->doMovement();
	agent->doMovement();

	delete pPoint;
}

