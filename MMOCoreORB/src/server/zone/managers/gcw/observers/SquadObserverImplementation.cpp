/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/managers/gcw/observers/SquadObserver.h"

#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/TangibleObject.h"

void SquadObserverImplementation::addMember(AiAgent* member) {
	if (member == nullptr)
		return;

	Locker locker(&squadLock);
	teamMembers.add(member);
}

AiAgent* SquadObserverImplementation::getMember(int index) {
	Locker locker(&squadLock);

	if (index >= teamMembers.size())
		return nullptr;

	return teamMembers.get(index);
}

void SquadObserverImplementation::despawnSquad() {
	Locker lock(&squadLock);

	int size = teamMembers.size();

	for (int i = size - 1; i >= 0; --i) {
		auto member = teamMembers.get(i);

		if (member == nullptr || member->isInCombat())
			continue;

		Locker clocker(member, &squadLock);

		member->dropObserver(ObserverEventType::SQUAD, _this.getReferenceUnsafeStaticCast());

		if (!member->isDead())
			member->destroyObjectFromWorld(true);
	}
}

bool SquadObserverImplementation::despawnMembersCloseToLambdaShuttle(const Vector3& landingPosition, bool forcedCleanup) {
	Locker lock(&squadLock);

	for (int i = size() - 1; i >= 0; i--) {
		auto member = getMember(i);

		if (member == nullptr) {
			teamMembers.remove(i);
			continue;
		}

		Locker cLock(member, &squadLock);

		auto distance = member->getWorldPosition().squaredDistanceTo(landingPosition);

		if (member->isDead()) {
			member->dropObserver(ObserverEventType::SQUAD, _this.getReferenceUnsafeStaticCast());
			removeMember(i);

			continue;
		}

		if (!forcedCleanup && distance > 8 * 8 && !member->isInCombat())
				continue;

		member->getCooldownTimerMap()->updateToCurrentAndAddMili("reaction_chat", 60000);

		member->eraseBlackboard("formationOffset");
		member->setFollowObject(nullptr);

		member->clearPatrolPoints();
		member->setNextPosition(landingPosition.getX(), landingPosition.getZ(), landingPosition.getY());

		member->dropObserver(ObserverEventType::SQUAD, _this.getReferenceUnsafeStaticCast());
		member->destroyObjectFromWorld(true);

		removeMember(i);
	}

	return teamMembers.size() == 0;
}
