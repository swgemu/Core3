/*
 * BehaviorTreeTest.cpp
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "server/zone/managers/creature/AiMap.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/bt/Behavior.h"

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

class BehaviorTreeTest : public ::testing::Test {
protected:
	// These three things are the heart of all tests, so ensure they all
	// get set up in this object
	Reference<MockAiAgent*> agent;
	Reference<AiMap*> aiMap;
	Reference<Behavior*> root;

public:
	BehaviorTreeTest()
		: agent(new MockAiAgent()), aiMap(AiMap::instance()), root(NULL) {}

	void SetUp() {
		ASSERT_TRUE( agent != NULL ) << "AiAgent failed to initialize";
		ASSERT_TRUE( aiMap != NULL ) << "AiMap failed to initialize";

		aiMap->loadTemplates();
		ASSERT_GT( aiMap->getTemplateSize(), 0 ) << "Did not load any AI templates";

		// ensure that aiMap is initialized before trying to load the example template
		root = aiMap->getTemplate("example");
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
