#ifndef BEHAVIORMOCKS_H_
#define BEHAVIORMOCKS_H_

#include "gmock/gmock.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"

class MockQueueCommand : public QueueCommand {
public:
	MockQueueCommand() : QueueCommand("", NULL) {}
    MOCK_CONST_METHOD0(getMaxRange, float());
	MOCK_CONST_METHOD3(doQueueCommand, int(CreatureObject*, const uint64&, const UnicodeString&));
};

class MockThreatMap : public ThreatMap {
public:
	MockThreatMap(TangibleObject* t) : ThreatMap(t) {}
    MOCK_METHOD0(getHighestThreatCreature, CreatureObject*());
};

class MockPatrolPoint : public PatrolPoint {
public:
	MockPatrolPoint() : PatrolPoint() {}
	MOCK_METHOD2(isInRange, bool(SceneObject*, float));
};

#endif // BEHAVIORMOCKS_H_
