#include "server/zone/objects/mission/PlayerBounty.h"

bool PlayerBountyImplementation::canTakeMission(uint64 enemyID, uint64 cooldownTime) {
	if (missionCooldownList.size() == 0)
		return true;

	if (!missionCooldownList.contains(enemyID))
		return true;

	uint64 enemyCooldown = missionCooldownList.get(enemyID);

	if (enemyCooldown + cooldownTime <= System::getMiliTime()) {
		missionCooldownList.drop(enemyID);
		return true;
	}

	return false;
}
