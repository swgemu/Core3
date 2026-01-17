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

Vector3 CreatureHerdObserverImplementation::getFormationOffset(int positionIndex, float followerRadius, float leaderRadius) {
	if (positionIndex <= 0) {
		// Leader gets no offset
		return Vector3(0, 0, 0);
	}

	// Use configured spacing or defaults
	float buffer = spacingBuffer > 0 ? spacingBuffer : 1.5f;
	float jitterPercent = maxJitterPercent > 0 ? maxJitterPercent : 0.1f;

	// Safe spacing calculations using both radii
	float combinedRad = leaderRadius + followerRadius;

	// Row and side calculation (position 1 = first follower)
	int side = (positionIndex % 2 == 0) ? -1 : 1;  // Odd positions = right, even = left
	int row = (positionIndex - 1) / 2;              // 0-indexed row behind leader

	// X offset: side spacing with slight row expansion to fan out
	float sideSpacing = (followerRadius * 2.0f) * buffer;
	float baseX = side * (sideSpacing + (row * followerRadius * 0.3f));

	// Y offset: first row clears leader radius, subsequent rows clear previous row
	float rowSpacing = (followerRadius * 2.0f) * buffer;
	float baseY = -((combinedRad * buffer) + (row * rowSpacing));

	// Minimal jitter for natural look (won't cause clipping due to small percentage)
	float maxJitter = followerRadius * jitterPercent;
	float jitterX = (System::frandom(100) - 50) / 50.0f * maxJitter;
	float jitterY = (System::frandom(100) - 50) / 50.0f * maxJitter;

	return Vector3(baseX + jitterX, baseY + jitterY, 0);
}

Vector3 CreatureHerdObserverImplementation::getFormationWorldPosition(AiAgent* member) {
	if (member == nullptr) {
		return Vector3(0, 0, 0);
	}

	Locker locker(&herdLock);

	// Get the herd leader
	if (herdMembers.size() < 1) {
		return member->getWorldPosition();
	}

	AiAgent* leader = herdMembers.get(0);

	if (leader == nullptr) {
		return member->getWorldPosition();
	}

	// If member IS the leader, return leader's current position
	if (leader->getObjectID() == member->getObjectID()) {
		return member->getWorldPosition();
	}

	// Get member's CURRENT position in herd (dynamic - shifts when creatures die)
	int positionIndex = 0;

	for (int i = 0; i < herdMembers.size(); ++i) {
		auto herdMember = herdMembers.get(i);

		if (herdMember != nullptr && herdMember->getObjectID() == member->getObjectID()) {
			positionIndex = i;
			break;
		}
	}

	if (positionIndex <= 0) {
		// Not found or is leader
		return member->getWorldPosition();
	}

	// Get radii for spacing calculation
	float followerRadius = member->getTemplateRadius();
	float leaderRadius = leader->getTemplateRadius();

	// Get local formation offset (relative to leader facing forward)
	Vector3 localOffset = getFormationOffset(positionIndex, followerRadius, leaderRadius);

	// Rotate offset based on leader's facing direction
	float directionAngle = leader->getDirection()->getRadians();
	float cosAngle = Math::cos(directionAngle);
	float sinAngle = Math::sin(directionAngle);

	float xRotated = (localOffset.getX() * cosAngle) + (localOffset.getY() * sinAngle);
	float yRotated = (-localOffset.getX() * sinAngle) + (localOffset.getY() * cosAngle);

	// Calculate world position relative to leader
	Vector3 leaderPos = leader->getWorldPosition();

	return Vector3(leaderPos.getX() + xRotated, leaderPos.getY() + yRotated, leaderPos.getZ());
}
