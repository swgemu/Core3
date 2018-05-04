#include "server/zone/managers/frs/FrsManagerData.h"

void FrsManagerDataImplementation::updateChallengeTime(uint64 playerID) {
	Time current;
	challengeTimes.put(playerID, current);
}

bool FrsManagerDataImplementation::hasChallengedRecently(uint64 playerID, uint64 challengeCooldown) {
	if (!challengeTimes.contains(playerID))
		return false;

	if (getChallengeDuration(playerID) > challengeCooldown) {
		challengeTimes.drop(playerID);
		return false;
	}

	return true;
}

uint64 FrsManagerDataImplementation::getChallengeTime(uint64 playerID) {
	return challengeTimes.get(playerID).getMiliTime();
}

uint64 FrsManagerDataImplementation::getChallengeDuration(uint64 playerID) {
	return (Time().getMiliTime() - getChallengeTime(playerID));
}
