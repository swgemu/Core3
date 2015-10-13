/*
 * BehaviorTreeTest.cpp
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "server/zone/Zone.h"
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
using ::testing::FloatEq;
using ::testing::TypedEq;
using ::testing::Mock;
using ::testing::NiceMock;

class BehaviorTreeTest : public ::testing::Test {
protected:
	// These three things are the heart of all tests, so ensure they all
	// get set up in this object
	Reference<NiceMock<MockAiAgent>* > agent;
	Reference<AiMap*> aiMap;
	Reference<node::Composite*> root;

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
		.WillOnce(Return(scnoWeak))
		.WillOnce(Return(scnoWeak));
	EXPECT_CALL(*agent, isInRange(TypedEq<SceneObject*>(mockCreo.get()), FloatEq(128.f)))
		.WillOnce(Return(true))
		.WillOnce(Return(false));
	TESTBEHAVIOR(CheckFollowInRange, "condition=128", Behavior::SUCCESS);
	TESTBEHAVIOR(CheckFollowInRange, "condition=128", Behavior::FAILURE);

	EXPECT_CALL(*agent, getFollowObject())
		.WillOnce(Return(scnoWeak))
		.WillOnce(Return(scnoWeak));
	EXPECT_CALL(*mockCreo, asTangibleObject())
		.WillOnce(Return(tano))
		.WillOnce(Return(tano));
	EXPECT_CALL(*mockCreo, isAttackableBy(TypedEq<CreatureObject*>(agent.get())))
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

	// create a mock follow object to reuse
	Reference<NiceMock<MockCreatureObject>* > mockCreo = new NiceMock<MockCreatureObject>();
	CreatureObject* creo = mockCreo.get();
	TangibleObject* tano = mockCreo.get();
	ManagedWeakReference<SceneObject*> scnoWeak = mockCreo.get();

	// need a mock zone for checkConditions -- this can be a raw pointer because getZone() returns a 
	// raw pointer
	MockZone* mockZone = new MockZone();

	// set and forget the functions that get called a lot
	MockThreatMap* mockThreat = new MockThreatMap(mockCreo.get());
	ON_CALL(*agent, isDead()).WillByDefault(Return(false));
	ON_CALL(*agent, isIncapacitated()).WillByDefault(Return(false));
	ON_CALL(*agent, getZone()).WillByDefault(Return(mockZone));
	ON_CALL(*agent, getFollowObject()).WillByDefault(Return(scnoWeak));
	ON_CALL(*agent, getThreatMap()).WillByDefault(Return(mockThreat));
	ON_CALL(*mockCreo, asCreatureObject()).WillByDefault(Return(creo));
	ON_CALL(*mockCreo, asTangibleObject()).WillByDefault(Return(tano));

	// work the tree from left to right to ensure that everything works
	// first make sure getting a target from the map doesn't also get a target from defenders
	EXPECT_CALL(*mockThreat, getHighestThreatCreature()).WillOnce(Return(creo)); // expect one call
	EXPECT_CALL(*agent, getMainDefender()).Times(0);

	// go ahead and succeed all the checks so UntilSucceed passes -- the end result should be that
	// we DON'T exit combat
	EXPECT_CALL(*agent, isInRange(TypedEq<SceneObject*>(mockCreo.get()), FloatEq(128.f)))
		.WillOnce(Return(true));
	EXPECT_CALL(*mockCreo, isAttackableBy(TypedEq<CreatureObject*>(agent.get())))
		.WillOnce(Return(true));
	EXPECT_CALL(*mockCreo, getPosture())
		.WillOnce(Return(CreaturePosture::UPRIGHT))
		.WillOnce(Return(CreaturePosture::UPRIGHT));
	EXPECT_CALL(*agent, hasDefender(TypedEq<SceneObject*>(mockCreo.get()))).WillOnce(Return(true));
	EXPECT_CALL(*mockCreo, hasState(CreatureState::PEACE)).WillOnce(Return(false));
	EXPECT_CALL(*agent, clearCombatState(_)).Times(0);

	Locker locker(agent);
	gtRoot->doAction(agent.get());

	delete mockThreat;
	// don't delete mockZone here because somewhere a reference grabbed it and started counting. GC will handle it.
}

TEST_F(BehaviorTreeTest, SelectWeaponTest) {
	// SelectWeapon should have the id "selwep0"
	ASSERT_TRUE( root->getChild(STRING_HASHCODE("attack")) != NULL );
	Behavior* swRoot = root->getChild(STRING_HASHCODE("attack"))->getChild(STRING_HASHCODE("selwep0"));
	ASSERT_TRUE( swRoot != NULL );

	// create a mock follow object to reuse
	Reference<NiceMock<MockCreatureObject>* > mockCreo = new NiceMock<MockCreatureObject>();
	CreatureObject* creo = mockCreo.get();
	TangibleObject* tano = mockCreo.get();
	ManagedWeakReference<SceneObject*> scnoWeak = mockCreo.get();

	// and a mock weao
	Reference<MockWeaponObject* > mockWeao = new MockWeaponObject();
	Reference<MockWeaponObject* > mockDefaultWeao = new MockWeaponObject();
	SceneObject* mockDefaultWeaoScno = mockDefaultWeao.get();

	// and since this tree test blackboards, I'm going to make a blackboard to use
	// all the agent functions just wrap the map functions, so we'll use live
	// data from thie blackboard as the mock returns
	BlackboardDataMap blackboard;

	// need a mock zone for checkConditions -- this can be a raw pointer because getZone() returns a 
	// raw pointer
	MockZone* mockZone = new MockZone();

	// set and forget the functions that get called a lot
	ON_CALL(*agent, isDead()).WillByDefault(Return(false));
	ON_CALL(*agent, isIncapacitated()).WillByDefault(Return(false));
	ON_CALL(*agent, getZone()).WillByDefault(Return(mockZone));
	ON_CALL(*agent, getFollowObject()).WillByDefault(Return(scnoWeak));
	ON_CALL(*agent, getTemplateRadius()).WillByDefault(Return(0));
	ON_CALL(*mockCreo, asCreatureObject()).WillByDefault(Return(creo));
	ON_CALL(*mockCreo, asTangibleObject()).WillByDefault(Return(tano));
	ON_CALL(*mockCreo, getTemplateRadius()).WillByDefault(Return(0));

	// expect Update range (where we test blackboard writing)
	EXPECT_CALL(*agent, getDistanceTo(TypedEq<SceneObject*>(creo)))
		.WillOnce(Return(5.f)); // use 5 to compare to BlackboardData
	EXPECT_CALL(*agent, writeBlackboard(TypedEq<const String&>("followRange"), 
						TypedEq<const BlackboardData&>(BlackboardData(5.f))))
		.Times(1);
	blackboard.put("followRange", BlackboardData(5.f)); // simulate the agent's blackboard
	// then inweaponrange (ranged), which succeeds
	EXPECT_CALL(*agent, peekBlackboard(TypedEq<const String&>("followRange")))
		.WillOnce(Return(blackboard.contains("followRange")))
		.WillOnce(Return(blackboard.contains("followRange")))
		.WillOnce(Return(blackboard.contains("followRange")))
		.WillOnce(Return(blackboard.contains("followRange")));
	EXPECT_CALL(*agent, readBlackboard(TypedEq<const String&>("followRange")))
		.WillOnce(Return(blackboard.get("followRange")))
		.WillOnce(Return(blackboard.get("followRange")))
		.WillOnce(Return(blackboard.get("followRange")))
		.WillOnce(Return(blackboard.get("followRange")));
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
	EXPECT_CALL(*agent, writeBlackboard(TypedEq<const String&>("stagedWeapon"), 
						TypedEq<const BlackboardData&>(BlackboardData(AiAgent::WEAPONMELEE))))
		.Times(1);
	blackboard.put("stagedWeapon", BlackboardData(AiAgent::WEAPONMELEE)); // simulate the agent's blackboard
	// equipweapon succeeds
	EXPECT_CALL(*agent, peekBlackboard(TypedEq<const String&>("stagedWeapon")))
		.WillOnce(Return(blackboard.contains("stagedWeapon")));
	EXPECT_CALL(*agent, readBlackboard(TypedEq<const String&>("stagedWeapon")))
		.WillOnce(Return(blackboard.get("stagedWeapon")));
	EXPECT_CALL(*agent, setWeapon(TypedEq<uint32>(blackboard.get("stagedWeapon").get<uint32>()))).Times(1);
	// eraseBB x2 (once for fR and once for sW)
	EXPECT_CALL(*agent, eraseBlackboard(TypedEq<const String&>("followRange"))).Times(1);
	EXPECT_CALL(*agent, eraseBlackboard(TypedEq<const String&>("stagedWeapon"))).Times(1);

	// Don't actually need to do this, but do it just to make sure that the blackboard
	// doesn't throw or something weird
	blackboard.drop("followRange");
	blackboard.drop("stagedWeapon");

	Locker locker(agent);
	swRoot->doAction(agent.get());

	// force the order of clearing, or else gmock introduces a deadlock
	Mock::VerifyAndClear(agent);
	Mock::VerifyAndClear(mockWeao);
	Mock::VerifyAndClear(mockDefaultWeao);
}

TEST_F(BehaviorTreeTest, SelectAttackTest) {
}

TEST_F(BehaviorTreeTest, CombatMoveTest) {
}

TEST_F(BehaviorTreeTest, WalkMoveTest) {
}

TEST_F(BehaviorTreeTest, WaitTest) {
}

