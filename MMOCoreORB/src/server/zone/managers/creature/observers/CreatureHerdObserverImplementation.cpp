/*
			Copyright <SWGEmu>
	See file COPYING for copying conditions.
 */

#include "server/zone/managers/creature/observers/CreatureHerdObserver.h"

#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/AiSpeciesData.h"
#include "templates/params/creature/CreaturePosture.h"

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
		// The cross-locker below releases herdLock while it spins on a contended
		// member lock, so removeMember (now called on every despawn path) can
		// shrink herdMembers mid-iteration -- a stale index here would read out
		// of bounds. Re-check before each get.
		if (i >= herdMembers.size())
			continue;

		auto member = herdMembers.get(i);

		if (member == nullptr || member->isInCombat())
			continue;

		Locker clocker(member, &herdLock);

		member->dropObserver(ObserverEventType::HERD, _this.getReferenceUnsafeStaticCast());

		if (!member->isDead())
			member->destroyObjectFromWorld(true);
	}
}

bool CreatureHerdObserverImplementation::restHerd() {
	Locker lock(&herdLock);

	int size = herdMembers.size();

	if (size == 0)
		return false;

	// Get zone and creature manager from first valid member
	Zone* zone = nullptr;
	ManagedReference<CreatureManager*> creoManager = nullptr;

	for (int i = 0; i < size; ++i) {
		auto member = herdMembers.get(i);

		if (member != nullptr) {
			zone = member->getZone();

			if (zone != nullptr) {
				creoManager = zone->getCreatureManager();
				break;
			}
		}
	}

	bool anyRested = false;

	for (int i = 0; i < size; ++i) {
		// Cross-locker can release herdLock mid-spin; re-check the index --
		// removeMember on another thread can shrink herdMembers under this loop.
		// continue (not break): one concurrent removal must not abandon the rest
		// of the herd.
		if (i >= herdMembers.size())
			continue;

		auto member = herdMembers.get(i);

		if (member == nullptr || member->isDead() || member->isInCombat())
			continue;

		Locker clocker(member, &herdLock);

		member->setMovementState(AiAgent::RESTING);

		// Chance to stop resting from 45s up to 90s stored in ms
		int delay = 300 * 1000;
		int restingTime = delay - ((45 + System::random(45)) * 1000);
		member->writeBlackboard("restingTime", restingTime);

		// Check species to determine posture
		bool canSitDown = false;

		if (creoManager != nullptr) {
			int speciesID = member->getSpecies();
			AiSpeciesData* speciesData = creoManager->getAiSpeciesData(speciesID);

			if (speciesData != nullptr) {
				canSitDown = speciesData->canSitDown();
			}
		}

		if (canSitDown && System::random(100) > 50) {
			member->setPosture(CreaturePosture::SITTING, true);
		} else {
			member->setPosture(CreaturePosture::LYINGDOWN, true);
		}

		anyRested = true;
	}

	return anyRested;
}

bool CreatureHerdObserverImplementation::stopHerdRest() {
	Locker lock(&herdLock);

	int size = herdMembers.size();

	if (size == 0)
		return false;

	bool anyWoken = false;

	for (int i = 0; i < size; ++i) {
		// Cross-locker can release herdLock mid-spin; re-check the index --
		// removeMember on another thread can shrink herdMembers under this loop.
		// continue (not break): one concurrent removal must not abandon the rest
		// of the herd.
		if (i >= herdMembers.size())
			continue;

		auto member = herdMembers.get(i);

		if (member == nullptr || member->isDead())
			continue;

		Locker clocker(member, &herdLock);

		member->setPosture(CreaturePosture::UPRIGHT, true);

		// Leader patrols, followers follow
		if (i == 0) {
			member->setMovementState(AiAgent::PATROLLING);
		} else {
			member->setMovementState(AiAgent::FOLLOWING);
		}

		anyWoken = true;
	}

	return anyWoken;
}

Vector3 CreatureHerdObserverImplementation::getFormationOffset(int positionIndex, float followerRadius, float leaderRadius) {
	if (positionIndex <= 0) {
		return Vector3(0, 0, 0);
	}

	float buffer = spacingBuffer > 0 ? spacingBuffer : 4.0f;
	float spacing = (followerRadius * 2.0f) * buffer;
	float combinedRad = leaderRadius + followerRadius;

	// Staggered grid: row 0 has 2, row 1 has 3, row 2 has 2, row 3 has 3, etc.
	// This creates a natural blob shape with some in the middle
	int row = 0;
	int count = 0;

	while (count + (row % 2 == 0 ? 2 : 3) < positionIndex) {
		count += (row % 2 == 0) ? 2 : 3;
		row++;
	}

	int posInRow = positionIndex - count - 1;
	int creaturesInRow = (row % 2 == 0) ? 2 : 3;

	// X offset: center the row, then position within it
	float rowWidth = (creaturesInRow - 1) * spacing;
	float baseX = -rowWidth / 2.0f + (posInRow * spacing);

	// Y offset: distance behind leader
	float baseY = -((combinedRad * buffer) + (row * spacing));

	// Small jitter for natural look (safe amount)
	float jitter = followerRadius * 0.15f;
	float jitterX = (System::frandom(100) - 50) / 50.0f * jitter;
	float jitterY = (System::frandom(100) - 50) / 50.0f * jitter;

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
