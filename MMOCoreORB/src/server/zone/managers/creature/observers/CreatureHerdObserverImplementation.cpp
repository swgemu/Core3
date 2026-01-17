/*
			Copyright <SWGEmu>
	See file COPYING for copying conditions.
 */

#include "server/zone/managers/creature/observers/CreatureHerdObserver.h"

#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/TangibleObject.h"

void CreatureHerdObserverImplementation::addMember(AiAgent* member) {
	if (member == nullptr)
		return;

	Locker locker(&herdLock);
	herdMembers.add(member);
}

void CreatureHerdObserverImplementation::removeMember(AiAgent* member) {
	if (member == nullptr)
		return;

	Locker locker(&herdLock);

	for (int i = herdMembers.size() - 1; i >= 0; --i) {
		auto herdMember = herdMembers.get(i);

		if (herdMember != nullptr && herdMember->getObjectID() == member->getObjectID()) {
			herdMembers.remove(i);
			break;
		}
	}
}

AiAgent* CreatureHerdObserverImplementation::getMember(int index) {
	Locker locker(&herdLock);

	if (index >= herdMembers.size())
		return nullptr;

	return herdMembers.get(index);
}

int CreatureHerdObserverImplementation::getMemberPosition(uint64 memberID) {
	Locker locker(&herdLock);

	int memberPosition = 0;

	for (int i = 0; i < herdMembers.size(); ++i) {
		auto member = herdMembers.get(i);

		if (member == nullptr || member->getObjectID() != memberID)
			continue;

		memberPosition = i;
		break;
	}


	return memberPosition;
}

AiAgent* CreatureHerdObserverImplementation::getHerdLeader() {
	Locker locker(&herdLock);

	if (herdMembers.size() < 1) {
		return nullptr;
	}

	return getMember(0);
}

void CreatureHerdObserverImplementation::despawnHerd() {
	Locker lock(&herdLock);

	int size = herdMembers.size();

	for (int i = size - 1; i >= 0; --i) {
		auto member = herdMembers.get(i);

		if (member == nullptr || member->isInCombat())
			continue;

		Locker clocker(member, &herdLock);

		member->dropObserver(ObserverEventType::HERD, _this.getReferenceUnsafeStaticCast());

		if (!member->isDead())
			member->destroyObjectFromWorld(true);
	}
}
